#include <stdio.h>
#include <stdlib.h>
#include "../src/mca.h"

/*
 * Please, take a look at README before edit this file or tests (.asm) files
 */

#define  BUFFER_SIZE  16

void instruction_info(struct instruction instr)
{
    #ifdef _ENABLE_RAW_BYTES
    printf("RAW bytes (hex): ");
    for(int i=0; i<instr.length; i++)
        printf("%02X ", instr.instr[i]);
    #endif

    printf("\nInstr. length: %d\n", instr.length);

    printf("Print instruction fields:\n");
    printf("\tLocated Prefixes %d:\n\t\t", instr.prefix_cnt);

    for (int i = 0; i < instr.prefix_cnt; i++)
        printf("0x%X ", instr.prefixes[i]);

    if(instr.set_field & REX)
        printf("\n\n\tREX 0x%X:", instr.rex.value);

    if(instr.set_prefix & VEX) {
        printf("\n\tVEX prefix value:\n\t\t");
        for(int i=0; i<instr.vex_cnt; i++)
            printf("0x%X ", instr.vex[i]);

        #ifdef _ENABLE_VEX_INFO
            if(instr._vex.type == 0xC5) {
                printf("\n\tField 0x%X:\n\t\t", instr.vex[1]);
                printf("r: %X\n\t\t", instr._vex.vexc5b.vex_r);
                printf("v: %X\n\t\t", instr._vex.vexc5b.vex_v);
                printf("L: %X\n\t\t", instr._vex.vexc5b.vex_l);
                printf("pp: %X\n\t\t", instr._vex.vexc5b.vex_pp);
            }
            else {
                printf("\n\tField 0x%X:\n\t\t",instr.vex[1]);
                printf("r: %X\n\t\t", instr._vex.vexc4b.vex_r);
                printf("x: %X\n\t\t", instr._vex.vexc4b.vex_x);
                printf("b: %X\n\t\t", instr._vex.vexc4b.vex_b);
                printf("m: %X\n\n\t", instr._vex.vexc4b.vex_m);
                printf("Field 0x%X:\n\t\t",instr.vex[2]);
                printf("W: %X\n\t\t", instr._vex.vexc4b.vex_w);
                printf("v: %X\n\t\t", instr._vex.vexc4b.vex_v);
                printf("L: %X\n\t\t", instr._vex.vexc4b.vex_l);
                printf("pp: %X\n\n\t", instr._vex.vexc4b.vex_pp);
            }
        #endif
    }

    printf("\n\tOP: 0x%X\n", instr.op);

    if(instr.set_field & MODRM)
        printf("\tmod_reg_rm: 0x%X\n", instr.modrm.value);

    if(instr.set_field & SIB)
        printf("\tSIB byte: 0x%X\n", instr.sib.value);

    if(instr.set_field & DISP)
        printf("\tdisp (%d): 0x%llX\n", instr.disp_len, instr.disp);

    if(instr.set_field & IMM)
        printf("\tIimm: 0x%llX\n", instr.imm);

    printf("------------------------------------------------\n");

}

static int count_bytes(const uint8_t *instr_bytes) {
    int i = 0;
    for(; i<BUFFER_SIZE && instr_bytes[i] != 0xCC; i++);
    return i;
}

static int count_cc_bytes(const uint8_t *instr_bytes) {
    int i = 0, count = 0;
    for(; i<BUFFER_SIZE; i++)
        if(instr_bytes[i] == 0xCC)
            count++;
    return count;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage:\n");
        printf("\tmain_test <file_name.bin> <architecture>");
        printf("\n\nArchitecture must be 1 (x86) or 2 (x64).");
        exit(-1);
    }

    FILE *hfile = fopen(argv[1], "rb");
    int arch = atoi(argv[2]);

    if (hfile == NULL) {
        printf("ERROR: cannot open file!\n");
        exit(-1);
    }

    printf("\n\tSELECTED_ARCHITECTURE: %d\n", arch);

    struct instruction instr = {0};
    printf("Structure size: %d-bytes\n", sizeof(struct instruction));
    int reads;
    int offset = 0;

    uint8_t buf[BUFFER_SIZE];

    int instr_count = 0;
    while(!feof(hfile)) {
        reads = fread(buf, sizeof(char), BUFFER_SIZE, hfile);
        int cc_bytes = count_bytes(buf);
        if(cc_bytes == 0)
            continue; // skip, it's just an invalid/not encoded OP

        printf("\nBytes from file: ");
        for(int i=0; i<BUFFER_SIZE; i++)
            printf("%02X ", buf[i]);
        printf("\n");

        offset = mca_decode(&instr, arch, (char*)buf, 0);
        instruction_info(instr);

        // instruction may have 0xCC bytes,
        // toulerance count 0xCC that are part of the instruction
        int tolerance = count_cc_bytes(instr.instr);
        if((cc_bytes+tolerance) != instr.length)
            printf("Possible decoding error.\nCounted bytes: %d\n\n",cc_bytes);

        instr_count++;
    }

    fclose(hfile);

    return 0;
}