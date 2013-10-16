/*
 * capt_seq.c - auto-generated by CHDK code_gen.
 */
#include "lolevel.h"
#include "platform.h"
#include "core.h"

#define USE_STUBS_NRFLAG 1          // see stubs_entry.S

#include "../../../generic/capt_seq.c"

/*************************************************************/
//** capt_seq_task @ 0xFF9533C4 - 0xFF9535D8, length=134
void __attribute__((naked,noinline)) capt_seq_task() {
asm volatile (
"    STMFD   SP!, {R4,LR} \n"
"    SUB     SP, SP, #4 \n"
"    MOV     R4, SP \n"
"    B       loc_FF953518 \n"

"loc_FF9533D4:\n"
"    LDR     R2, [SP] \n"
"    LDR     R3, [R2] \n"
"    MOV     R0, R2 \n"
"    CMP     R3, #0x14 \n"
"    LDRLS   PC, [PC, R3, LSL#2] \n"
"    B       loc_FF9534F0 \n"
"    .long   loc_FF953440 \n"
"    .long   loc_FF95344C \n"
"    .long   loc_FF953454 \n"
"    .long   loc_FF953464 \n"
"    .long   loc_FF95345C \n"
"    .long   loc_FF95346C \n"
"    .long   loc_FF953474 \n"
"    .long   loc_FF953480 \n"
"    .long   loc_FF953488 \n"
"    .long   loc_FF953494 \n"
"    .long   loc_FF95349C \n"
"    .long   loc_FF9534A4 \n"
"    .long   loc_FF9534AC \n"
"    .long   loc_FF9534B4 \n"
"    .long   loc_FF9534BC \n"
"    .long   loc_FF9534C8 \n"
"    .long   loc_FF9534D0 \n"
"    .long   loc_FF9534D8 \n"
"    .long   loc_FF9534E0 \n"
"    .long   loc_FF9534E8 \n"
"    .long   loc_FF953500 \n"

"loc_FF953440:\n"
"    BL      sub_FF954BD4 \n"
"    BL      shooting_expo_param_override\n"   // +
"    BL      sub_FF9510D8 \n"
"    B       loc_FF9534FC \n"

"loc_FF95344C:\n"
"    BL      sub_FF953000_my \n"  // --> Patched. Old value = 0xFF953000.
"    B       loc_FF9534FC \n"

"loc_FF953454:\n"
"    BL      sub_FF954F68 \n"
"    B       loc_FF9534FC \n"

"loc_FF95345C:\n"
"    BL      sub_FF953E54 \n"
"    B       loc_FF9534FC \n"

"loc_FF953464:\n"
"    BL      sub_FF953EB0 \n"
"    B       loc_FF9534FC \n"

"loc_FF95346C:\n"
"    BL      sub_FF9540A0 \n"
"    B       loc_FF9534FC \n"

"loc_FF953474:\n"
"    BL      sub_FF954CC8 \n"
"    BL      sub_FF9510D8 \n"
"    B       loc_FF9534FC \n"

"loc_FF953480:\n"
"    BL      sub_FF9530E8 \n"
"    B       loc_FF9534FC \n"

"loc_FF953488:\n"
"    BL      sub_FF954D30 \n"
"    BL      sub_FF9510D8 \n"
"    B       loc_FF9534FC \n"

"loc_FF953494:\n"
"    BL      sub_FF953EB0 \n"
"    B       loc_FF9534FC \n"

"loc_FF95349C:\n"
"    BL      sub_FF9555F0 \n"
"    B       loc_FF9534FC \n"

"loc_FF9534A4:\n"
"    BL      sub_FF955878 \n"
"    B       loc_FF9534FC \n"

"loc_FF9534AC:\n"
"    BL      sub_FF955904 \n"
"    B       loc_FF9534FC \n"

"loc_FF9534B4:\n"
"    BL      sub_FF9559BC \n"
"    B       loc_FF9534FC \n"

"loc_FF9534BC:\n"
"    MOV     R0, #0 \n"
"    BL      sub_FF955A6C \n"
"    B       loc_FF9534FC \n"

"loc_FF9534C8:\n"
"    BL      sub_FF955BBC \n"
"    B       loc_FF9534FC \n"

"loc_FF9534D0:\n"
"    BL      sub_FF955C30 \n"
"    B       loc_FF9534FC \n"

"loc_FF9534D8:\n"
"    BL      sub_FF955CE8 \n"
"    B       loc_FF9534FC \n"

"loc_FF9534E0:\n"
"    BL      sub_FF955DB8 \n"
"    B       loc_FF9534FC \n"

"loc_FF9534E8:\n"
"    BL      sub_FF955DE4 \n"
"    B       loc_FF9534FC \n"

"loc_FF9534F0:\n"
"    LDR     R0, =0xFF952D84 \n"
"    MOV     R1, #0x2DC \n"
"    BL      _DebugAssert \n"

"loc_FF9534FC:\n"
"    LDR     R2, [SP] \n"

"loc_FF953500:\n"
"    LDR     R3, =0x85BDC \n"
"    LDR     R1, [R2, #4] \n"
"    LDR     R0, [R3] \n"
"    BL      sub_FF8223D8 /*_SetEventFlag*/ \n"
"    LDR     R0, [SP] \n"
"    BL      sub_FF952E00 \n"

"loc_FF953518:\n"
"    LDR     R3, =0x85BE0 \n"
"    MOV     R1, R4 \n"
"    LDR     R0, [R3] \n"
"    MOV     R2, #0 \n"
"    BL      sub_FF822B88 /*_ReceiveMessageQueue*/ \n"
"    TST     R0, #1 \n"
"    BEQ     loc_FF9533D4 \n"
"    MOV     R1, #0x24C \n"
"    LDR     R0, =0xFF952D84 \n"
"    ADD     R1, R1, #1 \n"
"    BL      _DebugAssert \n"
"    BL      _ExitTask \n"
"    ADD     SP, SP, #4 \n"
"    LDMFD   SP!, {R4,PC} \n"
"    MOV     PC, LR \n"
);
}

