#ifndef FENICE_FENICE_H
#define FENICE_FENICE_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define  _ENABLE_RAW_BYTES


enum supported_architecture {
    X86 = 1,
    X64 = 2
};

enum decode_status {
    ERROR = 0,
};

#define ALL (X86 | X64)

//
// instruction prefix look-up table
static size_t x86_64_prefix[256] = {
        //       00  01  02  03  04  05  06  07  08  09  0A  0B  0C  0D  0E  0F
        /* 00 */ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  ALL,
        /* 10 */ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        /* 20 */ 0,  0,  0,  0,  0,  0,  ALL,0,  0,  0,  0,  0,  0,  0,  ALL,0,
        /* 30 */ 0,  0,  0,  0,  0,  0,  ALL,0,  0,  0,  0,  0,  0,  0,  ALL,0,
        /* 40 */ X64,X64,X64,X64,X64,X64,X64,X64,X64,X64,X64,X64,X64,X64,X64,X64, // REX prefixes
        /* 50 */ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        /* 60 */ 0,  0,  0,  0,  ALL,ALL,ALL,ALL,0,  0,  0,  0,  0,  0,  0,  0,
        /* 70 */ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        /* 80 */ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        /* 90 */ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        /* A0 */ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        /* B0 */ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        /* C0 */ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        /* D0 */ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        /* E0 */ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        /* F0 */ ALL,0,ALL,  ALL,0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
};

//
// 1-byte lookup table
//
#define X87_FPU  2

static size_t modrm_1b[256] = {
        //      00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F
        /* 00 */ 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
        /* 10 */ 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
        /* 20 */ 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
        /* 30 */ 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
        /* 40 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /* 50 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /* 60 */ 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0,
        /* 70 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /* 80 */ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        /* 90 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /* A0 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /* B0 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /* C0 */ 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
        /* D0 */ 1, 1, 1, 1, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, // 2 = Coprocessor Escape
        /* E0 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /* F0 */ 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1
};

#define   b   1 // byte
#define   v   2 // word, dword or qword (64bit mode), depending on OS attribute
#define   z   3 // word for 16bit OS or dword for 32/64-bit OS
#define   p   4 // 32-bit, 48-bit, or 80-bit pointer, depending on operand-size attribute
#define   b1  5 // byte
#define   z1  6 // word for 16bit OS or dword for 32/64-bit OS
#define   w   7 // word
#define   wb  8 // word, byte
#define   gr3b  9 // byte (imm exists only if mod.reg == 0)
#define   gr3z  10 // word, dword depending on OS (imm exists only if mod.reg == 0)

static size_t imm_byte_1b[256] = {
        //      00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F
        /* 00 */ 0, 0, 0, 0, b, z, 0, 0, 0, 0, 0, 0, b, z, 0, 0,
        /* 10 */ 0, 0, 0, 0, b, z, 0, 0, 0, 0, 0, 0, b, z, 0, 0,
        /* 20 */ 0, 0, 0, 0, b, z, 0, 0, 0, 0, 0, 0, b, z, 0, 0,
        /* 30 */ 0, 0, 0, 0, b, z, 0, 0, 0, 0, 0, 0, b, z, 0, 0,
        /* 40 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /* 50 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /* 60 */ 0, 0, 0, 0, 0, 0, 0, 0, z, z, b, b, 0, 0, 0, 0,
        /* 70 */ b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b,
        /* 80 */ b, z, b, b, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /* 90 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, p, 0, 0, 0, 0, 0,
        /* A0 */ b1,z1,b1,z1, 0, 0, 0, 0, b, z, 0, 0, 0, 0, 0, 0,
        /* B0 */ b, b, b, b, b, b, b, b, v, v, v, v, v, v, v, v,
        /* C0 */ b, b, w, 0, 0, 0, b, z, wb, 0, w, 0, 0, b, 0, 0,
        /* D0 */ 0, 0, 0, 0, b, b, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /* E0 */ b, b, b, b, b, b, b, b, z, z, p, b, 0, 0, 0, 0,
        /* F0 */ 0, 0, 0, 0, 0, 0, gr3b, gr3z, 0, 0, 0, 0, 0, 0, 0, 0
};

//
// 1-byte lookup table END
//

//
// 2-byte OP look-up table

// 0x0f
#define  OE   0x01
// 0x66 0x0f
#define  O66  0x02
// 0xf2 0x0f
#define  OF2  0x04
// 0xf3 0x0f
#define  OF3  0x08

#define  P1   (OE)
#define  P2   (O66 | OE)
#define  P4   (OF3 | OE)
#define  P5   (O66 | OF2)
#define  P6   (OE  | O66 | OF3)
#define  P7   (OE  | O66 | OF2 | OF3)
#define  P8   (O66 | OF2 | OF3)

