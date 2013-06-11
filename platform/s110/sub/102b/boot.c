#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "dryos31.h"

#define offsetof(TYPE, MEMBER) ((int) &((TYPE *)0)->MEMBER)

const char * const new_sa = &_end;

// Forward declarations
extern volatile int jogdial_stopped;
void JogDial_task_my(void);

/*
static void __attribute__((naked,noinline)) blink(int cnt)
{
	volatile long *p=(void*)0xC022C30C;
	int i;

	for(;cnt>0;cnt--){
		*p = *p | 0x21; // Turn on LED
		for(i=0;i<0x200000;i++){
			asm ("nop\n");
			asm ("nop\n");
		}
		*p = (*p & 0xFFFFFFDF) | 0x1; // Turn off LED
		for(i=0;i<0x200000;i++){
			asm ("nop\n");
			asm ("nop\n");
		}
	}
}
*/

extern void task_CaptSeq();
extern void task_InitFileModules();
extern void task_RotaryEncoder();
extern void task_MovieRecord();
extern void task_ExpDrv();

#include "../../../generic/boot.c" // for DRYOS_NEW_TASK_HOOK

void __attribute__((naked,noinline)) boot() {
asm volatile (
      "    LDR     R1, =0xC0410000 \n" 
      "    MOV     R0, #0 \n" 
      "    STR     R0, [R1] \n" 
      "    MOV     R1, #0x78 \n" 
      "    MCR     p15, 0, R1, c1, c0 \n" 
      "    MOV     R1, #0 \n" 
      "    MCR     p15, 0, R1, c7, c10, 4 \n" 
      "    MCR     p15, 0, R1, c7, c5 \n" 
      "    MCR     p15, 0, R1, c7, c6 \n" 
      "    MOV     R0, #0x3D \n" 
      "    MCR     p15, 0, R0, c6, c0 \n" 
      "    MOV     R0, #0xC000002F \n" 
      "    MCR     p15, 0, R0, c6, c1 \n" 
      "    MOV     R0, #0x37 \n" 
      "    MCR     p15, 0, R0, c6, c2 \n" 
      "    MOV     R0, #0x40000037 \n" 
      "    MCR     p15, 0, R0, c6, c3 \n" 
      "    MOV     R0, #0x80000017 \n" 
      "    MCR     p15, 0, R0, c6, c4 \n" 
      "    LDR     R0, =0xF0000037 \n" 
      "    MCR     p15, 0, R0, c6, c5 \n" 
      "    LDR     R0, =0xD000002B \n" 
      "    MCR     p15, 0, R0, c6, c7 \n" 
      "    MOV     R0, #0x34 \n" 
      "    MCR     p15, 0, R0, c2, c0 \n" 
      "    MOV     R0, #0x34 \n" 
      "    MCR     p15, 0, R0, c2, c0, 1 \n" 
      "    MOV     R0, #0x34 \n" 
      "    MCR     p15, 0, R0, c3, c0 \n" 
      "    LDR     R0, =0x33333330 \n" 
      "    MCR     p15, 0, R0, c5, c0, 2 \n" 
      "    LDR     R0, =0x33333330 \n" 
      "    MCR     p15, 0, R0, c5, c0, 3 \n" 
      "    MRC     p15, 0, R0, c1, c0 \n" 
      "    ORR     R0, R0, #0x1000 \n" 
      "    ORR     R0, R0, #4 \n" 
      "    ORR     R0, R0, #1 \n" 
      "    MCR     p15, 0, R0, c1, c0 \n" 
      "    MOV     R1, #0x80000006 \n" 
      "    MCR     p15, 0, R1, c9, c1 \n" 
      "    MOV     R1, #6 \n" 
      "    MCR     p15, 0, R1, c9, c1, 1 \n" 
      "    MRC     p15, 0, R1, c1, c0 \n" 
      "    ORR     R1, R1, #0x50000 \n" 
      "    MCR     p15, 0, R1, c1, c0 \n" 
      "    LDR     R2, =0xC0200000 \n" 
      "    MOV     R1, #1 \n" 
      "    STR     R1, [R2, #0x10C] \n" 
      "    MOV     R1, #0xFF \n" 
      "    STR     R1, [R2, #0xC] \n" 
      "    STR     R1, [R2, #0x1C] \n" 
      "    STR     R1, [R2, #0x2C] \n" 
      "    STR     R1, [R2, #0x3C] \n" 
      "    STR     R1, [R2, #0x4C] \n" 
      "    STR     R1, [R2, #0x5C] \n" 
      "    STR     R1, [R2, #0x6C] \n" 
      "    STR     R1, [R2, #0x7C] \n" 
      "    STR     R1, [R2, #0x8C] \n" 
      "    STR     R1, [R2, #0x9C] \n" 
      "    STR     R1, [R2, #0xAC] \n" 
      "    STR     R1, [R2, #0xBC] \n" 
      "    STR     R1, [R2, #0xCC] \n" 
      "    STR     R1, [R2, #0xDC] \n" 
      "    STR     R1, [R2, #0xEC] \n" 
      "    STR     R1, [R2, #0xFC] \n" 
      "    LDR     R1, =0xC0400008 \n" 
      "    LDR     R2, =0x430005 \n" 
      "    STR     R2, [R1] \n" 
      "    MOV     R1, #1 \n" 
      "    LDR     R2, =0xC0243100 \n" 
      "    STR     R2, [R1] \n" 
      "    LDR     R2, =0xC0242010 \n" 
      "    LDR     R1, [R2] \n" 
      "    ORR     R1, R1, #1 \n" 
      "    STR     R1, [R2] \n" 
      "    LDR     R0, =0xF896E004 \n" 
      "    LDR     R1, =0x685000 \n" 
      "    LDR     R3, =0x6B3264 \n" 
"loc_F8000144:\n"
      "    CMP     R1, R3 \n" 
      "    LDRCC   R2, [R0], #4 \n" 
      "    STRCC   R2, [R1], #4 \n" 
      "    BCC     loc_F8000144 \n" 
      "    LDR     R0, =0xF8953558 \n" 
      "    LDR     R1, =0x1900 \n" 
      "    LDR     R3, =0x1C3AC \n" 
"loc_F8000160:\n"
      "    CMP     R1, R3 \n" 
      "    LDRCC   R2, [R0], #4 \n" 
      "    STRCC   R2, [R1], #4 \n" 
      "    BCC     loc_F8000160 \n" 
      "    LDR     R1, =0x28BC88 \n" 
      "    MOV     R2, #0 \n" 
"loc_F8000178:\n"
      "    CMP     R3, R1 \n" 
      "    STRCC   R2, [R3], #4 \n" 
      "    BCC     loc_F8000178 \n" 
      "    BL      HookIntoTaskCreateFunction\n" // DRYOS_NEW_TASK_HOOK
      "    B       sub_F800038C_my \n" 
//      "    B       sub_F800038C \n" 
    );
}

