#include <stdio.h>
#include <stdlib.h>

#include "utils/function_length.h"
#include "utils/test_functions.h"

void instruction_info(struct instruction instr)
{
#ifdef _ENABLE_RAW_BYTES
    printf("RAW bytes (hex): ");
    for(int i=0; i<instr.length; i++)
        printf("%02X ", instr.instr[i]);
#endif

    printf("\nInstr. length: %d\n", instr.length);
    if(instr.jcc_type != 0)
        printf("\nInstr. is a jump with target address: 0x%X\n",instr.label);

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

size_t get_file_size(FILE *hfile)
{
    fseek(hfile, 0, SEEK_END);
    size_t file_size = (size_t) ftell(hfile);
    fseek(hfile, 0, 0);
    return file_size;
}

void binary_file(char *file_name, int architecture) {
    FILE *hfile = fopen(file_name, "rb");
    int arch = architecture;

    if (hfile == NULL) {
        printf("ERROR: cannot open file!\n");
        exit(-1);
    }

    printf("File opened!\n");

    size_t file_size = get_file_size(hfile);
    printf("File size (bytes): %d\n", file_size);

    uint8_t *data_buffer = calloc(file_size, sizeof(char));
    if(data_buffer == NULL)
    {
        printf("Failed allocating memory\n");
        exit(-1);
    }

    fread(data_buffer, sizeof(char), file_size, hfile);
    fclose(hfile);

    int offset = 0x400;
    int parse_bytes = 0x11000;
    int byte_reads = 0;

    while(byte_reads <= parse_bytes) {
        struct instruction instr;
        mca_decode(&instr, arch, (char*)data_buffer, offset);

        for(int i=0; i<instr.length; i++)
            printf("%02X ", instr.instr[i]);

        offset += instr.length;
        byte_reads+=instr.length;
    }
}

void in_memory(int arch) {
    printf("Reading function machine code at address 0x%X...",(uint32_t) example1);
    pFunctionInfo func_info = getFunctionLength(example1, X86);
    printf(" Done!\nFunction Length: %d-bytes, decoded %d instructions.\n", func_info->length, func_info->pVisited->tos);
    printf("\nAddresses of instructions that has been decoded:\n");

    for(int i=0; i<func_info->pVisited->tos; i++) {
        if(i % 8 == 0)
            printf("\n");
        printf("%X, ",func_info->pVisited->vect[i]);

    }
    printf("\n");

    int offset = 0;
    uint32_t start = func_info->pVisited->vect[0];
    uint32_t end = func_info->pVisited->vect[func_info->pVisited->tos-1];

    printf("\nStart disassembly the addresses range: [0x%X, 0x%X]\n\n", start, end);

    while(offset <= func_info->length) {
        struct instruction instr;
        mca_decode(&instr, arch, (char*)example1, offset);
        printf("Instr. VA: 0x%X\n",(uint32_t)((uint32_t)example1+offset));
        instruction_info(instr);

        offset += instr.length;
    }

    vector_free(func_info->pVisited);
    free(func_info);
}

int main(int argc, char *argv[])
{
    if(argc == 2)
    {
        in_memory(atoi(argv[1]));
    }
    else if(argc == 3)
    {
        binary_file(argv[1], atoi(argv[2]));
    }
    else
    {
        printf("How to launch the application?\n");
        printf("1. binary file, 2 parameters required\n");
        printf("\tmain <file_name.exe> <architecture>\n");
        printf("2. in-memory analysis, 1 parameter required\n");
        printf("\tmain <architecture>\n");
        printf("\n\nArchitecture must be 1 (x86) or 2 (x64).");
        exit(-1);
    }
}