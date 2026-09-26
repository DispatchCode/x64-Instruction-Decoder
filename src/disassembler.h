#ifndef X64ID_DISASSEMBLER_H
#define X64ID_DISASSEMBLER_H

#include <stddef.h>

#include "disassembler_output.h"

#define MAX_INSTRUCTION_BYTES 15

struct disassembler_result {
	struct disassembly_row *rows;
	size_t row_count;
	size_t lane_count;
	size_t *lane_heads;
	char *assembly_text;
};

int disassembler_decode_buffer(const unsigned char *bytes, size_t file_size,
							   int arch, struct disassembler_result *result);
void disassembler_free_result(struct disassembler_result *result);

#endif
