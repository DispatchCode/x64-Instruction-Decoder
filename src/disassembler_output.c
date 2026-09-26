#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#include "disassembler_output.h"

#define MAX_INSTRUCTION_BYTES 15
#define NO_ROW SIZE_MAX

enum target_display_mode { TARGET_FILE_OFFSET, TARGET_ABSOLUTE_ADDRESS };

static char *trim(char *text)
{
	char *end;

	while (isspace((unsigned char)*text))
		text++;
	end = text + strlen(text);
	while (end > text && isspace((unsigned char)end[-1]))
		*--end = '\0';
	return text;
}

static int parse_color(const char *name)
{
	static const struct {
		const char *name;
		int code;
	} colors[] = {{"black", 30},		{"red", 31},
				  {"green", 32},		{"yellow", 33},
				  {"blue", 34},			{"magenta", 35},
				  {"cyan", 36},			{"white", 37},
				  {"bright_black", 90}, {"bright_red", 91},
				  {"bright_green", 92}, {"bright_yellow", 93},
				  {"bright_blue", 94},	{"bright_magenta", 95},
				  {"bright_cyan", 96},	{"bright_white", 97},
				  {"none", 0},			{"default", 0}};

	for (size_t i = 0; i < sizeof(colors) / sizeof(colors[0]); i++) {
		if (strcasecmp(name, colors[i].name) == 0)
			return colors[i].code;
	}
	return -1;
}

struct color_config disassembler_default_colors(void)
{
	return (struct color_config){
		.mode = COLOR_AUTO,
		.mnemonic = 36,
		.jump = 33,
		.call = 35,
		.ret = 32,
		.data = 90,
		.reg = 96,
		.memory_size = 94,
		.brackets = 93,
	};
}

int disassembler_load_color_config(struct color_config *config,
								   const char *requested_path)
{
	const char *environment_path = getenv("X64ID_DISASSEMBLER_CONFIG");
	const char *path = requested_path;
	char line[256];
	int in_colors_section = 0;
	FILE *file;

	if (path == NULL || *path == '\0')
		path = environment_path;
	if (path == NULL || *path == '\0')
		path = "disassembler.ini";
	file = fopen(path, "r");
	if (file == NULL) {
		if ((requested_path != NULL && *requested_path != '\0') ||
			(environment_path != NULL && *environment_path != '\0')) {
			perror(path);
			return 0;
		}
		return 1;
	}

	while (fgets(line, sizeof(line), file) != NULL) {
		char *entry = trim(line);
		char *equals;

		if (*entry == '\0' || *entry == '#' || *entry == ';')
			continue;
		if (*entry == '[') {
			char *close = strchr(entry, ']');
			if (close != NULL) {
				*close = '\0';
				in_colors_section = strcasecmp(trim(entry + 1), "colors") == 0;
			}
			continue;
		}
		if (!in_colors_section || (equals = strchr(entry, '=')) == NULL)
			continue;

		*equals++ = '\0';
		char *key = trim(entry);
		char *value = trim(equals);
		if (strcasecmp(key, "enabled") == 0) {
			if (strcasecmp(value, "always") == 0)
				config->mode = COLOR_ALWAYS;
			else if (strcasecmp(value, "never") == 0)
				config->mode = COLOR_NEVER;
			else if (strcasecmp(value, "auto") == 0)
				config->mode = COLOR_AUTO;
			continue;
		}

		int color = parse_color(value);
		if (color < 0)
			continue;
		if (strcasecmp(key, "mnemonic") == 0)
			config->mnemonic = color;
		else if (strcasecmp(key, "jump") == 0)
			config->jump = color;
		else if (strcasecmp(key, "call") == 0)
			config->call = color;
		else if (strcasecmp(key, "return") == 0)
			config->ret = color;
		else if (strcasecmp(key, "data") == 0)
			config->data = color;
		else if (strcasecmp(key, "register") == 0)
			config->reg = color;
		else if (strcasecmp(key, "memory_size") == 0)
			config->memory_size = color;
		else if (strcasecmp(key, "brackets") == 0)
			config->brackets = color;
	}

	if (ferror(file)) {
		perror(path);
		fclose(file);
		return 0;
	}
	return fclose(file) == 0;
}

int disassembler_colors_enabled(const struct color_config *config)
{
	if (config->mode == COLOR_ALWAYS)
		return 1;
	if (config->mode == COLOR_NEVER)
		return 0;
	return isatty(STDOUT_FILENO);
}

static int color_for_mnemonic(const char *mnemonic,
							  const struct color_config *config)
{
	if (strcmp(mnemonic, "call") == 0)
		return config->call;
	if (strncmp(mnemonic, "ret", 3) == 0 || strncmp(mnemonic, "iret", 4) == 0)
		return config->ret;
	if (mnemonic[0] == 'j')
		return config->jump;
	if (strcmp(mnemonic, "db") == 0)
		return config->data;
	return config->mnemonic;
}

