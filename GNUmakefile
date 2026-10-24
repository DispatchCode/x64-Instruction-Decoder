# SPDX-License-Identifier: GPL-2.0-only

.DEFAULT_GOAL := all

BUILD_DIR ?= build
CMAKE ?= cmake
CTEST ?= ctest
PYTHON ?= python3
ARCH ?= x86_64
SWEEP_OUTPUT ?= /tmp/opcode-sweep-$(ARCH).txt
SWEEP_MISSING ?= /tmp/opcode-sweep-$(ARCH)-missing.txt
GENERATED_TEST_BINARIES := \
	test/defined_opcodes_x86.bin \
	test/defined_opcodes_x86_64.bin \
	test/opcode_sweep_x86.bin \
	test/opcode_sweep_x86_64.bin

.PHONY: all configure test clean help opcode-sweep opcode-sample inspect-opcode-sweep

all: configure ## Configure and build all configured executables.
	$(CMAKE) --build "$(BUILD_DIR)"

configure:
	$(CMAKE) -S . -B "$(BUILD_DIR)"

help: ## Show documented build targets and executable usage.
	@printf '%s\n' 'Usage: make [target] [VARIABLE=value]' '' 'Targets:'
	@awk 'BEGIN { FS = ":.*##" } /^[a-zA-Z0-9_.-]+:.*##/ { printf "  %-24s %s\n", $$1, $$2 }' "$(firstword $(MAKEFILE_LIST))"
	@printf '%s\n' \
		'' \
		'Executables (make builds them in $(BUILD_DIR); x64id_test is under test/):' \
		'  $(BUILD_DIR)/x64id_disassembler [--arch x86|x86_64] FILE' \
		'      Disassemble a raw binary. Use --help for all CLI options.' \
		'  $(BUILD_DIR)/x64id FILE 1|2' \
		'      Decode a binary with architecture 1=x86 or 2=x86_64.' \
		'  $(BUILD_DIR)/x64id 1|2' \
		'      Run the built-in in-memory decoder demo.' \
		'  $(BUILD_DIR)/test/x64id_test FILE 1|2' \
		'      Run the low-level decoder diagnostic.' \
		'' \
		'Sample files:' \
		'  test/defined_opcodes_x86_64.bin   Samples generated from definitions.txt' \
		'  test/defined_opcodes_x86.bin      32-bit samples generated from definitions.txt' \
		'  Run make opcode-sample to refresh; set ARCH=x86 for the 32-bit file.' \
		'' \
		'ARCH selects the sample/sweep architecture; BUILD_DIR selects the CMake build folder.'

test: configure ## Build the disassembler and run the automated test suite.
	$(CMAKE) --build "$(BUILD_DIR)" --target x64id_disassembler
	$(CTEST) --test-dir "$(BUILD_DIR)" --output-on-failure

opcode-sweep: ## Generate exhaustive x86 and x86_64 opcode sweep binaries.
	$(PYTHON) test/generate_opcode_sweep.py

opcode-sample: ## Generate one representative binary sample from definitions.txt.
	$(PYTHON) test/generate_definition_sample.py --arch "$(ARCH)"

inspect-opcode-sweep: configure ## Disassemble a sweep and list unique unrecognized forms.
	@case "$(ARCH)" in x86|x86_64) ;; *) \
		echo "ARCH must be x86 or x86_64." >&2; exit 2 ;; \
	esac
	$(PYTHON) test/generate_opcode_sweep.py
	$(CMAKE) --build "$(BUILD_DIR)" --target x64id_disassembler
	"$(BUILD_DIR)/x64id_disassembler" --arch "$(ARCH)" \
		--output "$(SWEEP_OUTPUT)" "test/opcode_sweep_$(ARCH).bin" >/dev/null
	$(PYTHON) test/summarize_opcode_sweep.py --arch "$(ARCH)" \
		--disassembly "$(SWEEP_OUTPUT)" \
		--definitions "src/tools/definitions.txt" \
		--output "$(SWEEP_MISSING)"
	@cat "$(SWEEP_MISSING)"
	@echo "Full disassembly saved to $(SWEEP_OUTPUT)"

clean: ## Remove build outputs and generated test binaries.
	@if [ -f "$(BUILD_DIR)/CMakeCache.txt" ]; then \
		$(CMAKE) --build "$(BUILD_DIR)" --target clean; \
	elif [ "$(BUILD_DIR)" = "build" ] && [ -f CMakeCache.txt ]; then \
		$(CMAKE) --build . --target clean; \
	else \
		echo "Nothing to clean in $(BUILD_DIR)."; \
	fi
	$(RM) $(GENERATED_TEST_BINARIES)