/*************************************************************/
//** sub_FF953000_my @ 0xFF953000 - 0xFF9530E0, length=57
void __attribute__((naked,noinline)) sub_FF953000_my() {
asm volatile (
"    STMFD   SP!, {R4,R5,LR} \n"
"    LDR     R5, [R0, #0xC] \n"
"    BL      sub_FF95BBAC \n"
"    CMP     R0, #0 \n"
"    BNE     loc_FF953018 \n"
"    BL      sub_FF95BBB8 \n"

"loc_FF953018:\n"
"    MOV     R0, R5 \n"
"    BL      sub_FF954F78 \n"
"    TST     R0, #1 \n"
"    MOV     R2, R5 \n"
"    MOV     R1, #1 \n"
"    BEQ     loc_FF953038 \n"
"    LDMFD   SP!, {R4,R5,LR} \n"
"    B       sub_FF951580 \n"

"loc_FF953038:\n"
"    BL      sub_FF9996D4 \n"
"    BL      sub_FF9508E4 \n"
"    MOV     R4, R0 \n"
"    BL      sub_FF827E98 \n"
"    ADD     R3, R5, R5, LSL#1 \n"
"    ADD     R4, R4, R3, LSL#5 \n"
"    STR     R0, [R4, #4] \n"
"    MOV     R0, R5 \n"
"    BL      sub_FF956950 \n"
"    BL      sub_FF9554B4 \n"
"    BL      sub_FF955458 \n"
"    MOV     R0, R5 \n"
"    BL      sub_FF956138_my \n"  // --> Patched. Old value = 0xFF956138.
"    BL      capt_seq_hook_raw_here\n"   // +
"    MOV     R2, R5 \n"
"    MOV     R1, #1 \n"
"    BL      sub_FF951580 \n"
"    LDMFD   SP!, {R4,R5,LR} \n"
"    B       sub_FF956338 \n"
"    MOV     R2, R0 \n"
"    MOV     R1, #2 \n"
"    MOV     R0, #1 \n"
"    STR     LR, [SP, #-4]! \n"
"    BL      sub_FF952EE4 \n"
"    TST     R0, #1 \n"
"    MOV     R1, #0x168 \n"
"    LDR     R0, =0xFF952D84 \n"
"    BEQ     loc_FF9530A8 \n"
"    BL      _DebugAssert \n"

"loc_FF9530A8:\n"
"    MOV     R0, #0 \n"
"    LDR     PC, [SP], #4 \n"

"loc_FF9530DC:\n"
"    MOV     R0, #0 \n"
"    LDR     PC, [SP], #4 \n"
);
}