void __attribute__((naked,noinline)) sub_F800038C_my() {

 if ( (*(int*)0xC022F48C & 0x4) )
		*(int*)(0x2FF0+0x4) = 0x200000;  // Playmode "PhySwConfig.c" @f807b174
	else
		*(int*)(0x2FF0+0x4) = 0x100000; // Shootingmode

   asm volatile (
      "    LDR     R0, =0xF8000404 \n" 
      "    MOV     R1, #0 \n" 
      "    LDR     R3, =0xF800043C \n" 
"loc_F8000398:\n"
      "    CMP     R0, R3 \n" 
      "    LDRCC   R2, [R0], #4 \n" 
      "    STRCC   R2, [R1], #4 \n" 
      "    BCC     loc_F8000398 \n" 
      "    LDR     R0, =0xF800043C \n" 
      "    MOV     R1, #0x4B0 \n" 
      "    LDR     R3, =0xF8000624 \n" 
"loc_F80003B4:\n"
      "    CMP     R0, R3 \n" 
      "    LDRCC   R2, [R0], #4 \n" 
      "    STRCC   R2, [R1], #4 \n" 
      "    BCC     loc_F80003B4 \n" 
      "    MOV     R0, #0xD2 \n" 
      "    MSR     CPSR_cxsf, R0 \n" 
      "    MOV     SP, #0x1000 \n" 
      "    MOV     R0, #0xD3 \n" 
      "    MSR     CPSR_cxsf, R0 \n" 
      "    MOV     SP, #0x1000 \n" 
      "    LDR     R0, =0x698 \n" 
      "    LDR     R2, =0xEEEEEEEE \n" 
      "    MOV     R3, #0x1000 \n" 
"loc_F80003E8:\n"
      "    CMP     R0, R3 \n" 
      "    STRCC   R2, [R0], #4 \n" 
      "    BCC     loc_F80003E8 \n" 
//      "    BL      sub_F800116C \n"
      "    BL      sub_F800116C_my \n"
	);
}

