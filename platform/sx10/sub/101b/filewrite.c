/*
 * filewrite.c - auto-generated by CHDK code_gen.
 */
#include "lolevel.h"
#include "platform.h"

typedef struct {
    unsigned int address;
    unsigned int length;
} cam_ptp_data_chunk; //camera specific structure

#define MAX_CHUNKS_FOR_JPEG 3 //filewritetask is prepared for this many chunks
/*
 * fwt_data_struct: defined here as it's camera dependent
 * unneeded members are designated with unkn
 * file_offset, full_size, seek_flag only needs to be defined for DryOS>=r50 generation cameras
 * pdc is always required
 * name is not currently used
 */
typedef struct
{
    int unkn1[5];                                //
    cam_ptp_data_chunk pdc[MAX_CHUNKS_FOR_JPEG];
    char name[32];
} fwt_data_struct;

#include "../../../generic/filewrite.c"

/*************************************************************/
//** filewritetask @ 0xFFA45AE4 - 0xFFA45BC4, length=57
void __attribute__((naked,noinline)) filewritetask() {
asm volatile (
"    STMFD   SP!, {R1-R5,LR} \n"
"    LDR     R4, =0xCB68 \n"

"loc_FFA45AEC:\n"
"    LDR     R0, [R4, #0x10] \n"
"    MOV     R2, #0 \n"
"    ADD     R1, SP, #8 \n"
"    BL      sub_FF8274FC /*_ReceiveMessageQueue*/ \n"
"    CMP     R0, #0 \n"
"    BNE     loc_FFA45B1C \n"
"    LDR     R0, [SP, #8] \n"
"    LDR     R1, [R0] \n"
"    CMP     R1, #1 \n"
"    BNE     loc_FFA45B24 \n"
"    LDR     R0, [R4, #8] \n"
"    BL      _GiveSemaphore \n"

"loc_FFA45B1C:\n"
"    BL      _ExitTask \n"
"    LDMFD   SP!, {R1-R5,PC} \n"

"loc_FFA45B24:\n"
"    SUB     R1, R1, #2 \n"
"    CMP     R1, #5 \n"
"    ADDLS   PC, PC, R1, LSL#2 \n"
"    B       loc_FFA45AEC \n"
"    B       loc_FFA45B4C \n"
"    B       loc_FFA45BB0 \n"
"    B       loc_FFA45BB8 \n"
"    B       loc_FFA45BB8 \n"
"    B       loc_FFA45BB8 \n"
"    B       loc_FFA45BC0 \n"

"loc_FFA45B4C:\n"
"    MOV     R0, #0 \n"
"    STR     R0, [SP] \n"

"loc_FFA45B54:\n"
"    LDR     R0, [R4, #0x10] \n"
"    MOV     R1, SP \n"
"    BL      sub_FF827740 /*_GetNumberOfPostedMessages*/ \n"
"    LDR     R0, [SP] \n"
"    CMP     R0, #0 \n"
"    BEQ     loc_FFA45B80 \n"
"    LDR     R0, [R4, #0x10] \n"
"    MOV     R2, #0 \n"
"    ADD     R1, SP, #4 \n"
"    BL      sub_FF8274FC /*_ReceiveMessageQueue*/ \n"
"    B       loc_FFA45B54 \n"

"loc_FFA45B80:\n"
"    LDR     R0, [R4] \n"
"    CMN     R0, #1 \n"
"    BEQ     loc_FFA45BA4 \n"
"    BL      fwt_close \n"  // --> Patched. Old value = _Close.
"    MVN     R0, #0 \n"
"    STR     R0, [R4] \n"
"    LDR     R0, =0x7EC98 \n"
"    BL      sub_FF85AF9C \n"
"    BL      sub_FF859644 \n"

"loc_FFA45BA4:\n"
"    LDR     R0, [R4, #0xC] \n"
"    BL      _GiveSemaphore \n"
"    B       loc_FFA45AEC \n"

"loc_FFA45BB0:\n"
"    BL      sub_FFA45D84_my \n"  // --> Patched. Old value = 0xFFA45D84. Open stage
"    B       loc_FFA45AEC \n"

"loc_FFA45BB8:\n"
"    BL      sub_FFA45EC0_my \n"  // --> Patched. Old value = 0xFFA45EC0. Write stage
"    B       loc_FFA45AEC \n"

"loc_FFA45BC0:\n"
"    BL      sub_FFA45FBC_my \n"  // --> Patched. Old value = 0xFFA45FBC. Close stage
"    B       loc_FFA45AEC \n"
);
}

