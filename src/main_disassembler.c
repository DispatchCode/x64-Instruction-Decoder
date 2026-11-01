// SPDX-License-Identifier: GPL-2.0-only

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <unistd.h>

#include "disassembler.h"
#include "x64id.h"

static int read_line(const char *prompt, char *buffer, size_t buffer_size)
{
	fputs(prompt, stdout);
	if (fgets(buffer, (int)buffer_size, stdin) == NULL)
		return 0;

	buffer[strcspn(buffer, "\r\n")] = '\0';
	return 1;
}

static int parse_architecture(const char *input, int *arch)
{
	char *end;
	long value;

	if (strcasecmp(input, "x86") == 0) {
		*arch = X86;
		return 1;
	}
	if (strcasecmp(input, "x86_64") == 0 || strcasecmp(input, "x64") == 0) {
		*arch = X64;
		return 1;
	}

	errno = 0;
	value = strtol(input, &end, 10);
	while (isspace((uint8_t)*end))
		end++;

	if (errno != 0 || end == input || *end != '\0' ||
		(value != X86 && value != X64))
		return 0;

	*arch = (int)value;
	return 1;
}

struct byte_buffer {
	uint8_t *data;
	size_t length;
	size_t capacity;
};

struct hex_parser {
	struct byte_buffer *bytes;
	uint8_t high_nibble;
};

static int reserve_bytes(struct byte_buffer *buffer, size_t required)
{
	size_t capacity = buffer->capacity ? buffer->capacity : 64;
	uint8_t *data;

	while (capacity < required) {
		if (capacity > SIZE_MAX / 2) {
			capacity = required;
			break;
		}
		capacity *= 2;
	}
	if (capacity == buffer->capacity)
		return 1;
	data = realloc(buffer->data, capacity);
	if (data == NULL)
		return 0;
	buffer->data = data;
	buffer->capacity = capacity;
	return 1;
}

static int append_byte(struct byte_buffer *buffer, uint8_t byte)
{
	if (buffer->length >= INT_MAX || !reserve_bytes(buffer, buffer->length + 1))
		return 0;
	buffer->data[buffer->length++] = byte;
	return 1;
}

static int hex_value(int character)
{
	if (character >= '0' && character <= '9')
		return character - '0';
	character = tolower((uint8_t)character);
	if (character >= 'a' && character <= 'f')
		return character - 'a' + 10;
	return -1;
}

static int parse_hex_character(struct hex_parser *parser, int character)
{
	int nibble = hex_value(character);

	if (nibble >= 0) {
		if (parser->high_nibble == UINT8_MAX) {
			parser->high_nibble = (uint8_t)nibble;
			return 1;
		}
		if (!append_byte(parser->bytes,
						 (uint8_t)((parser->high_nibble << 4) | nibble)))
			return 0;
		parser->high_nibble = UINT8_MAX;
		return 1;
	}

	if (isspace((uint8_t)character) || character == ':' || character == ',')
		return parser->high_nibble == UINT8_MAX;
	return 0;
}

static int parse_hex_argument(struct hex_parser *parser, const char *text)
{
	for (const uint8_t *cursor = (const uint8_t *)text; *cursor != '\0';
		 cursor++) {
		if (!parse_hex_character(parser, *cursor))
			return 0;
	}
	return parser->high_nibble == UINT8_MAX;
}

static int read_hex_input(struct byte_buffer *bytes)
{
	struct hex_parser parser = {.bytes = bytes, .high_nibble = UINT8_MAX};
	int character;
	int terminal_input = isatty(STDIN_FILENO);

	if (terminal_input)
		fputs("Machine-code bytes (hex): ", stdout);
	while ((character = getchar()) != EOF) {
		if (terminal_input && (character == '\n' || character == '\r'))
			break;
		if (!parse_hex_character(&parser, character)) {
			fputs("Invalid byte input; enter pairs of hexadecimal digits.\n",
				  stderr);
			return 0;
		}
	}
	if (ferror(stdin)) {
		perror("Unable to read byte input");
		return 0;
	}
	if (parser.high_nibble != UINT8_MAX || bytes->length == 0) {
		fputs("Enter one or more complete hexadecimal bytes.\n", stderr);
		return 0;
	}
	return 1;
}

