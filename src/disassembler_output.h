#ifndef X64ID_DISASSEMBLER_OUTPUT_H
#define X64ID_DISASSEMBLER_OUTPUT_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

enum color_mode { COLOR_AUTO, COLOR_ALWAYS, COLOR_NEVER };

struct color_config {
	enum color_mode mode;
	int mnemonic;
	int jump;
	int call;
	int ret;
	int data;
	int reg;
	int memory_size;
	int brackets;
};

struct disassembly_row {
	size_t offset;
	size_t length;
	size_t assembly_offset;
	size_t target_index;
	size_t interval_start;
	size_t interval_end;
	size_t next_in_lane;
	int has_branch;
	int has_target_offset;
	int64_t target_offset;
	uint64_t absolute_target;
};

struct disassembly_view {
	const struct disassembly_row *rows;
	size_t row_count;
	size_t lane_count;
	const size_t *lane_heads;
	const char *assembly_text;
};

struct color_config disassembler_default_colors(void);
int disassembler_load_color_config(struct color_config *config,
								   const char *requested_path);
int disassembler_colors_enabled(const struct color_config *config);
int disassembler_print(FILE *stream, const unsigned char *bytes,
					   const struct disassembly_view *view,
					   const struct color_config *config, int use_color);

#endif