/*************************************************************/
//** sub_FF956138_my @ 0xFF956138 - 0xFF956164, length=12
void __attribute__((naked,noinline)) sub_FF956138_my() {
asm volatile (
"    STMFD   SP!, {R4,R5,LR} \n"
"    LDR     R3, =0x85C54 \n"
"    LDR     R5, =0x6FDC \n"
"    SUB     SP, SP, #4 \n"
"    MVN     R1, #0 \n"
"    STR     R0, [R5] \n"
"    LDR     R0, [R3] \n"
"    BL      sub_FF822574 /*_ClearEventFlag*/ \n"
"    BL      sub_FF95BE08 \n"
"    LDR     R0, [R0, #0x7C] \n"
"    BL      sub_FF8A2A04 \n"
"    BL      sub_FF9560AC \n"
"    BL      wait_until_remote_button_is_released\n"
"    BL      capt_seq_hook_set_nr\n"
"    LDR     PC, =0xFF956168 \n"  // Continue in firmware
);
}

/*************************************************************/
//** exp_drv_task @ 0xFF8FA108 - 0xFF8FA440, length=207
void __attribute__((naked,noinline)) exp_drv_task() {
asm volatile (
"    STMFD   SP!, {R4-R8,LR} \n"
"    SUB     SP, SP, #0x14 \n"
"    MOV     R7, SP \n"
"    B       loc_FF8FA3FC \n"

"loc_FF8FA118:\n"
"    CMP     R2, #0x19 \n"
"    BNE     loc_FF8FA130 \n"
"    LDR     R0, [R12, #0x34] \n"
"    MOV     LR, PC \n"
"    LDR     PC, [R12, #0x30] \n"
"    B       loc_FF8FA168 \n"

"loc_FF8FA130:\n"
"    SUB     R3, R2, #0x16 \n"
"    CMP     R3, #1 \n"
"    BHI     loc_FF8FA148 \n"
"    MOV     R0, R12 \n"
"    BL      sub_FF8FA0B0 \n"
"    B       loc_FF8FA158 \n"

"loc_FF8FA148:\n"
"    CMP     R2, #0x18 \n"
"    BNE     loc_FF8FA174 \n"
"    BL      sub_FF8AF4D8 \n"
"    BL      sub_FF8B1350 \n"

"loc_FF8FA158:\n"
"    LDR     R3, [SP] \n"
"    LDR     R0, [R3, #0x34] \n"
"    MOV     LR, PC \n"
"    LDR     PC, [R3, #0x30] \n"

"loc_FF8FA168:\n"
"    LDR     R0, [SP] \n"
"    BL      sub_FF8F8524 \n"
"    B       loc_FF8FA3FC \n"

"loc_FF8FA174:\n"
"    CMP     R2, #0xC \n"
"    MOV     R8, #1 \n"
"    BNE     loc_FF8FA1E4 \n"
"    LDR     R1, [R12, #0x24] \n"
"    ADD     R1, R1, R1, LSL#1 \n"
"    ADD     R1, R12, R1, LSL#1 \n"
"    ADD     R6, SP, #0xC \n"
"    SUB     R1, R1, #2 \n"
"    MOV     R2, #6 \n"
"    MOV     R0, R6 \n"
"    BL      _memcpy \n"
"    LDR     R0, [SP] \n"
"    BL      sub_FF8F9750 \n"
"    LDR     R3, [SP] \n"
"    LDR     R1, [R3, #0x24] \n"
"    LDR     R2, [R3, #0x34] \n"
"    ADD     R0, R3, #4 \n"
"    MOV     LR, PC \n"
"    LDR     PC, [R3, #0x30] \n"
"    LDR     R0, [SP] \n"
"    BL      sub_FF8F98D4 \n"
"    LDR     R3, [SP] \n"
"    ADD     R0, R3, #4 \n"
"    LDR     R1, [R3, #0x24] \n"
"    LDR     R2, [R3, #0x3C] \n"
"    MOV     LR, PC \n"
"    LDR     PC, [R3, #0x38] \n"
"    B       loc_FF8FA3AC \n"

"loc_FF8FA1E4:\n"
"    SUB     R3, R2, #0xD \n"
"    CMP     R3, #1 \n"
"    BHI     loc_FF8FA264 \n"
"    ADD     R6, SP, #0xC \n"
"    ADD     R5, SP, #4 \n"
"    MOV     R0, R12 \n"
"    MOV     R1, R6 \n"
"    MOV     R2, R5 \n"
"    BL      sub_FF8F9950 \n"
"    MOV     R4, R0 \n"
"    CMP     R4, #3 \n"
"    CMPNE   R4, #1 \n"
"    BNE     loc_FF8FA244 \n"
"    LDR     R12, [SP] \n"
"    MOV     R0, R5 \n"
"    LDR     R1, [R12, #0x24] \n"
"    MOV     R2, R4 \n"
"    LDR     R3, [R12, #0x34] \n"
"    MOV     LR, PC \n"
"    LDR     PC, [R12, #0x30] \n"
"    MOV     R1, R4 \n"
"    LDR     R0, [SP] \n"
"    BL      sub_FF8FA090 \n"
"    B       loc_FF8FA3AC \n"

"loc_FF8FA244:\n"
"    LDR     R12, [SP] \n"
"    MOV     R2, R4 \n"
"    ADD     R0, R12, #4 \n"
"    LDR     R1, [R12, #0x24] \n"
"    LDR     R3, [R12, #0x34] \n"
"    MOV     LR, PC \n"
"    LDR     PC, [R12, #0x30] \n"
"    B       loc_FF8FA3AC \n"

"loc_FF8FA264:\n"
"    CMP     R2, #0x14 \n"
"    BNE     loc_FF8FA2B8 \n"
"    LDR     R1, [R12, #0x24] \n"
"    ADD     R1, R1, R1, LSL#1 \n"
"    ADD     R1, R12, R1, LSL#1 \n"
"    ADD     R6, SP, #0xC \n"
"    SUB     R1, R1, #2 \n"
"    MOV     R2, #6 \n"
"    MOV     R0, R6 \n"
"    BL      _memcpy \n"
"    LDR     R0, [SP] \n"
"    BL      sub_FF8F92B0 \n"
"    LDR     R3, [SP] \n"
"    ADD     R0, R3, #4 \n"
"    LDR     R1, [R3, #0x24] \n"
"    LDR     R2, [R3, #0x34] \n"
"    MOV     LR, PC \n"
"    LDR     PC, [R3, #0x30] \n"
"    LDR     R0, [SP] \n"
"    BL      sub_FF8F9480 \n"
"    B       loc_FF8FA3AC \n"

"loc_FF8FA2B8:\n"
"    ADD     R6, SP, #0xC \n"
"    ADD     R1, R12, #4 \n"
"    MOV     R0, R6 \n"
"    MOV     R2, #6 \n"
"    BL      _memcpy \n"
"    LDR     R12, [SP] \n"
"    LDR     R3, [R12] \n"
"    MOV     R0, R12 \n"
"    CMP     R3, #0x15 \n"
"    LDRLS   PC, [PC, R3, LSL#2] \n"
"    B       loc_FF8FA398 \n"
"    .long   loc_FF8FA33C \n"
"    .long   loc_FF8FA344 \n"
"    .long   loc_FF8FA34C \n"
"    .long   loc_FF8FA34C \n"
"    .long   loc_FF8FA33C \n"
"    .long   loc_FF8FA344 \n"
"    .long   loc_FF8FA34C \n"
"    .long   loc_FF8FA34C \n"
"    .long   loc_FF8FA364 \n"
"    .long   loc_FF8FA364 \n"
"    .long   loc_FF8FA388 \n"
"    .long   loc_FF8FA390 \n"
"    .long   loc_FF8FA398 \n"
"    .long   loc_FF8FA398 \n"
"    .long   loc_FF8FA398 \n"
"    .long   loc_FF8FA354 \n"
"    .long   loc_FF8FA35C \n"
"    .long   loc_FF8FA370 \n"
"    .long   loc_FF8FA378 \n"
"    .long   loc_FF8FA378 \n"
"    .long   loc_FF8FA398 \n"
"    .long   loc_FF8FA380 \n"

"loc_FF8FA33C:\n"
"    BL      sub_FF8F8A00 \n"
"    B       loc_FF8FA394 \n"

"loc_FF8FA344:\n"
"    BL      sub_FF8F8B3C \n"
"    B       loc_FF8FA394 \n"

"loc_FF8FA34C:\n"
"    BL      sub_FF8F8C6C \n"
"    B       loc_FF8FA394 \n"

"loc_FF8FA354:\n"
"    BL      sub_FF8F8E40 \n"
"    B       loc_FF8FA394 \n"

"loc_FF8FA35C:\n"
"    BL      sub_FF8F8F48 \n"
"    B       loc_FF8FA394 \n"

"loc_FF8FA364:\n"
"    BL      sub_FF8F900C_my \n"  // --> Patched. Old value = 0xFF8F900C.
"    MOV     R8, #0 \n"
"    B       loc_FF8FA394 \n"

"loc_FF8FA370:\n"
"    BL      sub_FF8F90D0 \n"
"    B       loc_FF8FA394 \n"

"loc_FF8FA378:\n"
"    BL      sub_FF8F91B8 \n"
"    B       loc_FF8FA394 \n"

"loc_FF8FA380:\n"
"    BL      sub_FF8F9510 \n"
"    B       loc_FF8FA394 \n"

"loc_FF8FA388:\n"
"    BL      sub_FF8F95E4 \n"
"    B       loc_FF8FA394 \n"

"loc_FF8FA390:\n"
"    BL      sub_FF8F96D0 \n"

"loc_FF8FA394:\n"
"    LDR     R12, [SP] \n"

"loc_FF8FA398:\n"
"    ADD     R0, R12, #4 \n"
"    LDR     R1, [R12, #0x24] \n"
"    LDR     R2, [R12, #0x34] \n"
"    MOV     LR, PC \n"
"    LDR     PC, [R12, #0x30] \n"

"loc_FF8FA3AC:\n"
"    CMP     R8, #1 \n"
"    BNE     loc_FF8FA3D4 \n"
"    LDR     R1, [SP] \n"
"    LDR     R3, [R1, #0x24] \n"
"    ADD     R3, R3, R3, LSL#1 \n"
"    ADD     R1, R1, R3, LSL#1 \n"
"    MOV     R0, R6 \n"
"    SUB     R1, R1, #2 \n"
"    BL      sub_FF8F88B8 \n"
"    B       loc_FF8FA3F4 \n"

"loc_FF8FA3D4:\n"
"    MOV     R0, #1 \n"
"    MOV     R1, R0 \n"
"    MOV     R2, R0 \n"
"    BL      sub_FF8F885C \n"
"    MOV     R0, #1 \n"
"    MOV     R1, R0 \n"
"    MOV     R2, R0 \n"
"    BL      sub_FF8F8978 \n"

"loc_FF8FA3F4:\n"
"    LDR     R0, [SP] \n"
"    BL      sub_FF8F8524 \n"

"loc_FF8FA3FC:\n"
"    LDR     R3, =0x616E0 \n"
"    MOV     R2, #0 \n"
"    LDR     R0, [R3] \n"
"    MOV     R1, R7 \n"
"    BL      sub_FF822B88 /*_ReceiveMessageQueue*/ \n"
"    LDR     R12, [SP] \n"
"    LDR     R2, [R12] \n"
"    CMP     R2, #0x1A \n"
"    BNE     loc_FF8FA118 \n"
"    MOV     R0, R12 \n"
"    BL      sub_FF8F8524 \n"
"    LDR     R3, =0x616DC \n"
"    MOV     R1, #1 \n"
"    LDR     R0, [R3] \n"
"    BL      sub_FF8223D8 /*_SetEventFlag*/ \n"
"    BL      _ExitTask \n"
"    ADD     SP, SP, #0x14 \n"
"    LDMFD   SP!, {R4-R8,PC} \n"
);
}

