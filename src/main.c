#include <stdio.h>
#include <stdlib.h>
#include "mca.h"

size_t get_file_size(FILE *hfile)
{
    fseek(hfile, 0, SEEK_END);
    size_t file_size = (size_t) ftell(hfile);
    fseek(hfile, 0, 0);
    return file_size;
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage:\n");
        printf("\tmain <file_name.exe> <architecture>");
        printf("\n\nArchitecture must be 1 (x86) or 2 (x64).");
        exit(-1);
    }

    FILE *hfile = fopen(argv[1], "rb");
    int arch = atoi(argv[2]);

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