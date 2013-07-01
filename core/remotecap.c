#include "ptp.h"
#include "stdlib.h"
#include "platform.h"
#include "conf.h"
#include "remotecap_core.h"
#include "module_load.h"
#include "modules.h"
#include "raw.h"
#include "cachebit.h"

#define HOOK_WAIT_MAX_DEFAULT 3000 // timeout for remotecap hooks, in 10ms sleeps = 30 sec
static int hook_wait_max=HOOK_WAIT_MAX_DEFAULT; 

static int available_image_data=0; // type of data available

static int remote_file_target=0; // requested data types

static ptp_data_chunk raw_chunk;
static ptp_data_chunk dng_hdr_chunk;

// raw subimage range
static int startline=0;
static int linecount=0;

#ifdef CAM_HAS_FILEWRITETASK_HOOK
static int jpeg_curr_chunk;
#ifdef CAM_FILEWRITETASK_SEEKS
static int jpeg_session_wait; // should the current invocation of the jpeg hook block
#endif //CAM_FILEWRITETASK_SEEKS
#endif //CAM_HAS_FILEWRITETASK_HOOK


int remotecap_get_target_support(void) {
    int ret = (PTP_CHDK_CAPTURE_RAW | PTP_CHDK_CAPTURE_DNGHDR);
#ifdef CAM_HAS_FILEWRITETASK_HOOK
    ret |= PTP_CHDK_CAPTURE_JPG;
#endif
    return ret;
}

int remotecap_get_target(void) {
    return remote_file_target;
}

/*
set hook timeout in ms
*/
void remotecap_set_timeout(int timeout) 
{
    if(timeout <= 0) {
        hook_wait_max = HOOK_WAIT_MAX_DEFAULT;
    } else {
        hook_wait_max = timeout/10;
    }
}

int remotecap_get_available_data_type(void) {
    return available_image_data;
}

static void remotecap_set_available_data_type(int type)
{
    available_image_data = type;
}

// free hooks, reset target and available
static void remotecap_reset(void) {
    remote_file_target=0;
    remotecap_set_available_data_type(0);
    // TODO do we need remotecap_jpeg_chunks_done() ?
}

//called to activate or deactive hooks
int remotecap_set_target( int type, int lstart, int lcount )
{
    // fail if invalid / unsupported type requested,
    // or current mode cannot support requested types
    if ((type & ~remotecap_get_target_support()) 
        || !(mode_get() & MODE_REC)
        || ((type & PTP_CHDK_CAPTURE_RAW) && !is_raw_possible())) {
        remotecap_reset();
        return 0;
    }
    // clear requested
    if(type==0) {
        remotecap_reset();
        return 1;
    }
    // invalid range, return error
    if(lstart<0 || lstart>CAM_RAW_ROWS-1 || lcount<0 || lcount+lstart>CAM_RAW_ROWS) {
        remotecap_reset();
        return 0;
    }
    // default lcount = to end of buffer
    if(lcount == 0) {
        lcount = CAM_RAW_ROWS - lstart;
    }
    remote_file_target=type;
    startline=lstart;
    linecount=lcount;
    return 1;
}

/*
don't allow unloading DNG module if target is DNG
not optimal since it could lead to loading/unloading every shot
could make logic more sophisticated later
*/
int remotecap_using_dng_module(void) {
    return (remote_file_target & PTP_CHDK_CAPTURE_DNGHDR) != 0;
}

/*
return 0 if timed out, otherwise non-zero
called from tasks that need to wait for data to be read
*/
static int remotecap_wait(int datatype) {
    int wait = hook_wait_max;

    remotecap_set_available_data_type(datatype);

    while (wait && (remotecap_get_available_data_type() & datatype)) {
        msleep(10);
        wait--;
    }
    return wait;
}


void filewrite_set_discard_jpeg(int state);
int filewrite_get_jpeg_chunk(char **addr,unsigned *size, unsigned n, int *pos);

extern long hook_raw_size(void); // TODO should use camera_sensor, but see note on size mismatch!

