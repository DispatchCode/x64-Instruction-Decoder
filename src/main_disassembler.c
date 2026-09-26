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
	while (isspace((unsigned char)*end))
		end++;

	if (errno != 0 || end == input || *end != '\0' ||
		(value != X86 && value != X64))
		return 0;

	*arch = (int)value;
	return 1;
}

static int disassemble_file(const char *path, const char *output_path, int arch,
							const struct color_config *config)
{
	FILE *file = fopen(path, "rb");
	FILE *output = NULL;
	unsigned char *bytes = NULL;
	struct disassembler_result disassembly = {0};
	size_t file_size;
	long end;
	int result = EXIT_FAILURE;
	int use_color = disassembler_colors_enabled(config);

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
	if (file_size > (size_t)-1 - MAX_INSTRUCTION_BYTES) {
		fputs("Input file is too large.\n", stderr);
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

	if (!disassembler_decode_buffer(bytes, file_size, arch, &disassembly)) {
		fputs("Unable to build the control-flow map.\n", stderr);
		goto cleanup;
	}
	if (output_path != NULL) {
		struct stat input_stat;
		struct stat output_stat;

		if (fstat(fileno(file), &input_stat) == 0 &&
			stat(output_path, &output_stat) == 0 &&
			input_stat.st_dev == output_stat.st_dev &&
			input_stat.st_ino == output_stat.st_ino) {
			fputs("Output file must differ from the input binary.\n", stderr);
			goto cleanup;
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
	free(bytes);
	fclose(file);
	return result;
}

static void print_help(const char *program)
{
	printf("Usage: %s [OPTIONS] [BINARY_FILE]\n\n", program);
	puts("Disassemble a binary file, showing machine-code bytes and assembly.");
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
	int arch = 0;
	struct color_config config = disassembler_default_colors();

	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
			print_help(argv[0]);
			return EXIT_SUCCESS;
		}
		if (strcmp(argv[i], "--config") == 0) {
			if (i + 1 >= argc) {
				fputs("--config requires a file path.\n", stderr);
				return EXIT_FAILURE;
			}
			config_path = argv[++i];
			continue;
		}
		if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
			if (i + 1 >= argc || output_path != NULL ||
				argv[i + 1][0] == '\0') {
				fputs("--output requires one non-empty file path.\n", stderr);
				return EXIT_FAILURE;
			}
			output_path = argv[++i];
			continue;
		}
		if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--arch") == 0) {
			if (i + 1 >= argc || arch_argument != NULL) {
				fputs("--arch requires one architecture value.\n", stderr);
				return EXIT_FAILURE;
			}
			arch_argument = argv[++i];
			continue;
		}
		if (strncmp(argv[i], "--arch=", 7) == 0) {
			if (arch_argument != NULL || argv[i][7] == '\0') {
				fputs("--arch requires one architecture value.\n", stderr);
				return EXIT_FAILURE;
			}
			arch_argument = argv[i] + 7;
			continue;
		}
		if (argv[i][0] == '-') {
			fprintf(stderr, "Unknown option: %s\n", argv[i]);
			fprintf(stderr, "Run '%s --help' for usage.\n", argv[0]);
			return EXIT_FAILURE;
		}
		if (path != NULL) {
			fprintf(stderr, "Only one binary file can be specified.\n");
			return EXIT_FAILURE;
		}
		path = argv[i];
	}

	if (path == NULL) {
		if (!read_line("Binary file path: ", input, sizeof(input))) {
			fputs("Unable to read file path.\n", stderr);
			return EXIT_FAILURE;
		}
		path = input;
	}

	if (*path == '\0') {
		fputs("The file path cannot be empty.\n", stderr);
		return EXIT_FAILURE;
	}
	if (arch_argument != NULL && !parse_architecture(arch_argument, &arch)) {
		fprintf(stderr, "Unknown architecture '%s'; use x86 or x86_64.\n",
				arch_argument);
		return EXIT_FAILURE;
	}

	if (!disassembler_load_color_config(&config, config_path))
		return EXIT_FAILURE;
	if (arch_argument == NULL) {
		while (1) {
			if (!read_line("Architecture (1 = x86, 2 = x86_64): ", input,
						   sizeof(input))) {
				fputs("Unable to read architecture.\n", stderr);
				return EXIT_FAILURE;
			}
			if (parse_architecture(input, &arch))
				break;
			fputs("Enter x86 (1) or x86_64 (2).\n", stderr);
		}
	}

	return disassemble_file(path, output_path, arch, &config);
}