static void print_colored(FILE *stream, const char *text, size_t length,
						  int color, int enabled)
{
	if (enabled && color != 0)
		fprintf(stream, "\033[%dm", color);
	fwrite(text, 1, length, stream);
	if (enabled && color != 0)
		fputs("\033[0m", stream);
}

static int is_identifier_char(unsigned char ch)
{
	return isalnum(ch) || ch == '_';
}

static int token_is(const char *token, size_t length, const char *expected)
{
	return strlen(expected) == length &&
		   strncasecmp(token, expected, length) == 0;
}

static int is_register_token(const char *token, size_t length)
{
	static const char *const fixed_registers[] = {
		"al",	  "cl",		"dl",  "bl",  "ah",	 "ch",	"dh",  "bh",
		"spl",	  "bpl",	"sil", "dil", "ax",	 "cx",	"dx",  "bx",
		"sp",	  "bp",		"si",  "di",  "eax", "ecx", "edx", "ebx",
		"esp",	  "ebp",	"esi", "edi", "rax", "rcx", "rdx", "rbx",
		"rsp",	  "rbp",	"rsi", "rdi", "ip",	 "eip", "rip", "flags",
		"eflags", "rflags", "es",  "cs",  "ss",	 "ds",	"fs",  "gs",
	};

	for (size_t i = 0; i < sizeof(fixed_registers) / sizeof(fixed_registers[0]);
		 i++) {
		if (token_is(token, length, fixed_registers[i]))
			return 1;
	}

	if (length >= 2 && (token[0] == 'r' || token[0] == 'R')) {
		char number[3] = {0};
		size_t digits = 1;
		if (isdigit((unsigned char)token[1])) {
			number[0] = token[1];
			if (length > 2 && isdigit((unsigned char)token[2])) {
				number[1] = token[2];
				digits++;
			}
			int index = atoi(number);
			size_t suffix = 1 + digits;
			if (index >= 8 && index <= 15 &&
				(length == suffix ||
				 (length == suffix + 1 &&
				  strchr("bwd", tolower((unsigned char)token[suffix])) !=
					  NULL)))
				return 1;
		}
	}

	if (length >= 4 && (strncasecmp(token, "xmm", 3) == 0 ||
						strncasecmp(token, "ymm", 3) == 0)) {
		char number[4] = {0};
		size_t digits = length - 3;
		if (digits > 0 && digits < sizeof(number)) {
			memcpy(number, token + 3, digits);
			char *end;
			long index = strtol(number, &end, 10);
			if (*end == '\0' && index >= 0 && index <= 31)
				return 1;
		}
	}

	if (length >= 3 && (strncasecmp(token, "cr", 2) == 0 ||
						strncasecmp(token, "dr", 2) == 0)) {
		char number[4] = {0};
		size_t digits = length - 2;
		if (digits > 0 && digits < sizeof(number)) {
			memcpy(number, token + 2, digits);
			char *end;
			long index = strtol(number, &end, 10);
			if (*end == '\0' && index >= 0 && index <= 15)
				return 1;
		}
	}

	return 0;
}

static size_t memory_size_length(const char *text)
{
	static const char *const sizes[] = {"XMMWORD", "YMMWORD", "QWORD",
										"DWORD",   "WORD",	  "BYTE"};

	for (size_t i = 0; i < sizeof(sizes) / sizeof(sizes[0]); i++) {
		size_t length = strlen(sizes[i]);
		const char *ptr;

		if (strncasecmp(text, sizes[i], length) != 0 ||
			is_identifier_char((unsigned char)text[length]))
			continue;
		ptr = text + length;
		while (isspace((unsigned char)*ptr))
			ptr++;
		if (strncasecmp(ptr, "PTR", 3) == 0 &&
			!is_identifier_char((unsigned char)ptr[3]))
			return (size_t)(ptr + 3 - text);
	}
	return 0;
}

static void print_operands(FILE *stream, const char *text,
						   const struct color_config *config, int use_color)
{
	if (!use_color) {
		fputs(text, stream);
		return;
	}

	while (*text != '\0') {
		if (*text == '[' || *text == ']') {
			print_colored(stream, text++, 1, config->brackets, use_color);
			continue;
		}

		size_t size_length = memory_size_length(text);
		if (size_length != 0) {
			print_colored(stream, text, size_length, config->memory_size,
						  use_color);
			text += size_length;
			continue;
		}

		if (isalpha((unsigned char)*text) || *text == '_') {
			const char *end = text + 1;
			while (is_identifier_char((unsigned char)*end))
				end++;
			size_t length = (size_t)(end - text);
			int color = is_register_token(text, length) ? config->reg : 0;
			print_colored(stream, text, length, color, use_color);
			text = end;
			continue;
		}

		fputc(*text++, stream);
	}
}

