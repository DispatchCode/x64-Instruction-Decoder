# Disassembler tests

The old checked-in `.bin` files are useful samples, but are not an exhaustive
or self-checking suite. `test_disassembler.py` builds temporary raw byte streams
from `src/tools/definitions.txt` and exercises the actual `x64id_disassembler`
CLI in both `x86` and `x86_64` modes.

For each declared opcode, the suite checks the mnemonic and instruction bytes.
ModRM handlers are exercised with all 8 `reg` values (or the declared `/digit`),
all 8 `r/m` values, and register, base-memory, disp8, and disp32 forms. SIB is
included for memory forms. Immediate, relative-branch, prefix, and opcode-range
forms are generated from each definition. The corpus lives in a temporary
directory and is removed after the run.

Adding an opcode or range with an existing handler requires editing only
`definitions.txt`: the suite discovers it and generates its cases automatically.
The test runner checks handler names up front, so a new operand-layout handler
cannot silently be mistaken for a no-operand instruction. When a genuinely new
encoding layout is added to the decoder, add one reusable generator rule for
that handler; individual opcode definitions still need no test-code changes.

A separate regression case feeds an unsupported two-byte opcode followed by a
known `nop`. It checks that both unsupported bytes appear in a `db` row and
that decoding resumes at the following instruction. This covers the raw-binary
CLI contract; these tests do not interpret ELF or PE files.

From the project root, run:

```sh
make test
```

The root `GNUmakefile` creates `build/` as needed, builds the disassembler, and
runs CTest. Use `make clean` to remove build outputs and generated sample/sweep
binaries; checked-in test fixtures are preserved. Set `BUILD_DIR` to choose
another build folder, for example `make test BUILD_DIR=some/path`.

The test uses only Python's standard library. The generated matrix covers the
opcodes present in `definitions.txt`; it does not claim full ISA coverage or
replace comparison against independent decoders. This follows the layered
approach used by mature decoders such as [iced](https://github.com/icedland/iced):
systematic instruction coverage, explicit regression cases, and independent
cross-checking as a separate validation layer.

## Opcode sweep binaries

To generate the sweep binaries, run `make opcode-sweep`. To generate them,
build the CLI, and save the x86_64 disassembly in one step, run:

```sh
make inspect-opcode-sweep
```

The target prints a deduplicated list of opcode forms whose slots were
disassembled as `db`. It groups prefix and vector-length variants by opcode
map, opcode byte, and encoding family, and gives an example byte sequence and
the number of affected variants. Definitions restricted to another architecture
are excluded, so `PUSH ES` is not reported as missing by the x86_64 sweep. The
report is also saved to
`/tmp/opcode-sweep-x86_64-missing.txt`; the full output is saved to
`/tmp/opcode-sweep-x86_64.txt`. Choose the 32-bit decoder with
`make inspect-opcode-sweep ARCH=x86`; set `SWEEP_OUTPUT` or `SWEEP_MISSING` to
choose other paths. The target handles generation, building, disassembly, and
the summary itself.

## Definition sample binaries

To create a compact binary with one representative encoding for every opcode
currently declared in `definitions.txt`, run:

```sh
make opcode-sample
./build/x64id_disassembler --arch x86_64 test/defined_opcodes_x86_64.bin
```

Use `make opcode-sample ARCH=x86` and
`./build/x64id_disassembler --arch x86 test/defined_opcodes_x86.bin` for the
32-bit decoder. The generator expands opcode ranges and separates samples with
`CC` (`int3`) so each one is easy to spot in the output. Run `make opcode-sample`
again after editing `definitions.txt` to refresh the sample binary.

The generated `test/opcode_sweep_x86.bin` and `test/opcode_sweep_x86_64.bin`
can also be passed directly to the disassembler. Each
binary tests all byte values in the one-byte, `0F`, `0F 38`, and `0F 3A` maps
with no prefix and with `66`, `F2`, or `F3`, plus VEX map, `pp`, vector-length,
and opcode-byte combinations. Each case occupies a 16-byte slot. `CC` bytes
pad the slots and serve as immediate/displacement data where an encoding
consumes them, so the next case remains at a predictable offset. The missing
opcode summary maps offsets to cases directly from the generator in memory.

In x86_64 mode, legacy `C4` and `C5` cases are represented by `NOP` slots and
covered by valid VEX cases. Treating those bytes as legacy instructions would
create malformed VEX prefixes and can crash the current decoder.

The sweep uses one representative ModRM value per opcode and is intended to
find missing or incorrectly dispatched opcode families. The automated matrix
above covers the broader ModRM variations for opcodes already declared in
`definitions.txt`.
