#include <stdio.h>
#include <stdlib.h>
#include "fenice.h"

#define  BUFFER_SIZE  16

size_t get_file_size(FILE *hfile)
{
    fseek(hfile, 0, SEEK_END);
    size_t file_size = (size_t) ftell(hfile);
    fseek(hfile, 0, 0);

    return file_size;
}

void instruction_info(struct instruction instr)
{
    printf("------------------------------------------------\n");
    printf("len: %d\n", instr.length);
    printf("RAW bytes (hex): ");
    for(int i=0; i<instr.length; i++)
        printf("%02X ", instr.instr[i]);

    printf("\n\nPrint instruction fields:\n");
    printf("\tLocated Prefixes %d:\n", instr.prefix_cnt);

    for (int i = 0; i < instr.prefix_cnt; i++)
        printf("0x%X ", instr.prefixes[i]);

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

    int file_size = get_file_size(hfile);
    uint8_t buf[file_size];
    reads = fread(buf, sizeof(char), file_size, hfile);

    do {

        offset += decode(&instr, arch, (char*)buf, offset);
        instruction_info(instr);
    } while(offset < file_size);

    fclose(hfile);

    return 0;
}