static int disassemble_buffer(const uint8_t *bytes, size_t file_size,
							  FILE *input_file, const char *output_path,
							  int arch, const struct color_config *config)
{
	FILE *output = NULL;
	struct disassembler_result disassembly = {0};
	int result = EXIT_FAILURE;
	int use_color = disassembler_colors_enabled(config);

	if (file_size > INT_MAX) {
		fputs("Input file exceeds the decoder's maximum supported size.\n",
			  stderr);
		return EXIT_FAILURE;
	}

	if (!disassembler_decode_buffer(bytes, file_size, arch, &disassembly)) {
		fputs("Unable to build the control-flow map.\n", stderr);
		return EXIT_FAILURE;
	}
	if (output_path != NULL) {
		struct stat output_stat;

		if (input_file != NULL) {
			struct stat input_stat;

			if (fstat(fileno(input_file), &input_stat) == 0 &&
				stat(output_path, &output_stat) == 0 &&
				input_stat.st_dev == output_stat.st_dev &&
				input_stat.st_ino == output_stat.st_ino) {
				fputs("Output file must differ from the input binary.\n",
					  stderr);
				goto cleanup;
			}
		}

		output = fopen(output_path, "w");
		if (output == NULL) {
			perror(output_path);
			goto cleanup;
		}
	}

	struct disassembly_view view = {
		.rows = disassembly.rows,
		.row_count = disassembly.row_count,
		.lane_count = disassembly.lane_count,
		.lane_heads = disassembly.lane_heads,
		.assembly_text = disassembly.assembly_text,
	};
	if (!disassembler_print(stdout, bytes, &view, config, use_color)) {
		fputs("Unable to write disassembly to standard output.\n", stderr);
		goto cleanup;
	}
	if (output != NULL &&
		!disassembler_print(output, bytes, &view, config, 0)) {
		fprintf(stderr, "Unable to write disassembly to '%s'.\n", output_path);
		goto cleanup;
	}

	result = EXIT_SUCCESS;

cleanup:
	if (output != NULL && fclose(output) != 0) {
		perror(output_path);
		result = EXIT_FAILURE;
	}
	disassembler_free_result(&disassembly);
	return result;
}

static int disassemble_file(const char *path, const char *output_path, int arch,
							const struct color_config *config)
{
	FILE *file = fopen(path, "rb");
	uint8_t *bytes = NULL;
	long end;
	size_t file_size;
	int result = EXIT_FAILURE;

	if (file == NULL) {
		perror(path);
		return EXIT_FAILURE;
	}
	if (fseek(file, 0, SEEK_END) != 0 || (end = ftell(file)) < 0 ||
		fseek(file, 0, SEEK_SET) != 0) {
		perror("Unable to determine input file size");
		goto cleanup;
	}
	file_size = (size_t)end;
	if (file_size > INT_MAX) {
		fputs("Input file exceeds the decoder's maximum supported size.\n",
			  stderr);
		goto cleanup;
	}

	/* Zero padding lets the decoder inspect a final partial instruction safely.
	 */
	bytes = calloc(file_size + MAX_INSTRUCTION_BYTES, 1);
	if (bytes == NULL) {
		perror("calloc");
		goto cleanup;
	}
	if (fread(bytes, 1, file_size, file) != file_size) {
		if (ferror(file))
			perror("Unable to read input file");
		else
			fputs("Unexpected end of input file.\n", stderr);
		goto cleanup;
	}

	result =
		disassemble_buffer(bytes, file_size, file, output_path, arch, config);

cleanup:
	free(bytes);
	if (fclose(file) != 0) {
		perror(path);
		result = EXIT_FAILURE;
	}
	return result;
}

static int disassemble_hex_bytes(struct byte_buffer *bytes,
								 const char *output_path, int arch,
								 const struct color_config *config)
{
	size_t padded_size;

	if (bytes->length == 0) {
		fputs("No machine-code bytes were provided.\n", stderr);
		return EXIT_FAILURE;
	}
	padded_size = bytes->length + MAX_INSTRUCTION_BYTES;
	if (!reserve_bytes(bytes, padded_size)) {
		perror("realloc");
		return EXIT_FAILURE;
	}
	memset(bytes->data + bytes->length, 0, MAX_INSTRUCTION_BYTES);
	return disassemble_buffer(bytes->data, bytes->length, NULL, output_path,
							  arch, config);
}

static void print_help(const char *program)
{
	printf("Usage: %s [OPTIONS] [BINARY_FILE]\n", program);
	printf("       %s [OPTIONS] --bytes [HEX_BYTES...]\n\n", program);
	puts("Disassemble a binary file, showing machine-code bytes and assembly.");
	puts("Use --bytes to decode hexadecimal bytes from arguments or standard "
		 "input.");
	puts("If BINARY_FILE is omitted, the program asks for its path.");
	puts("--output writes a plain-text copy while keeping terminal output.");
	puts("The left gutter draws arrows between jumps and in-file instruction "
		 "targets.");
	puts(
		"If --arch is omitted, the architecture is requested interactively.\n");
	puts("Options:");
	puts("  -h, --help          Show this help and exit.");
	puts("  -a, --arch ARCH     Select x86 or x86_64 (also accepts 1 or 2).");
	puts("  -o, --output FILE   Export the disassembly to a text file.");
	puts("  -b, --bytes         Read hexadecimal bytes; accepts pairs such as");
	puts("                      '48 89 D8 C3'. With no values, read from "
		 "stdin.");
	puts("  --config FILE       Read color settings from FILE.");
	puts("                      Default: ./disassembler.ini");
	puts("                      X64ID_DISASSEMBLER_CONFIG can also select a "
		 "file.\n");
	puts("Color settings use the [colors] section in the INI file:");
	puts("  enabled             auto | always | never (auto: terminal only)");
	puts("  mnemonic            Ordinary mnemonics (default: cyan)");
	puts("  jump                Jcc and jmp mnemonics (default: yellow)");
	puts("  call                call mnemonics (default: magenta)");
	puts("  return              ret/iret mnemonics (default: green)");
	puts("  data                db fallback output (default: bright_black)");
	puts("  register            Register names (default: bright_cyan)");
	puts("  memory_size         PTR size qualifiers (default: bright_blue)");
	puts("  brackets            [ and ] in memory operands (default: "
		 "bright_yellow)\n");
	puts("Available colors: black, red, green, yellow, blue, magenta, cyan,");
	puts("white, bright_black, bright_red, bright_green, bright_yellow,");
	puts("bright_blue, bright_magenta, bright_cyan, bright_white, default, "
		 "none.");
}