static size_t modrm_2b[256] = {
        //       00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F
        /* 00 */ P1,P1,P1,P1,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /* 10 */ P7,P7,P7,P2,P2,P2,P6,P2,P1,0, 0, 0, 0, 0, 0, P1,
        /* 20 */ P1,P1,P1,P1,0, 0, 0, 0, P2,P2,P7,P2,P7,P7,P2,P2,
        /* 30 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /* 40 */ P1,P1,P1,P1,P1,P1,P1,P1,P1,P1,P1,P1,P1,P1,P1,P1,
        /* 50 */ P2,P7,P4,P4,P2,P2,P2,P2,P7,P7,P7,P6,P7,P7,P7,P7,
        /* 60 */ P2,P2,P2,P2,P2,P2,P2,P2,P2,P2,P2,P2,O66,O66,P2,P2,
        /* 70 */ P7,P1,P1,P1,P2,P2,P2,P1,P1,P1, 0, 0,P5,P5,P6,P6,
        /* 80 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /* 90 */ P1,P1,P1,P1,P1,P1,P1,P1,P1,P1,P1,P1,P1,P1,P1,P1,
        /* A0 */ 0, 0, 0, P1,P1,P1, 0, 0, 0, 0, 0,P1,P1,P1,P1,P1,
        /* B0 */ P1,P1,P1,P1,P1,P1,P1,P1,OF3,P1,P1,P1,P4,P4,P1,P1,
        /* C0 */ P1,P1,P7,P1,P2,P2,P2,P1, 0, 0, 0, 0, 0, 0, 0, 0,
        /* D0 */ P5,P2,P2,P2,P2,P2,P8,P2,P2,P2,P2,P2,P2,P2,P2,P2,
        /* E0 */ P2,P2,P2,P2,P2,P2,P8,P2,P2,P2,P2,P2,P2,P2,P2,P2,
        /* F0 */ OF2,P2,P2,P2,P2,P2,P2,P2,P2,P2,P2,P2,P2,P2,P2, 0
};

static size_t imm_byte_2b[256] = {
        //      00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F
        /* 00 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /* 10 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /* 20 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /* 30 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /* 40 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /* 50 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /* 60 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /* 70 */ b, b, b, b, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /* 80 */ z, z, z, z, z, z, z, z, z, z, z, z, z, z, z, z,
        /* 90 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /* A0 */ 0, 0, 0, 0, b, 0, 0, 0, 0, 0, 0, 0, b, 0, 0, 0,
        /* B0 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, b, 0, 0, 0, 0, 0,
        /* C0 */ 0, 0, b, 0, b, b, b, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /* D0 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /* E0 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        /* F0 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

enum prefixes {
    ES = 1,  // 0x26
    CS = 2,  // 0x2E
    SS = 4,  // 0x36
    DS = 8,  // 0x3E
    FS = 16, // 0x64
    GS = 32, // 0x65
    OS = 64, // 0x66
    AS = 128,// 0x67
    REPNE  = 256,
    REPE   = 512,
    OP64   = 1024
};

enum instruction_feature {
    PREFIX = 1,
    ESCAPE = 2, // 0x0F
    OP     = 4,
    OP38   = 8,
    OP3A   = 16,
    MODRM  = 32,
    SIB    = 64,
    REX    = 128,
    DISP   = 512,
    IMM    = 1024,
    FPU    = 2048,
    VEX    = 4096
};

struct instruction {
#ifdef _ENABLE_RAW_BYTES
    uint8_t instr[15];
#endif

    uint8_t prefixes[4];
    uint8_t op;

    union
    {
        struct
        {
            uint8_t rm  : 3;
            uint8_t reg : 3;
            uint8_t mod : 2;
        } bits;
        uint8_t value;
    } modrm;

    union
    {
        struct
        {
            uint8_t rex_b : 1;
            uint8_t rex_x : 1;
            uint8_t rex_r : 1;
            uint8_t rex_w : 1;
        } bits;
        uint8_t value;
    } rex;

    union
    {
        struct
        {
            uint8_t  base   : 3;
            uint8_t  index  : 3;
            uint8_t  scaled : 2;
        } bits;
        uint8_t value;
    } sib;

    uint8_t vex[3];

    uint64_t disp;
    uint64_t imm;

    uint16_t set_prefix; // bit mask
    uint16_t set_field;

    int8_t vex_cnt;
    int prefix_cnt;
    int length;
    int disp_len;
    int imm_len;
};


//
// Functions
//
int mca_decode(struct instruction *instr, enum supported_architecture arch, char *data_src, int offset);
static void mca_decode_modrm(struct instruction *instr, enum supported_architecture arch, const char *data_src, const size_t *modrm_table, const size_t *imm_table);
static inline bool mca_check_sib(uint8_t mod, uint8_t rm);
static inline int mca_displacement_size(uint8_t mod, uint8_t rm);
static inline int mca_imm_size(struct instruction *instr, size_t val, enum supported_architecture arch);
static int mca_decode_2b(struct instruction *instr, enum supported_architecture arch, const char *data_src);
static inline int mca_vex_size(struct instruction *instr, enum supported_architecture arch, const char *data);
static inline void mca_vex_decode(struct instruction *instr, enum supported_architecture arch, const char *data, uint8_t vex_size);

#endif //FENICE_FENICE_H
