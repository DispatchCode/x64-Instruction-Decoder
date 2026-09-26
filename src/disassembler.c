#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "disassembler.h"
#include "x64id.h"

#define NO_ROW SIZE_MAX

struct text_arena {
	char *data;
	size_t length;
	size_t capacity;
};

static int append_text(struct text_arena *arena, const char *text,
					   size_t *text_offset)
{
	size_t text_length = strlen(text) + 1;
	size_t required;

	if (text_length > SIZE_MAX - arena->length)
		return 0;
	required = arena->length + text_length;
	if (required > arena->capacity) {
		size_t capacity = arena->capacity == 0 ? 4096 : arena->capacity;
		char *new_data;

		while (capacity < required) {
			if (capacity > SIZE_MAX / 2) {
				capacity = required;
				break;
			}
			capacity *= 2;
		}
		new_data = realloc(arena->data, capacity);
		if (new_data == NULL)
			return 0;
		arena->data = new_data;
		arena->capacity = capacity;
	}
	*text_offset = arena->length;
	memcpy(arena->data + arena->length, text, text_length);
	arena->length = required;
	return 1;
}

static int is_direct_call(const struct instruction *instr)
{
	return !(instr->set_prefix & VEX) && instr->op_cnt == 0 &&
		   instr->op[0] == 0xE8 && instr->imm_len != 0;
}

static int get_relative_displacement(const struct instruction *instr,
									 int64_t *displacement)
{
	switch (instr->imm_len) {
	case 1:
		*displacement = (int8_t)instr->imm;
		return 1;
	case 2:
		*displacement = (int16_t)instr->imm;
		return 1;
	case 4:
		*displacement = (int32_t)instr->imm;
		return 1;
	default:
		return 0;
	}
}

static uint64_t relative_target(const struct instruction *instr,
								uintptr_t instruction_address)
{
	int64_t displacement;
	uint64_t next_instruction =
		(uint64_t)instruction_address + (uint64_t)instr->length;

	if (!get_relative_displacement(instr, &displacement))
		return instr->label;
	if (displacement < 0)
		return next_instruction - (uint64_t)(-(displacement + 1)) - 1;
	return next_instruction + (uint64_t)displacement;
}

static size_t find_row_offset(const struct disassembly_row *rows,
							  size_t row_count, size_t target)
{
	size_t low = 0;
	size_t high = row_count;

	while (low < high) {
		size_t middle = low + (high - low) / 2;
		if (rows[middle].offset < target)
			low = middle + 1;
		else
			high = middle;
	}
	if (low < row_count && rows[low].offset == target)
		return low;
	return NO_ROW;
}

static int append_row(struct disassembly_row **rows, size_t *row_count,
					  size_t *capacity, struct disassembly_row row)
{
	if (*row_count == *capacity) {
		size_t new_capacity = *capacity == 0 ? 64 : *capacity * 2;
		struct disassembly_row *new_rows;

		if (new_capacity < *capacity ||
			new_capacity > (size_t)-1 / sizeof(**rows))
			return 0;
		new_rows = realloc(*rows, new_capacity * sizeof(**rows));
		if (new_rows == NULL)
			return 0;
		*rows = new_rows;
		*capacity = new_capacity;
	}
	(*rows)[(*row_count)++] = row;
	return 1;
}

static int build_disassembly_rows(const unsigned char *bytes, size_t file_size,
								  int arch, struct disassembly_row **rows_out,
								  size_t *row_count_out, size_t *lane_count_out,
								  size_t **lane_heads_out,
								  struct text_arena *assembly_text)
{
	struct disassembly_row *rows = NULL;
	size_t row_count = 0;
	size_t capacity = 0;
	size_t branch_count = 0;
	size_t *lane_ends = NULL;
	size_t *lane_tails = NULL;
	size_t *lane_heads = NULL;
	size_t lane_count = 0;
	size_t offset = 0;