/*************************************************************/
//** sub_FFA45D84_my @ 0xFFA45D84 - 0xFFA45DC4, length=17
void __attribute__((naked,noinline)) sub_FFA45D84_my() {
asm volatile (
"    STMFD   SP!, {R4-R8,LR} \n"
"    MOV     R4, R0 \n"
"    ADD     R0, R0, #0x2C \n"
"    SUB     SP, SP, #0x38 \n"
"    BL      sub_FF85AF9C \n"
"    MOV     R1, #0 \n"
"    BL      sub_FF8595F4 \n"
"    LDR     R0, [R4, #0xC] \n"
"    BL      sub_FF857904 \n"
"    LDR     R7, [R4, #8] \n"
"    LDR     R8, =0x1B6 \n"
"    ADD     R6, R4, #0x2C \n"
"    LDR     R5, [R4, #0xC] \n"
//hook start
"    STMFD SP!, {R4-R12,LR}\n"
"    MOV R0, R4\n"
"    BL filewrite_main_hook\n"
"    LDMFD SP!, {R4-R12,LR}\n"
//hook end
"    MOV     R0, R6 \n"
"    MOV     R1, R7 \n"
"    MOV     R2, R8 \n"
"    BL      fwt_open \n"  // --> Patched. Old value = _Open.
"    LDR     PC, =0xFFA45DC8 \n"  // Continue in firmware
);
}

/*************************************************************/
//** sub_FFA45EC0_my @ 0xFFA45EC0 - 0xFFA45FB8, length=63
void __attribute__((naked,noinline)) sub_FFA45EC0_my() {
asm volatile (
"    STMFD   SP!, {R4-R10,LR} \n"
"    MOV     R4, R0 \n"
"    LDR     R0, [R0] \n"
"    CMP     R0, #4 \n"
"    LDREQ   R6, [R4, #0x18] \n"
"    LDREQ   R7, [R4, #0x14] \n"
"    BEQ     loc_FFA45EFC \n"
"    CMP     R0, #5 \n"
"    LDREQ   R6, [R4, #0x20] \n"
"    LDREQ   R7, [R4, #0x1C] \n"
"    BEQ     loc_FFA45EFC \n"
"    CMP     R0, #6 \n"
"    BNE     loc_FFA45F10 \n"
"    LDR     R6, [R4, #0x28] \n"
"    LDR     R7, [R4, #0x24] \n"

"loc_FFA45EFC:\n"
"    CMP     R6, #0 \n"
"    BNE     loc_FFA45F20 \n"

"loc_FFA45F04:\n"
"    MOV     R1, R4 \n"
"    MOV     R0, #7 \n"
"    B       loc_FFA45FB4 \n"

"loc_FFA45F10:\n"
"    LDR     R1, =0x205 \n"
"    LDR     R0, =0xFFA45EA0 /*'dwFWrite.c'*/ \n"
"    BL      _DebugAssert \n"
"    B       loc_FFA45F04 \n"

"loc_FFA45F20:\n"
"    LDR     R9, =0xCB68 \n"
"    MOV     R5, R6 \n"

"loc_FFA45F28:\n"
"    LDR     R0, [R4, #4] \n"
"    CMP     R5, #0x1000000 \n"
"    MOVLS   R8, R5 \n"
"    MOVHI   R8, #0x1000000 \n"
"    BIC     R1, R0, #0xFF000000 \n"
"    CMP     R1, #0 \n"
"    BICNE   R0, R0, #0xFF000000 \n"
"    RSBNE   R0, R0, #0x1000000 \n"
"    CMPNE   R8, R0 \n"
"    MOVHI   R8, R0 \n"
"    LDR     R0, [R9] \n"
"    MOV     R2, R8 \n"
"    MOV     R1, R7 \n"
"    BL      fwt_write \n"  // --> Patched. Old value = _Write.
"    LDR     R1, [R4, #4] \n"
"    CMP     R8, R0 \n"
"    ADD     R1, R1, R0 \n"
"    STR     R1, [R4, #4] \n"
"    BEQ     loc_FFA45F88 \n"
"    LDR     R0, =0x10B1 \n"
"    BL      sub_FF880C60 /*_IsControlEventActive_FW*/ \n"
"    LDR     R1, =0x9200005 \n"
"    STR     R1, [R4, #0x10] \n"
"    B       loc_FFA45F04 \n"

"loc_FFA45F88:\n"
"    SUB     R5, R5, R0 \n"
"    CMP     R5, R6 \n"
"    ADD     R7, R7, R0 \n"
"    LDRCS   R0, =0xFFA45EA0 /*'dwFWrite.c'*/ \n"
"    MOVCS   R1, #0x234 \n"
"    BLCS    _DebugAssert \n"
"    CMP     R5, #0 \n"
"    BNE     loc_FFA45F28 \n"
"    LDR     R0, [R4] \n"
"    MOV     R1, R4 \n"
"    ADD     R0, R0, #1 \n"

"loc_FFA45FB4:\n"
"    LDMFD   SP!, {R4-R10,LR} \n"
"    B       sub_FFA45A3C \n"
);
}