void __attribute__((naked,noinline)) sub_F800116C_my() {

	asm volatile (
      "    STR     LR, [SP, #-4]! \n" 
      "    SUB     SP, SP, #0x74 \n" 
      "    MOV     R1, #0x74 \n" 
      "    MOV     R0, SP \n" 
      "    BL      sub_F8648174 \n" 
      "    MOV     R0, #0x83000 \n" 
      "    STR     R0, [SP, #4] \n" 
	#if defined(OPT_CHDK_IN_EXMEM) 
      "    LDR     R0, =0x28C088 \n" 
	#else 
      "    LDR     R0, =new_sa \n"	
      "    LDR     R0, [R0] \n"	
	#endif 
      "    LDR     R2, =0x53F15C \n" 
      "    STR     R0, [SP, #8] \n" 
      "    SUB     R0, R2, R0 \n" 
      "    STR     R0, [SP, #0xC] \n" 
      "    MOV     R0, #0x22 \n" 
      "    STR     R0, [SP, #0x18] \n" 
      "    MOV     R0, #0x98 \n" 
      "    STR     R0, [SP, #0x1C] \n" 
      "    LDR     R0, =0x1E2 \n" 
      "    LDR     R1, =0x549C00 \n" 
      "    STR     R2, [SP, #0x10] \n" 
      "    STR     R0, [SP, #0x20] \n" 
      "    MOV     R0, #0xF6 \n" 
      "    STR     R1, [SP] \n" 
      "    STR     R1, [SP, #0x14] \n" 
      "    STR     R0, [SP, #0x24] \n" 
      "    MOV     R0, #0xB6 \n" 
      "    STR     R0, [SP, #0x28] \n" 
      "    MOV     R0, #0x85 \n" 
      "    STR     R0, [SP, #0x2C] \n" 
      "    MOV     R0, #0x40 \n" 
      "    STR     R0, [SP, #0x30] \n" 
      "    MOV     R0, #4 \n" 
      "    STR     R0, [SP, #0x34] \n" 
      "    MOV     R0, #0x10 \n" 
      "    STR     R0, [SP, #0x5C] \n" 
      "    MOV     R0, #0x800 \n" 
      "    STR     R0, [SP, #0x60] \n" 
      "    MOV     R0, #0xA0 \n" 
      "    STR     R0, [SP, #0x64] \n" 
      "    MOV     R0, #0x280 \n" 
      "    STR     R0, [SP, #0x68] \n" 
//      "    LDR     R1, =0xF8004264 \n" 
      "    LDR     R1, =sub_F8004264_my \n" 
      "    MOV     R2, #0 \n" 
      "    MOV     R0, SP \n" 
      "    BL      sub_F864817C \n" 
      "    ADD     SP, SP, #0x74 \n" 
      "    LDR     PC, [SP], #4 \n" 
	 );
}