void remotecap_raw_available(char *rawadr) {
// TODO this should probably just be noop if hook doesn't exist
#ifdef CAM_HAS_FILEWRITETASK_HOOK
    filewrite_set_discard_jpeg(1);
    jpeg_curr_chunk=0; //needs to be done here
#endif //CAM_HAS_FILEWRITETASK_HOOK
    if (remote_file_target & PTP_CHDK_CAPTURE_DNGHDR) {
        started();
        libdng->create_dng_header_for_ptp(&dng_hdr_chunk);

        if(!remotecap_wait(PTP_CHDK_CAPTURE_DNGHDR)) {
            remotecap_reset();
        }
        libdng->free_dng_header_for_ptp();
        finished();
    }

    if(!(remote_file_target & PTP_CHDK_CAPTURE_RAW)) {
        return;
    }

    started();
    
    raw_chunk.address=(unsigned int)ADR_TO_UNCACHED(rawadr+startline*CAM_RAW_ROWPIX*CAM_SENSOR_BITS_PER_PIXEL/8);
    if ( (startline==0) && (linecount==CAM_RAW_ROWS) )
    {
        //hook_raw_size() is sometimes different than CAM_RAW_ROWS*CAM_RAW_ROWPIX*CAM_SENSOR_BITS_PER_PIXEL/8
        // TODO above shoudln't be true!!!
        //if whole size is requested, send hook_raw_size()
        raw_chunk.length=(unsigned int)hook_raw_size();
    }
    else
    {
        raw_chunk.length=linecount*CAM_RAW_ROWPIX*CAM_SENSOR_BITS_PER_PIXEL/8;
    }
  
    if(!remotecap_wait(PTP_CHDK_CAPTURE_RAW)) {
        remotecap_reset();
    }
    
    finished();
}

#ifdef CAM_HAS_FILEWRITETASK_HOOK
/*
called from filewrite hook to notify code that jpeg data is available
*/
void remotecap_jpeg_available() {
    if(!(remote_file_target & PTP_CHDK_CAPTURE_JPG)) {
        return;
    }
#ifdef CAM_FILEWRITETASK_SEEKS
    // need custom wait code here to resume if jpeg queue is done
    int wait = hook_wait_max;

    jpeg_session_wait = 1;
    remotecap_set_available_data_type(PTP_CHDK_CAPTURE_JPG);

    while (wait && jpeg_session_wait && (remotecap_get_available_data_type() & PTP_CHDK_CAPTURE_JPG)) {
        msleep(10);
        wait--;
    }
    if(wait==0) {
        remotecap_reset();
    }

#else
    if(!remotecap_wait(PTP_CHDK_CAPTURE_JPG)) {
        remotecap_reset();
    }
#endif
}
#endif

// called by ptp code to get next chunk address/size for the format (fmt) that is being currently worked on
// returns 
// 0 no more chunks
// 1 more chunks
// 2 no more chunks in current jpeg queue TODO should keep this as internal state
// TODO could signal error in return value too
int remotecap_get_data_chunk( int fmt, char **addr, unsigned int *size, int *pos )
{
    int morechunks = 0; // default = no more chunks
    *pos = -1; // default = sequential
    
    switch (fmt & remotecap_get_target() & remotecap_get_available_data_type())
    {
        case PTP_CHDK_CAPTURE_RAW: //raw
            *addr=(char*)raw_chunk.address;
            *size=raw_chunk.length;
            break;
#ifdef CAM_HAS_FILEWRITETASK_HOOK
        case PTP_CHDK_CAPTURE_JPG: //jpeg
            morechunks = filewrite_get_jpeg_chunk(addr,size,jpeg_curr_chunk,pos);
            jpeg_curr_chunk+=1;
            break;
#endif
        case PTP_CHDK_CAPTURE_DNGHDR: // dng header
            *addr=(char*)dng_hdr_chunk.address;
            *size=dng_hdr_chunk.length;
            break;
        default:
            /*
             * attempting to get an unsupported, unavailable or not requested format
             * will free all hooks, deactiveate remotecap, and return error status
             */
            *addr=NULL;
            *size=0;
    }
    if(*addr == NULL) {
        remotecap_reset();
        morechunks = 0;
    }

    return morechunks;
}

void remotecap_send_complete(int rcgd_status,int type) {
    if(rcgd_status == 0) {
        // currently only one data type can be available at a time
        remotecap_set_available_data_type(0);
    }
#ifdef CAM_FILEWRITETASK_SEEKS
    else if(rcgd_status == 2) { // next jpeg chunks
        remotecap_jpeg_chunks_done(); // make jpeg_chunks NULL, immediately. TODO needed?
        jpeg_session_wait = 0;
    }
#endif
    // else more chunks of current type, no action needed
}