static void print_target(FILE *stream, uint64_t target, uintptr_t buffer_base,
						 enum target_display_mode mode)
{
	if (mode == TARGET_FILE_OFFSET) {
		if (target < (uint64_t)buffer_base) {
			fprintf(stream, "-0x%llx",
					(unsigned long long)((uint64_t)buffer_base - target));
			return;
		}
		target -= (uint64_t)buffer_base;
	}
	fprintf(stream, "0x%llx", (unsigned long long)target);
}

static void print_assembly(FILE *stream, const char *assembly,
						   const struct disassembly_row *row,
						   uintptr_t buffer_base,
						   const struct color_config *config, int use_color)
{
	const char *mnemonic_end = assembly;
	size_t mnemonic_length;
	char mnemonic[32];

	while (*mnemonic_end != '\0' && !isspace((unsigned char)*mnemonic_end))
		mnemonic_end++;
	mnemonic_length = (size_t)(mnemonic_end - assembly);
	if (mnemonic_length == 0) {
		fputs(assembly, stream);
		return;
	}
	if (mnemonic_length >= sizeof(mnemonic))
		mnemonic_length = sizeof(mnemonic) - 1;
	memcpy(mnemonic, assembly, mnemonic_length);
	mnemonic[mnemonic_length] = '\0';

	print_colored(stream, assembly, mnemonic_length,
				  color_for_mnemonic(mnemonic, config), use_color);
	if (row->has_branch) {
		fputc(' ', stream);
		print_target(stream, row->absolute_target, buffer_base,
					 TARGET_FILE_OFFSET);
	} else {
		print_operands(stream, mnemonic_end, config, use_color);
	}
}

static void print_table_header(FILE *stream, size_t lane_count)
{
	fprintf(stream, "%-8s  %-45s  ", "Offset", "Machine code");
	for (size_t lane = 0; lane < lane_count; lane++)
		fputs("  ", stream);
	fputs("Assembly\n", stream);

	fprintf(stream, "%-8s  %-45s  ", "--------",
			"---------------------------------------------");
	for (size_t lane = 0; lane < lane_count; lane++)
		fputs("  ", stream);
	fputs("--------\n", stream);
}

static void print_flow_gutter(FILE *stream, const struct disassembly_row *rows,
							  size_t row_index, size_t lane_count,
							  size_t *lane_current)
{
	for (size_t lane = 0; lane < lane_count; lane++) {
		size_t edge = lane_current[lane];
		const char *glyph = " ";

		while (edge != NO_ROW && rows[edge].interval_end < row_index) {
			edge = rows[edge].next_in_lane;
			lane_current[lane] = edge;
		}

		if (edge != NO_ROW && rows[edge].interval_start <= row_index &&
			rows[edge].interval_end >= row_index) {
			const struct disassembly_row *branch = &rows[edge];
			if (branch->target_index == NO_ROW) {
				if (row_index == edge)
					glyph =
						branch->has_target_offset &&
								branch->target_offset < (int64_t)branch->offset
							? "↖"
							: "↘";
			} else if (branch->target_index == edge) {
				glyph = "↻";
			} else if (row_index == edge) {
				glyph = branch->target_index > edge ? "┌" : "└";
			} else if (row_index == branch->target_index) {
				glyph = branch->target_index > edge ? "▼" : "▲";
			} else {
				glyph = "│";
			}
		}

		fprintf(stream, "%s ", glyph);
	}
}

int disassembler_print(FILE *stream, const unsigned char *bytes,
					   const struct disassembly_view *view,
					   const struct color_config *config, int use_color)
{
	size_t *lane_current = NULL;

	if (view->lane_count != 0) {
		lane_current = malloc(view->lane_count * sizeof(*lane_current));
		if (lane_current == NULL)
			return 0;
		memcpy(lane_current, view->lane_heads,
			   view->lane_count * sizeof(*lane_current));
	}

	print_table_header(stream, view->lane_count);
	for (size_t row_index = 0; row_index < view->row_count; row_index++) {
		const struct disassembly_row *row = &view->rows[row_index];
		const char *assembly = view->assembly_text + row->assembly_offset;

		fprintf(stream, "%08zx  ", row->offset);
		for (size_t i = 0; i < row->length; i++)
			fprintf(stream, "%02X ", bytes[row->offset + i]);
		for (size_t i = row->length; i < MAX_INSTRUCTION_BYTES; i++)
			fputs("   ", stream);
		fputs("  ", stream);
		print_flow_gutter(stream, view->rows, row_index, view->lane_count,
						  lane_current);
		print_assembly(stream, assembly, row, (uintptr_t)bytes, config,
					   use_color);
		fputc('\n', stream);
	}

	free(lane_current);
	return !ferror(stream);
}