void __attribute__((naked,noinline)) sub_F8004264_my() {
     
	 asm volatile (
      "    STMFD   SP!, {R4,LR} \n" 
      "    BL      sub_F8000AE8 \n" 
      "    BL      sub_F8005450 \n" 
      "    CMP     R0, #0 \n" 
      "    LDRLT   R0, =0xF80043D4 \n" 
      "    BLLT    sub_F80043B4 \n" 
      "    BL      sub_F8003E9C \n" 
      "    CMP     R0, #0 \n" 
      "    LDRLT   R0, =0xF80043DC \n" 
      "    BLLT    sub_F80043B4 \n" 
      "    LDR     R0, =0xF80043EC \n" 
      "    BL      sub_F8003F84 \n" 
      "    CMP     R0, #0 \n" 
      "    LDRLT   R0, =0xF80043F4 \n" 
      "    BLLT    sub_F80043B4 \n" 
      "    LDR     R0, =0xF80043EC \n" 
      "    BL      sub_F80029A4 \n" 
      "    CMP     R0, #0 \n" 
      "    LDRLT   R0, =0xF8004408 \n" 
      "    BLLT    sub_F80043B4 \n" 
      "    BL      sub_F8004DEC \n" 
      "    CMP     R0, #0 \n" 
      "    LDRLT   R0, =0xF8004414 \n" 
      "    BLLT    sub_F80043B4 \n" 
      "    BL      sub_F8007A50 \n" 
      "    CMP     R0, #0 \n" 
      "    LDRLT   R0, =0xF8004420 \n" 
      "    BLLT    sub_F80043B4 \n" 
      "    BL      sub_F8007AC8 \n" 
      "    CMP     R0, #0 \n" 
      "    LDRLT   R0, =0xF800442C \n" 
      "    BLLT    sub_F80043B4 \n" 
      "    BL      sub_F8006938 \n" 
      "    CMP     R0, #0 \n" 
      "    LDRLT   R0, =0xF800443C \n" 
      "    BLLT    sub_F80043B4 \n" 
      "    BL      sub_F8001664 \n" 
      "    CMP     R0, #0 \n" 
      "    LDRLT   R0, =0xF8004448 \n" 
      "    BLLT    sub_F80043B4 \n" 
      "    LDMFD   SP!, {R4,LR} \n" 
//      "    B       sub_F800CCB4 \n" 
      "    B       sub_F800CCB4_my \n" 
	);
};

void __attribute__((naked,noinline)) sub_F800CCB4_my() {

	asm volatile (
      "    STMFD   SP!, {R3,LR} \n" 
      "    BL      sub_F803B40C \n" 
      "    CMP     R0, #0 \n" 
      "    BNE     loc_F800CCD4 \n" 
      "    BL      sub_F8023348 \n" 
      "    CMP     R0, #0 \n" 
      "    MOVNE   R0, #1 \n" 
      "    BNE     loc_F800CCD8 \n" 
"loc_F800CCD4:\n"
      "    MOV     R0, #0 \n" 
"loc_F800CCD8:\n"
      //"    BL      sub_F80211F4 \n" 
      "    BL      sub_F80211F4_my \n" 
      "    CMP     R0, #0 \n" 
      "    BNE     loc_F800CCF8 \n" 
      "    BL      sub_F80205CC \n" 
      "    LDR     R1, =0x83DC00 \n" 
      "    MOV     R0, #0x54 \n" 
      "    BL      sub_F80399A0 \n" 
"loc_F800CCF4:\n"
      "    B       loc_F800CCF4 \n" 
"loc_F800CCF8:\n"
      "    BL      sub_F864833C \n" 
      "    LDR     R1, =0x5CE000 \n" 
      "    MOV     R0, #0 \n" 
      "    BL      sub_F803979C \n" 
      "    BL      sub_F8648344 \n" 
      "    MOV     R3, #0 \n" 
      "    STR     R3, [SP] \n" 
      //"    LDR     R3, =0xF800CC4C \n" 
      "    LDR     R3, =task_Startup_my \n" 
      "    MOV     R2, #0 \n" 
      "    MOV     R1, #0x19 \n" 
      "    LDR     R0, =0xF800CD3C \n" 
      "    BL      sub_F8648224 \n" 
      "    MOV     R0, #0 \n" 
      "    LDMFD   SP!, {R3,PC} \n" 
	 );
}

