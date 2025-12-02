#ifndef X64ID_DISASM
#define X64ID_DISASM

#include <stdio.h>
#include <stdint.h>

#include "x64id.h"


static const char* REGISTER_TABLE[10][16] = {
	// RT_8
    {"al", "cl", "dl", "bl", "ah", "ch", "dh", "bh",
     "r8b", "r9b", "r10b", "r11b", "r12b", "r13b", "r14b", "r15b"},

    // RT_8_REX (with rex prefix. indices 4-7 are low bytes of stack/base/index)
    {"al", "cl", "dl", "bl", "spl", "bpl", "sil", "dil",
     "r8b", "r9b", "r10b", "r11b", "r12b", "r13b", "r14b", "r15b"},

    // RT_16
    {"ax", "cx", "dx", "bx", "sp", "bp", "si", "di",
     "r8w", "r9w", "r10w", "r11w", "r12w", "r13w", "r14w", "r15w"},

    // RT_32
    {"eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi",
     "r8d", "r9d", "r10d", "r11d", "r12d", "r13d", "r14d", "r15d"},

    // RT_64
    {"rax", "rcx", "rdx", "rbx", "rsp", "rbp", "rsi", "rdi",
     "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15"},

    // RT_XMM (sse/avx)
    {"xmm0", "xmm1", "xmm2", "xmm3", "xmm4", "xmm5", "xmm6", "xmm7",
     "xmm8", "xmm9", "xmm10", "xmm11", "xmm12", "xmm13", "xmm14", "xmm15"},

    // RT_YMM (avx)
    {"ymm0", "ymm1", "ymm2", "ymm3", "ymm4", "ymm5", "ymm6", "ymm7",
     "ymm8", "ymm9", "ymm10", "ymm11", "ymm12", "ymm13", "ymm14", "ymm15"},

    // rt_seg (segment registers)
    {"es", "cs", "ss", "ds", "fs", "gs", "??", "??",
     "es", "cs", "ss", "ds", "fs", "gs", "??", "??"},

    // RT_CR (control registers - specialized moves)
    {"cr0", "cr1", "cr2", "cr3", "cr4", "cr5", "cr6", "cr7",
     "cr8", "cr9", "cr10", "cr11", "cr12", "cr13", "cr14", "cr15"},

    // RT_DR (debug registers)
    {"dr0", "dr1", "dr2", "dr3", "dr4", "dr5", "dr6", "dr7",
     "dr8", "dr9", "dr10", "dr11", "dr12", "dr13", "dr14", "dr15"}
};

extern void x64id_disasm(struct instruction *instr);

#endif