/*************************************************************/
//** sub_FFA45FBC_my @ 0xFFA45FBC - 0xFFA46058, length=40
void __attribute__((naked,noinline)) sub_FFA45FBC_my() {
asm volatile (
"    STMFD   SP!, {R4,R5,LR} \n"
"    LDR     R5, =0xCB68 \n"
"    MOV     R4, R0 \n"
"    LDR     R0, [R5] \n"
"    SUB     SP, SP, #0x1C \n"
"    CMN     R0, #1 \n"
"    BEQ     loc_FFA45FF0 \n"
"    BL      fwt_close \n"  // --> Patched. Old value = _Close.
"    CMP     R0, #0 \n"
"    LDRNE   R0, =0x9200003 \n"
"    STRNE   R0, [R4, #0x10] \n"
"    MVN     R0, #0 \n"
"    STR     R0, [R5] \n"

"loc_FFA45FF0:\n"
"    LDR     R0, [R4, #0x10] \n"
"    TST     R0, #1 \n"
"    BNE     loc_FFA46038 \n"
"    LDR     R0, =0x81FF \n"
"    ADD     R1, SP, #4 \n"
"    STR     R0, [SP, #4] \n"
"    MOV     R0, #0x20 \n"
"    STR     R0, [SP, #8] \n"
"    LDR     R0, [R4, #4] \n"
"    STR     R0, [SP, #0xC] \n"
"    LDR     R0, [R4, #0xC] \n"
"    STR     R0, [SP, #0x10] \n"
"    LDR     R0, [R4, #0xC] \n"
"    STR     R0, [SP, #0x14] \n"
"    LDR     R0, [R4, #0xC] \n"
"    STR     R0, [SP, #0x18] \n"
"    ADD     R0, R4, #0x2C \n"
"    BL      sub_FF858F08 \n"

"loc_FFA46038:\n"
"    ADD     R0, R4, #0x2C \n"
"    BL      sub_FF85AF9C \n"
"    BL      sub_FF859644 \n"
"    LDR     R1, [R5, #0x14] \n"
"    CMP     R1, #0 \n"
"    LDRNE   R0, [R4, #0x10] \n"
"    BLXNE   R1 \n"
"    ADD     SP, SP, #0x1C \n"
"    LDMFD   SP!, {R4,R5,PC} \n"
);
}