void __attribute__((naked,noinline)) sub_F80211F4_my() {

   asm volatile (
      "    STMFD   SP!, {R4-R6,LR} \n" 
      "    MOV     R6, R0 \n" 
      "    BL      sub_F807B16C \n" 
      "    MOV     R0, #0x36 \n" 
      "    BL      sub_F807BC94 \n" 
      "    MOV     R4, #1 \n" 
      "    BIC     R5, R4, R0 \n" 
      "    MOV     R0, #0x37 \n" 
      "    BL      sub_F807BC94 \n" 
      "    CMP     R6, #0 \n" 
      "    BIC     R4, R4, R0 \n" 
      "    BEQ     loc_F802122C \n" 
      "    ORRS    R0, R5, R4 \n" 
      "    LDMEQFD SP!, {R4-R6,PC} \n" 
"loc_F802122C:\n"
      "    BL      sub_F803B40C \n" 
      "    MOV     R2, R0 \n" 
      "    MOV     R3, #0 \n" 
      "    MOV     R1, R4 \n" 
      "    MOV     R0, R5 \n" 
      //"    BL      sub_F807B174 \n" // Disable StartUpChecks
      "    BL      sub_F807B170 \n" 
      "    MOV     R0, #1 \n" 
      "    LDMFD   SP!, {R4-R6,PC} \n" 
	 );
}

/*----------------------------------------------------------------------
	spytask
-----------------------------------------------------------------------*/
void spytask(long ua, long ub, long uc, long ud, long ue, long uf)
{
    core_spytask();
}

/*----------------------------------------------------------------------
	CreateTask_spytask
-----------------------------------------------------------------------*/
void CreateTask_spytask()
{
	_CreateTask("SpyTask", 0x19, 0x2000, spytask, 0);
}

void __attribute__((naked,noinline)) task_Startup_my() {

   asm volatile (
      "    STMFD   SP!, {R4,LR} \n" 
      "    BL      sub_F8004954 \n" 
      "    BL      sub_F8022408 \n" 
      "    BL      sub_F8020434 \n" 
      "    BL      sub_F803B458 \n" 
      "    BL      sub_F803B644 \n" 
      //"    BL      sub_F803B4EC \n" // load DISKBOOT.BIN
      "    BL      sub_F803B7BC \n" 
      "    BL      sub_F803B988 \n" 
      "    BL      sub_F803B7B0 \n" 
      "    BL      sub_F803B674 \n" 
      "    BL      sub_F80396D0 \n" 
      "    BL      sub_F803B990 \n" 
      "    BL      CreateTask_spytask\n" // +++
//	  "    BL      sub_F8021094 \n"  //"taskCreatePhySw
      "    BL      taskcreatePhySw_my\n" // +++
      "    BL      sub_F8036DF8 \n" 
      "    BL      sub_F803B9A8 \n" 
      "    BL      sub_F801DF88 \n" 
      "    BL      sub_F801FDA4 \n" 
      "    BL      sub_F803B198 \n" 
      "    BL      sub_F80203E8 \n" 
      "    BL      sub_F801FD40 \n" 
      "    BL      sub_F803B7B4 \n" 
      "    BL      sub_F801ECA4 \n" 
      "    BL      sub_F801FD04 \n" 
      "    LDMFD   SP!, {R4,LR} \n" 
      "    B       sub_F8004A90 \n" 
    );
}

void __attribute__((naked,noinline)) taskcreatePhySw_my() {

    asm volatile (
      "    STMFD   SP!, {R3-R5,LR} \n" 
      "    LDR     R4, =0x1E80 \n" 
      "    LDR     R0, [R4, #4] \n" 
      "    CMP     R0, #0 \n" 
      "    BNE     loc_F80210C8 \n" 
      "    MOV     R3, #0 \n" 
      "    STR     R3, [SP] \n" 
      //"    LDR     R3, =0xF8021060 \n" 
      //"    MOV     R2, #0x800 \n" 
      "    LDR     R3, =mykbd_task\n"
      "    MOV     R2, #0x2000\n"             // stack size for new task_PhySw so we don't have to do stack switch

      "    MOV     R1, #0x17 \n" 
      "    LDR     R0, =0xF8021344 \n" 
      "    BL      sub_F8648314 \n" 
      "    STR     R0, [R4, #4] \n" 
"loc_F80210C8:\n"
      "    BL      sub_F807C0E4 \n" // jogdial task called from here
      "    BL      sub_F80D501C \n" 
      "    BL      sub_F8023298 \n" 
      "    CMP     R0, #0 \n" 
      "    BNE     loc_F80210E8 \n" 
      "    LDR     R1, =0x41608 \n" 
      "    MOV     R0, #0 \n" 
      "    BL      sub_F80D4F88 \n" 
"loc_F80210E8:\n"
      "    LDMFD   SP!, {R3-R5,PC} \n" 
    );
}

