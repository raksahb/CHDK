#include "platform.h"

/*
sensor size from code at sub_FFB59D98 = (4464*3276)*(12/8) = 0x14EB7E0 = 21936096

@FFB59DD8 = 0x1170 = 4464	// raw sensor size
@FFB59DE0 = 0x0ccc = 3276
@FFB59DE8 = 0x10e0 = 4320	// cropped size ??
@FFB59DF0 = 0x0ca8 = 3240
*/

char *hook_raw_image_addr()
{
	// Appears to be two raw buffers (this returns active buffer)
	// Addresses below found in table at FFB99428, ref at FF888840
	// used in _sub_FF888634__SsImgProcBuf.c__0 
	// checks [0x36a0 + 0xc] --> defines which buffer is active

	if (*((int*)0x36ac) != 0)
		return (char*) 0x443B4960;
	else
		return (char*) 0x4235F6B0;	// found at (FFB5A14C) [search CRAW BUF]
}

char *hook_alt_raw_image_addr()
{
	// Appears to be two raw buffers (this returns inactive buffer)
	// Addresses below found in table at FFB99428, ref at FF888840
	// used in _sub_FF888634__SsImgProcBuf.c__0 
	// checks [0x36a0 + 0xc] --> defines which buffer is active

	if (*((int*)0x36ac) == 0)
		return (char*) 0x443B4960;
	else
		return (char*) 0x4235F6B0;	// found at (FFB5A14C) [search CRAW BUF]
}

long hook_raw_size()
{
	return 0x14EB7E0; // search CRAW BUF SIZE
}


char *camera_jpeg_count_str()
{
	return (char*)0xCF2FC; // loc_FFA3BD5C (search "9999", passed to sprintf)
}


void *vid_get_bitmap_fb()
{
	return (void*)0x40471000; // sub_FF930630
}


void *vid_get_viewport_live_fb()
{
	// Values below found by searching firmware for references & usage of viewport buffer address 0x40587700
	// then experimenting to see what gave best Motion Detector speed results using http://dataghost.com/chdk/md_meter.html.
	long* t = (long*)0xFFB96AE0;						// Table of viewport buffer addresses (@FF853F24 in _sub_FF853DC0__LiveImage.c__10)
	unsigned char i = *((unsigned char*)(0x20a8));		// Index value (byte) stored here (@FF853F50 in _sub_FF853DC0__LiveImage.c__10)
	return (void*)t[(i-1)&3];							// Appears to be 4 buffers, current index - 1 seems best
}

void *vid_get_viewport_fb()
{
	return (void*)0x40587700; // sub_FF8E8C5C
}

void *vid_get_viewport_fb_d()
{
	return (void*)(*(int*)(0x32B0+0x58)); // @FF878AB0 & FF878AE8 (comp to S95)
}