/*************************************************************/
//** sub_FF8F900C_my @ 0xFF8F900C - 0xFF8F90C0, length=46
void __attribute__((naked,noinline)) sub_FF8F900C_my() {
asm volatile (
"    STMFD   SP!, {R4,R5,LR} \n"
"    LDR     R3, =0x616DC \n"
"    MOV     R4, R0 \n"
"    MOV     R1, #0xE \n"
"    LDR     R0, [R3] \n"
"    BL      sub_FF822574 /*_ClearEventFlag*/ \n"
"    MOV     R1, #0 \n"
"    LDRSH   R0, [R4, #4] \n"
"    BL      sub_FF8F85C4 \n"
"    MOV     R5, R0 \n"
"    LDRSH   R0, [R4, #6] \n"
"    BL      sub_FF8F86F4 \n"
"    LDRSH   R0, [R4, #8] \n"
"    BL      sub_FF8F8790 \n"
"    LDR     R3, [R4] \n"
"    CMP     R3, #9 \n"
"    MOVEQ   R5, #0 \n"
"    CMP     R5, #1 \n"
"    LDR     R1, =0xFF8F8554 \n"
"    MOV     R2, #2 \n"
"    BNE     loc_FF8F9078 \n"
"    LDRSH   R0, [R4, #4] \n"
"    BL      sub_FFB6C6E8 \n"
"    LDR     R2, =0x61708 \n"
"    MOV     R3, #0 \n"
"    STR     R3, [R2] \n"
"    B       loc_FF8F907C \n"

"loc_FF8F9078:\n"
"    BL      sub_FF8F882C \n"

"loc_FF8F907C:\n"
"    STRH    R0, [R4, #4] \n"
"    LDRSH   R0, [R4, #6] \n"
"    BL      sub_FF8AF170_my \n"  // --> Patched. Old value = 0xFF8AF170.
"    BL      sub_FF8B10F4 \n"
"    LDRSH   R0, [R4, #8] \n"
"    MOV     R1, #1 \n"
"    BL      sub_FF8B0F10 \n"
"    MOV     R1, #0 \n"
"    ADD     R0, R4, #8 \n"
"    BL      sub_FF8B0FD4 \n"
"    CMP     R5, #1 \n"
"    MOV     R1, #2 \n"
"    MOV     R2, #0 \n"
"    LDMNEFD SP!, {R4,R5,PC} \n"
"    LDR     R3, =0x616DC \n"
"    LDR     R0, [R3] \n"
"    LDMFD   SP!, {R4,R5,LR} \n"
"    B       sub_FF8223C8 /*_WaitForAllEventFlag*/ \n"
);
}