void __attribute__((naked,noinline)) init_file_modules_task() {
    asm volatile(
 // f80675a8
      "    STMFD   SP!, {R4-R6,LR} \n" 
      "    BL      sub_F80D7584 \n" 
      "    LDR     R5, =0x5006 \n" 
      "    MOVS    R4, R0 \n" 
      "    MOVNE   R1, #0 \n" 
      "    MOVNE   R0, R5 \n" 
      "    BLNE    sub_F80D90A8 \n" 
      "    BL      sub_F80D75B0 \n" 
      "    BL      core_spytask_can_start\n" // +++
      "    CMP     R4, #0 \n" 
      "    LDMNEFD SP!, {R4-R6,PC} \n" 
      "    MOV     R0, R5 \n" 
      "    LDMFD   SP!, {R4-R6,LR} \n" 
      "    MOV     R1, #0 \n" 
      "    B       sub_F80D90A8 \n" 
    );
}

///*----------------------------------------------------------------------
// Pointer to stack location where jogdial task records previous and current
// jogdial positions
short *jog_position;

// @ 0xf807bdb8
void __attribute__((naked,noinline)) JogDial_task_my() {
 asm volatile(
      "    STMFD   SP!, {R4-R11,LR} \n" 
      "    SUB     SP, SP, #0x24 \n" 
      "    BL      sub_F807C150 \n" 
      "    LDR     R12, =0x3014 \n" 
      "    LDR     R6, =0xF864B5D4 \n" 
      "    MOV     R0, #0 \n" 

// Save pointer for kbd.c routine
" ADD R10, SP, #0x18 \n"
" LDR R9, =jog_position \n"
" STR R10, [R9] \n"

      "    ADD     R10, SP, #8 \n" 
      "    ADD     R9, SP, #0x10 \n" 
"loc_F807BDD8:\n"
      "    ADD     R2, SP, #0x1C \n" 
      "    MOV     R1, #0 \n" 
      "    ADD     R4, R2, R0, LSL #1 \n" 
      "    ADD     R3, SP, #0x18 \n" 
      "    STRH    R1, [R4] \n" 
      "    ADD     R4, R3, R0, LSL #1 \n" 
      "    STRH    R1, [R4] \n" 
      "    STR     R1, [R9, R0, LSL #2] \n" 
      "    STR     R1, [R10, R0, LSL #2] \n" 
      "    ADD     R0, R0, #1 \n" 
      "    CMP     R0, #2 \n" 
      "    BLT     loc_F807BDD8 \n" 
"loc_F807BE08:\n"
      "    LDR     R0, =0x3014 \n" 
      "    MOV     R2, #0 \n" 
      "    LDR     R0, [R0, #8] \n" 
      "    MOV     R1, SP \n" 
      "    BL      sub_F86482E4 \n" 
      "    CMP     R0, #0 \n" 
      "    LDRNE   R1, =0x20B \n" 
      "    LDRNE   R0, =0xF807C068 \n" 
      "    BLNE    sub_F864821C \n" 
      "    LDR     R0, [SP] \n" 
      "    AND     R4, R0, #0xFF \n" 
      "    AND     R0, R0, #0xFF00 \n" 
      "    CMP     R0, #0x100 \n" 
      "    BEQ     loc_F807BE78 \n" 
      "    CMP     R0, #0x200 \n" 
      "    BEQ     loc_F807BEB0 \n" 
      "    CMP     R0, #0x300 \n" 
      "    BEQ     sub_F807C0B4 \n" 
      "    CMP     R0, #0x400 \n" 
      "    BNE     loc_F807BE08 \n" 
      "    CMP     R4, #0 \n" 
      "    LDRNE   R1, =0x285 \n" 
      "    LDRNE   R0, =0xF807C068 \n" 
      "    BLNE    sub_F864821C \n" 
      "    RSB     R0, R4, R4, LSL #3 \n" 
      "    LDR     R0, [R6, R0, LSL #2] \n" 
"loc_F807BE70:\n"
      "    BL      sub_F807C134 \n" 
      "    B       loc_F807BE08 \n" 

"loc_F807BE78:\n"
//------------------  added code ---------------------
"labelA:\n"
                "LDR     R0, =jogdial_stopped\n"
                "LDR     R0, [R0]\n"
                "CMP     R0, #1\n"
                "BNE     labelB\n"
                "MOV     R0, #40\n"
                "BL      _SleepTask\n" //sleep
                "B       labelA\n"
"labelB:\n"
//------------------  original code ------------------
      "    LDR     R0, =0x3024 \n" 
      "    LDR     R0, [R0, R4, LSL #2] \n" 
      "    BL      sub_F8039F8C \n" 
      "    LDR     R2, =0xF807BD04 \n" 
      "    ORR     R3, R4, #0x200 \n" 
      "    ADD     R1, R2, #0 \n" 
      "    MOV     R0, #0x28 \n" 
      "    BL      sub_F8039EA8 \n" 
      "    TST     R0, #1 \n" 
      "    CMPNE   R0, #0x15 \n" 
      "    STR     R0, [R10, R4, LSL #2] \n" 
      "    BEQ     loc_F807BE08 \n" 
      "    LDR     R1, =0x21D \n" 
      "    B       loc_F807C054 \n" 
"loc_F807BEB0:\n"
      "    RSB     R5, R4, R4, LSL #3 \n" 
      "    LDR     R0, [R6, R5, LSL #2] \n" 
      "    LDR     R1, =0xC0240000 \n" 
      "    ADD     R0, R1, R0, LSL #8 \n" 
      "    LDR     R0, [R0, #0x104] \n" 
      "    MOV     R1, R0, ASR #0x10 \n" 
      "    ADD     R0, SP, #0x1C \n" 
      "    ADD     R11, R0, R4, LSL #1 \n" 
      "    ADD     R0, SP, #0x18 \n" 
      "    ADD     R0, R0, R4, LSL #1 \n" 
      "    STRH    R1, [R11] \n" 
      "    STR     R0, [SP, #0x20] \n" 
      "    LDRSH   R3, [R0] \n" 
      "    SUB     R2, R1, R3 \n" 
      "    CMP     R2, #0 \n" 
      "    BNE     loc_F807BF34 \n" 
      "    LDR     R0, [R9, R4, LSL #2] \n" 
      "    CMP     R0, #0 \n" 
      "    BEQ     loc_F807C010 \n" 
      "    LDR     R7, =0x3024 \n" 
      "    LDR     R0, [R7, R4, LSL #2] \n" 
      "    BL      sub_F8039F8C \n" 
      "    LDR     R2, =0xF807BD10 \n" 
      "    ORR     R3, R4, #0x300 \n" 
      "    ADD     R1, R2, #0 \n" 
      "    MOV     R0, #0x1F4 \n" 
      "    BL      sub_F8039EA8 \n" 
      "    TST     R0, #1 \n" 
      "    CMPNE   R0, #0x15 \n" 
      "    STR     R0, [R7, R4, LSL #2] \n" 
      "    BEQ     loc_F807C010 \n" 
      "    LDR     R1, =0x236 \n" 
      "    B       loc_F807C008 \n" 
"loc_F807BF34:\n"
      "    MOV     R0, R2 \n" 
      "    RSBLT   R0, R0, #0 \n" 
      "    MOVLE   R7, #0 \n" 
      "    MOVGT   R7, #1 \n" 
      "    CMP     R0, #0xFF \n" 
      "    BLS     loc_F807BF70 \n" 
      "    LDR     R0, =0x7FFF \n" 
      "    CMP     R2, #0 \n" 
      "    SUBLE   R0, R0, R3 \n" 
      "    ADDLE   R0, R0, R1 \n" 
      "    SUBGT   R0, R0, R1 \n" 
      "    ADDGT   R0, R0, R3 \n" 
      "    MVN     R1, #0x8000 \n" 
      "    SUB     R0, R0, R1 \n" 
      "    EOR     R7, R7, #1 \n" 
"loc_F807BF70:\n"
      "    STR     R0, [SP, #4] \n" 
      "    LDR     R0, [R9, R4, LSL #2] \n" 
      "    CMP     R0, #0 \n" 
      "    ADDEQ   R0, R6, R5, LSL #2 \n" 
      "    LDREQ   R0, [R0, #8] \n" 
      "    BEQ     loc_F807BFA8 \n" 
      "    ADD     R8, R6, R5, LSL #2 \n" 
      "    ADD     R1, R8, R7, LSL #2 \n" 
      "    LDR     R1, [R1, #0x10] \n" 
      "    CMP     R1, R0 \n" 
      "    BEQ     loc_F807BFAC \n" 
      "    LDR     R0, [R8, #0xC] \n" 
      "    BL      sub_F80210EC \n" 
      "    LDR     R0, [R8, #8] \n" 
"loc_F807BFA8:\n"
      "    BL      sub_F80210EC \n" 
"loc_F807BFAC:\n"
      "    ADD     R0, R6, R5, LSL #2 \n" 
      "    ADD     R7, R0, R7, LSL #2 \n" 
      "    LDR     R0, [R7, #0x10] \n" 
      "    LDR     R1, [SP, #4] \n" 
      "    BL      sub_F80210FC \n" 
      "    LDR     R0, [R7, #0x10] \n" 
      "    LDR     R7, =0x3024 \n" 
      "    STR     R0, [R9, R4, LSL #2] \n" 
      "    LDRH    R1, [R11] \n" 
      "    LDR     R0, [SP, #0x20] \n" 
      "    STRH    R1, [R0] \n" 
      "    LDR     R0, [R7, R4, LSL #2] \n" 
      "    BL      sub_F8039F8C \n" 
      "    LDR     R2, =0xF807BD10 \n" 
      "    ORR     R3, R4, #0x300 \n" 
      "    ADD     R1, R2, #0 \n" 
      "    MOV     R0, #0x1F4 \n" 
      "    BL      sub_F8039EA8 \n" 
      "    TST     R0, #1 \n" 
      "    CMPNE   R0, #0x15 \n" 
      "    STR     R0, [R7, R4, LSL #2] \n" 
      "    BEQ     loc_F807C010 \n" 
      "    LDR     R1, =0x267 \n" 
"loc_F807C008:\n"
      "    LDR     R0, =0xF807C068 \n" 
      "    BL      sub_F864821C \n" 
"loc_F807C010:\n"
      "    ADD     R0, R6, R5, LSL #2 \n" 
      "    LDR     R0, [R0, #0x18] \n" 
      "    CMP     R0, #1 \n" 
      "    BNE     sub_F807C0AC \n" 
      "    LDR     R0, =0x3014 \n" 
      "    LDR     R0, [R0, #0xC] \n" 
      "    CMP     R0, #0 \n" 
      "    BEQ     sub_F807C0AC \n" 
      "    LDR     R2, =0xF807BD04 \n" 
      "    ORR     R3, R4, #0x400 \n" 
      "    ADD     R1, R2, #0 \n" 
      "    BL      sub_F8039EA8 \n" 
      "    TST     R0, #1 \n" 
      "    CMPNE   R0, #0x15 \n" 
      "    STR     R0, [R10, R4, LSL #2] \n" 
      "    BEQ     loc_F807BE08 \n" 
      "    LDR     R1, =0x26E \n" 
"loc_F807C054:\n"
      "    LDR     R0, =0xF807C068 \n" 
      "    BL      sub_F864821C \n" 
      "    B       loc_F807BE08 \n" 
);
}