int main(int argc, char **argv)
{
	char input[1024];
	const char *path = NULL;
	const char *output_path = NULL;
	const char *config_path = NULL;
	const char *arch_argument = NULL;
	struct byte_buffer bytes = {0};
	struct hex_parser byte_parser = {
		.bytes = &bytes,
		.high_nibble = UINT8_MAX,
	};
	int bytes_mode = 0;
	int arch = 0;
	int result = EXIT_FAILURE;
	struct color_config config = disassembler_default_colors();

	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
			print_help(argv[0]);
			result = EXIT_SUCCESS;
			goto cleanup;
		}
		if (strcmp(argv[i], "--config") == 0) {
			if (i + 1 >= argc) {
				fputs("--config requires a file path.\n", stderr);
				goto cleanup;
			}
			config_path = argv[++i];
			continue;
		}
		if (strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--bytes") == 0) {
			if (bytes_mode) {
				fputs("--bytes can only be specified once.\n", stderr);
				goto cleanup;
			}
			bytes_mode = 1;
			while (i + 1 < argc && argv[i + 1][0] != '-') {
				if (!parse_hex_argument(&byte_parser, argv[++i])) {
					fputs("Invalid byte argument; use pairs of hexadecimal "
						  "digits.\n",
						  stderr);
					goto cleanup;
				}
			}
			continue;
		}
		if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
			if (i + 1 >= argc || output_path != NULL ||
				argv[i + 1][0] == '\0') {
				fputs("--output requires one non-empty file path.\n", stderr);
				goto cleanup;
			}
			output_path = argv[++i];
			continue;
		}
		if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--arch") == 0) {
			if (i + 1 >= argc || arch_argument != NULL) {
				fputs("--arch requires one architecture value.\n", stderr);
				goto cleanup;
			}
			arch_argument = argv[++i];
			continue;
		}
		if (strncmp(argv[i], "--arch=", 7) == 0) {
			if (arch_argument != NULL || argv[i][7] == '\0') {
				fputs("--arch requires one architecture value.\n", stderr);
				goto cleanup;
			}
			arch_argument = argv[i] + 7;
			continue;
		}
		if (argv[i][0] == '-') {
			fprintf(stderr, "Unknown option: %s\n", argv[i]);
			fprintf(stderr, "Run '%s --help' for usage.\n", argv[0]);
			goto cleanup;
		}
		if (path != NULL) {
			fprintf(stderr, "Only one binary file can be specified.\n");
			goto cleanup;
		}
		path = argv[i];
	}

	if (bytes_mode && path != NULL) {
		fputs("Specify either a binary file or --bytes, not both.\n", stderr);
		goto cleanup;
	}
	if (!bytes_mode && path == NULL) {
		if (!read_line("Binary file path: ", input, sizeof(input))) {
			fputs("Unable to read file path.\n", stderr);
			goto cleanup;
		}
		path = input;
	}

	if (!bytes_mode && *path == '\0') {
		fputs("The file path cannot be empty.\n", stderr);
		goto cleanup;
	}
	if (arch_argument != NULL && !parse_architecture(arch_argument, &arch)) {
		fprintf(stderr, "Unknown architecture '%s'; use x86 or x86_64.\n",
				arch_argument);
		goto cleanup;
	}

	if (!disassembler_load_color_config(&config, config_path))
		goto cleanup;
	if (arch_argument == NULL) {
		while (1) {
			if (!read_line("Architecture (1 = x86, 2 = x86_64): ", input,
						   sizeof(input))) {
				fputs("Unable to read architecture.\n", stderr);
				goto cleanup;
			}
			if (parse_architecture(input, &arch))
				break;
			fputs("Enter x86 (1) or x86_64 (2).\n", stderr);
		}
	}

	if (bytes_mode) {
		if (bytes.length == 0 && !read_hex_input(&bytes))
			goto cleanup;
		result = disassemble_hex_bytes(&bytes, output_path, arch, &config);
	} else {
		result = disassemble_file(path, output_path, arch, &config);
	}

cleanup:
	free(bytes.data);
	return result;
}
