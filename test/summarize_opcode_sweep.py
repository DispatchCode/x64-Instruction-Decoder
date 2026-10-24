#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-2.0-only

"""List unique opcode forms whose sweep slot starts with a `db` row."""

import argparse
import re
from collections import defaultdict
from pathlib import Path

from generate_opcode_sweep import generate_sweep


OFFSET_RE = re.compile(r"^\s*([0-9a-fA-F]+)\s+")
DATA_RE = re.compile(r"\bdb\b")
ARCH_RESTRICTED_HANDLERS = {"push": "x86"}


def restricted_opcodes(definitions_path, arch):
	if arch == "x86":
		return set()

	restricted = set()
	with definitions_path.open(encoding="utf-8") as definitions:
		for line in definitions:
			content = line.split("#", 1)[0].strip()
			if not content:
				continue
			fields = [field.strip() for field in content.split("|")]
			if len(fields) != 4 or ARCH_RESTRICTED_HANDLERS.get(fields[3]) != "x86":
				continue
			opcode = fields[1].split("/", 1)[0]
			if ":" in opcode:
				start, end = (int(value, 16) for value in opcode.split(":", 1))
				opcodes = range(start, end + 1)
			else:
				opcodes = (int(opcode, 16),)
			for value in opcodes:
				if value <= 0xFF:
					restricted.add(f"{value:02X}")
	return restricted


def missing_cases(disassembly_path, cases, definitions_path, arch):
	data_offsets = set()
	restricted = restricted_opcodes(definitions_path, arch)
	with disassembly_path.open(encoding="utf-8") as disassembly:
		for line in disassembly:
			match = OFFSET_RE.match(line)
			if match and DATA_RE.search(line):
				data_offsets.add(int(match.group(1), 16))

	missing = defaultdict(list)
	for case in cases:
		if case["status"] != "tested":
			continue
		if (case["family"] == "legacy" and
			case["opcode_map"] == "one_byte" and
			case["opcode"] in restricted):
			continue
		if int(case["offset"], 16) in data_offsets:
			family = "vex" if case["family"].startswith("vex_") else case["family"]
			key = (family, case["opcode_map"], case["opcode"])
			missing[key].append(case)
	return missing


def main():
	parser = argparse.ArgumentParser(description=__doc__)
	parser.add_argument("--arch", choices=("x86", "x86_64"), required=True)
	parser.add_argument("--disassembly", type=Path, required=True)
	parser.add_argument("--definitions", type=Path, required=True)
	parser.add_argument("--output", type=Path, required=True)
	args = parser.parse_args()

	_, cases = generate_sweep(args.arch)
	missing = missing_cases(args.disassembly, cases, args.definitions, args.arch)
	with args.output.open("w", encoding="utf-8") as report:
		report.write(f"Unrecognized opcode forms in {args.arch}:\n")
		if not missing:
			report.write("No `db` rows matched the tested opcode slots.\n")
		else:
			for (family, opcode_map, opcode), cases in sorted(missing.items()):
				example = cases[0]["encoding"]
				report.write(
					f"{family:8} {opcode_map:5} {opcode}  "
					f"({len(cases)} variant(s); example: {example})\n"
				)
			report.write(f"\n{len(missing)} unique opcode form(s).\n")
	print(f"Unique missing-opcode report saved to {args.output}")
	return 0


if __name__ == "__main__":
	raise SystemExit(main())
