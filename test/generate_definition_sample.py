#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-2.0-only

"""Generate a compact sample binary from the current opcode definitions."""

import argparse
from pathlib import Path

from test_disassembler import encodings, parse_definitions


SEPARATOR = 0xCC


def generate_sample(definitions, arch):
	corpus = bytearray()
	sample_count = 0
	for definition in definitions:
		encoded = next(encodings(definition, arch), None)
		if encoded is None:
			continue
		if sample_count:
			corpus.append(SEPARATOR)
		corpus.extend(encoded)
		sample_count += 1
	return corpus, sample_count


def main():
	parser = argparse.ArgumentParser(description=__doc__)
	parser.add_argument("--arch", choices=("x86", "x86_64"), default="x86_64")
	parser.add_argument(
		"--definitions", type=Path,
		default=Path(__file__).resolve().parents[1] / "src/tools/definitions.txt",
	)
	parser.add_argument("--output-dir", type=Path, default=Path(__file__).resolve().parent)
	args = parser.parse_args()

	args.output_dir.mkdir(parents=True, exist_ok=True)
	definitions = parse_definitions(args.definitions)
	corpus, sample_count = generate_sample(definitions, args.arch)
	binary_path = args.output_dir / f"defined_opcodes_{args.arch}.bin"
	binary_path.write_bytes(corpus)
	print(f"{binary_path}: {len(corpus)} bytes, {sample_count} instruction samples")
	return 0


if __name__ == "__main__":
	raise SystemExit(main())
