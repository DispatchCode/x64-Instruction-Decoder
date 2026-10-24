#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-2.0-only

"""Generate fixed-slot opcode sweeps and offset maps for the CLI."""

import argparse
from pathlib import Path


SLOT_SIZE = 16
FILL_BYTE = 0xCC
LEGACY_PREFIXES = ((), (0x66,), (0xF2,), (0xF3,))
LEGACY_MAPS = (
	("one_byte", ()),
	("0f", (0x0F,)),
	("0f38", (0x0F, 0x38)),
	("0f3a", (0x0F, 0x3A)),
)


def append_case(corpus, cases, family, prefix, opcode_map, opcode, encoding,
				status="tested"):
	if len(encoding) >= SLOT_SIZE:
		raise ValueError(f"case exceeds {SLOT_SIZE}-byte slot: {encoding.hex()}")

	offset = len(corpus)
	corpus.extend(encoding)
	corpus.extend(bytes((FILL_BYTE,)) * (SLOT_SIZE - len(encoding)))
	cases.append({
		"offset": f"0x{offset:08X}",
		"family": family,
		"legacy_prefix": " ".join(f"{byte:02X}" for byte in prefix),
		"opcode_map": opcode_map,
		"opcode": f"{opcode:02X}",
		"encoding": encoding.hex(" ").upper(),
		"status": status,
	})


def generate_sweep(arch):
	corpus = bytearray()
	cases = []

	for prefix in LEGACY_PREFIXES:
		for map_name, map_bytes in LEGACY_MAPS:
			for opcode in range(256):
				if (arch == "x86_64" and map_name == "one_byte" and
					opcode in (0xC4, 0xC5)):
					# In long mode C4/C5 are VEX prefixes. Test those in the
					# dedicated valid VEX sweep below, not as malformed legacy forms.
					append_case(corpus, cases, "legacy_excluded", prefix,
							   map_name, opcode, bytes((0x90,)),
							   status="covered by VEX sweep")
					continue
				encoding = bytes(prefix + map_bytes + (opcode, 0x00))
				append_case(corpus, cases, "legacy", prefix, map_name,
						   opcode, encoding)

	# VEX map, pp, and vector-length selectors. Use a memory ModRM form as a
	# generic sample; the fixed CC padding supplies any required displacement
	# or immediate bytes and keeps each following case on a 16-byte boundary.
	for map_number in range(1, 4):
		for pp in range(4):
			for vector_length in range(2):
				vex_c5 = 0xF8 | (vector_length << 2) | pp
				vex_c4_second = 0xE0 | map_number
				vex_c4_third = 0x78 | (vector_length << 2) | pp
				for opcode in range(256):
					if map_number == 1:
						encoding = bytes((0xC5, vex_c5, opcode, 0x00))
						append_case(corpus, cases, "vex_c5", (), "map1",
								   opcode, encoding)
					encoding = bytes((0xC4, vex_c4_second, vex_c4_third,
								  opcode, 0x00))
					append_case(corpus, cases, "vex_c4", (),
							   f"map{map_number}", opcode, encoding)

	return corpus, cases


def write_sweep(output_dir, arch, corpus):
	binary_path = output_dir / f"opcode_sweep_{arch}.bin"
	binary_path.write_bytes(corpus)
	print(f"{binary_path}: {len(corpus)} bytes")


def main():
	parser = argparse.ArgumentParser(description=__doc__)
	parser.add_argument(
		"--output-dir", type=Path, default=Path(__file__).resolve().parent,
		help="directory for the generated binaries",
	)
	args = parser.parse_args()
	args.output_dir.mkdir(parents=True, exist_ok=True)
	for arch in ("x86", "x86_64"):
		corpus, cases = generate_sweep(arch)
		write_sweep(args.output_dir, arch, corpus)
		print(f"{len(cases)} opcode cases for {arch}")
	return 0


if __name__ == "__main__":
	raise SystemExit(main())