	x64id_set_arch(arch);
	while (offset < file_size) {
		struct instruction instr;
		int decoded_length = x64id_decode(&instr, (char *)bytes, (int)offset);
		struct disassembly_row row = {
			.offset = offset,
			.length = 1,
			.target_index = NO_ROW,
			.interval_start = NO_ROW,
			.interval_end = NO_ROW,
			.next_in_lane = NO_ROW,
		};
		int valid_instruction = decoded_length > 0 &&
								decoded_length <= MAX_INSTRUCTION_BYTES &&
								(size_t)decoded_length <= file_size - offset;

		if (valid_instruction) {
			int64_t displacement;
			const char *assembly =
				instr.disasm[0] != '\0' ? instr.disasm : NULL;

			row.length = (size_t)decoded_length;
			row.has_branch = instr.jcc_type != 0 || is_direct_call(&instr);
			if (row.has_branch &&
				get_relative_displacement(&instr, &displacement)) {
				row.has_target_offset = 1;
				row.target_offset = (int64_t)offset + row.length + displacement;
			}
			if (row.has_branch)
				row.absolute_target =
					relative_target(&instr, (uintptr_t)(bytes + offset));
			if (is_direct_call(&instr))
				assembly = "call";
			if (assembly == NULL) {
				char fallback[16];
				snprintf(fallback, sizeof(fallback), "db 0x%02X",
						 bytes[offset]);
				if (!append_text(assembly_text, fallback, &row.assembly_offset))
					goto error;
			} else if (!append_text(assembly_text, assembly,
									&row.assembly_offset)) {
				goto error;
			}
		} else {
			char fallback[16];
			snprintf(fallback, sizeof(fallback), "db 0x%02X", bytes[offset]);
			if (!append_text(assembly_text, fallback, &row.assembly_offset))
				goto error;
		}

		if (!append_row(&rows, &row_count, &capacity, row))
			goto error;
		if (row.has_branch)
			branch_count++;
		offset += row.length;
	}

	for (size_t i = 0; i < row_count; i++) {
		if (rows[i].has_target_offset && rows[i].target_offset >= 0 &&
			(uint64_t)rows[i].target_offset < file_size)
			rows[i].target_index =
				find_row_offset(rows, row_count, (size_t)rows[i].target_offset);
	}

	if (branch_count != 0) {
		if (branch_count > (size_t)-1 / sizeof(*lane_ends))
			goto error;
		lane_ends = malloc(branch_count * sizeof(*lane_ends));
		lane_tails = malloc(branch_count * sizeof(*lane_tails));
		lane_heads = malloc(branch_count * sizeof(*lane_heads));
		if (lane_ends == NULL || lane_tails == NULL || lane_heads == NULL)
			goto error;

		for (size_t i = 0; i < row_count; i++) {
			if (!rows[i].has_branch)
				continue;

			size_t start = i;
			size_t end = i;
			if (rows[i].target_index != NO_ROW) {
				if (rows[i].target_index < start)
					start = rows[i].target_index;
				if (rows[i].target_index > end)
					end = rows[i].target_index;
			}

			size_t lane = 0;
			while (lane < lane_count && lane_ends[lane] >= start)
				lane++;
			if (lane == lane_count) {
				lane_ends[lane] = NO_ROW;
				lane_tails[lane] = NO_ROW;
				lane_heads[lane] = NO_ROW;
				lane_count++;
			}

			rows[i].interval_start = start;
			rows[i].interval_end = end;
			if (lane_tails[lane] == NO_ROW)
				lane_heads[lane] = i;
			else
				rows[lane_tails[lane]].next_in_lane = i;
			lane_tails[lane] = i;
			lane_ends[lane] = end;
		}
	}

	free(lane_ends);
	free(lane_tails);
	*rows_out = rows;
	*row_count_out = row_count;
	*lane_count_out = lane_count;
	*lane_heads_out = lane_heads;
	return 1;

error:
	free(rows);
	free(lane_ends);
	free(lane_tails);
	free(lane_heads);
	return 0;
}

int disassembler_decode_buffer(const unsigned char *bytes, size_t file_size,
							   int arch, struct disassembler_result *result)
{
	struct text_arena assembly_text = {0};

	memset(result, 0, sizeof(*result));
	if (!build_disassembly_rows(bytes, file_size, arch, &result->rows,
								&result->row_count, &result->lane_count,
								&result->lane_heads, &assembly_text)) {
		free(assembly_text.data);
		return 0;
	}
	result->assembly_text = assembly_text.data;
	return 1;
}

void disassembler_free_result(struct disassembler_result *result)
{
	free(result->lane_heads);
	free(result->rows);
	free(result->assembly_text);
	memset(result, 0, sizeof(*result));
}