/*************************************************************/
//** sub_FF8AF170_my @ 0xFF8AF170 - 0xFF8AF1C8, length=23
void __attribute__((naked,noinline)) sub_FF8AF170_my() {
asm volatile (
"    STMFD   SP!, {R4,LR} \n"
"    LDR     R3, =0x55EC \n"
"    LDR     R2, [R3] \n"
"    MOV     R3, R0, LSL#16 \n"
"    CMP     R2, #1 \n"
"    MOV     R1, #0x110 \n"
"    LDR     R0, =0xFF8AEB0C \n"
"    MOV     R4, R3, ASR#16 \n"
"    BEQ     loc_FF8AF198 \n"
"    BL      _DebugAssert \n"

"loc_FF8AF198:\n"
"    MOV     R1, #0x114 \n"
"    CMN     R4, #0xC00 \n"
"    LDR     R3, =0x47C36 \n"
"    LDR     R0, =0xFF8AEB0C \n"
"    ADD     R1, R1, #2 \n"
"    LDREQSH R4, [R3] \n"
"    LDRNE   R3, =0x47C36 \n"
"    CMN     R4, #0xC00 \n"
"    STRH    R4, [R3] \n"
"    BNE     loc_FF8AF1C4 \n"
"    BL      _DebugAssert \n"

"loc_FF8AF1C4:\n"
"    MOV     R0, R4 \n"
"    BL      apex2us \n"  // --> Patched. Old value = _apex2us.
"    LDR     PC, =0xFF8AF1CC \n"  // Continue in firmware
);
}
