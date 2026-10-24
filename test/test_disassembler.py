#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-2.0-only

"""End-to-end opcode/encoding coverage for the raw-binary disassembler."""

from dataclasses import dataclass
import re
import subprocess
import sys
import tempfile
from pathlib import Path
from typing import Optional


@dataclass(frozen=True)
class Definition:
	prefixes: tuple
	opcode: tuple
	extension: Optional[int]
	mnemonic: str
	handler: str
	line: int


def parse_definitions(path):
	definitions = []
	for line_number, line in enumerate(path.read_text(encoding="utf-8").splitlines(), 1):
		content = line.split("#", 1)[0].strip()
		if not content:
			continue
		fields = [field.strip() for field in content.split("|")]
		if len(fields) != 4:
			raise AssertionError(f"definitions.txt:{line_number}: expected four fields")
		prefix, opcode_text, mnemonic, handler = fields
		prefixes = () if prefix in ("", "00", "0x00") else tuple(
			int(value, 16) for value in re.findall(r"(?:0x)?([0-9a-fA-F]{2})", prefix)
		)
		extension = None
		if "/" in opcode_text:
			opcode_text, extension_text = opcode_text.split("/", 1)
			extension = int(extension_text, 10)
		if ":" in opcode_text:
			start, end = (int(value, 16) for value in opcode_text.split(":", 1))
			values = range(start, end + 1)
		else:
			values = (int(opcode_text, 16),)
		for value in values:
			width = max(1, (value.bit_length() + 7) // 8)
			opcode = tuple(value.to_bytes(width, "big"))
			definitions.append(Definition(prefixes, opcode, extension, mnemonic,
									  handler, line_number))
	return definitions


def modrm_bytes(mod, reg, rm):
	result = [((mod & 3) << 6) | ((reg & 7) << 3) | (rm & 7)]
	if mod == 3:
		return result
	if rm == 4:
		# SIB: scale 1, no index, base RSP. This also exercises SIB parsing.
		result.append(0x24)
		if mod == 1:
			result.append(0)
		elif mod == 2:
			result.extend((0, 0, 0, 0))
		return result
	if mod == 0 and rm == 5:
		return result + [0, 0, 0, 0]
	if mod == 1:
		return result + [0]
	if mod == 2:
		return result + [0, 0, 0, 0]
	return result


def immediate_bytes(handler, prefixes, arch, opcode):
	if handler in ("Eb_Ib", "Al_Ib", "Reg8_In_Opcode_Ib"):
		return [0]
	if handler in ("Ev_Iz", "Al_Iz", "Reg_In_Opcode_Iz", "Gv_Ev_Iz"):
		if opcode[-1] in (0x83, 0xC1, 0xBA):
			return [0]
		if handler == "Ev_Iz" and opcode[-1] in (0xF7,):
			return [0] * (2 if 0x66 in prefixes else 4)
		# These encodings use an operand-size immediate, except REX.W forms,
		# which still carry a sign-extended 32-bit immediate. The generated
		# cases do not add REX.W; 66 selects the 16-bit form.
		return [0] * (2 if 0x66 in prefixes else 4)
	if handler in ("Gv_Ev_Ib", "Ev_Gv_Ib"):
		return [0]
	if handler == "push_imm":
		return [0] * (1 if opcode[-1] == 0x6A else 2 if 0x66 in prefixes else 4)
	if handler in ("int_imm", "ret_imm"):
		return [0] * (1 if handler == "int_imm" else 2)
	if handler == "enter":
		return [0, 0, 0]
	if handler == "aam_aad":
		return [] if arch == "x86_64" else [0]
	if handler == "op82":
		return [] if arch == "x86_64" else [0]
	if handler == "moffs":
		return [0] * (4 if arch == "x86" and 0x67 not in prefixes else
					2 if arch == "x86" else 4 if 0x67 in prefixes else 8)
	if handler == "far_pointer":
		return [] if arch == "x86_64" else [0] * (4 if 0x66 in prefixes else 6)
	if handler == "io" and opcode[-1] <= 0xE7:
		return [0]
	if handler == "Jb":
		return [0]
	if handler == "Jz":
		return [0] * (4 if arch == "x86_64" else
					2 if 0x66 in prefixes else 4)
	return []


MODRM_HANDLERS = {
	"Eb_Gb", "Gb_Eb", "Ev_Gv", "Gv_Ev", "Eb_Ib", "Ev_Iz", "Ew", "M",
	"Gv_Ew", "Gv_Eb", "Gv_Ev_Iz", "Gv_Ev_Ib", "Ev_Gv_Ib",
	"Ev_Gv_CL", "Eb", "Ev", "Ev64", "Lea", "pop_Ev", "segment_move",
	"arpl_movsxd", "special_move", "shift_one", "shift_cl", "far_load",
}
HANDLERS_WITHOUT_MODRM = {
	"Al_Ib", "Al_Iz", "Jb", "Jz", "None", "Reg8_In_Opcode_Ib",
	"Reg_In_Opcode", "Reg_In_Opcode_Iz", "push", "segment_stack",
	"x86_only", "aam_aad", "push_imm", "op82", "integer_alias",
	"far_pointer", "ret_imm", "int_imm", "enter", "xchg_accumulator",
	"moffs", "string", "io", "jrcxz", "bswap", "endbr", "nop",
}
KNOWN_HANDLERS = MODRM_HANDLERS | HANDLERS_WITHOUT_MODRM
X86_ONLY_HANDLERS = {"push"}


def encodings(definition, arch):
	# In x86-64, 40..4f are REX prefixes, not INC/DEC opcodes. Their
	# opcode-register meanings are covered by the x86 corpus.
	if arch == "x86_64" and len(definition.opcode) == 1 and \
			0x40 <= definition.opcode[0] <= 0x4f:
		return
	if arch == "x86_64" and definition.handler == "far_load":
		return
	base = list(definition.prefixes + definition.opcode)
	if definition.handler == "endbr":
		yield bytes(base + [0xFA])
		yield bytes(base + [0xFB])
		return
	needs_modrm = definition.handler in MODRM_HANDLERS or \
		definition.extension is not None
	if needs_modrm:
		if definition.handler in ("Ew", "M", "far_load"):
			mods = (0, 1, 2)
		elif definition.handler == "special_move":
			mods = (3,)
		else:
			mods = (0, 1, 2, 3)
		if definition.extension is not None:
			regs = (definition.extension,)
		elif definition.handler == "segment_move":
			regs = (0, 2, 3, 4, 5) if definition.opcode[-1] == 0x8E else range(6)
		else:
			regs = range(8)
		for mod in mods:
			for reg in regs:
				for rm in range(8):
					encoded = base + modrm_bytes(mod, reg, rm)
					encoded += immediate_bytes(definition.handler,
										  definition.prefixes, arch,
										  definition.opcode)
					if len(encoded) <= 15:
						yield bytes(encoded)
	else:
		encoded = base + immediate_bytes(definition.handler,
									  definition.prefixes, arch,
									  definition.opcode)
		if len(encoded) <= 15:
			yield bytes(encoded)


def run_disassembler(executable, binary, arch):
	return subprocess.run(
		[executable, "--arch", arch, "--config", "/dev/null", str(binary)],
		check=False, capture_output=True, text=True,
	)


def parse_rows(output):
	rows = []
	for line in output.splitlines():
		match = re.match(r"^([0-9a-fA-F]{8})  ", line)
		if not match:
			continue
		offset = int(match.group(1), 16)
		byte_column = line[10:55]
		machine_bytes = bytes(int(value, 16) for value in
						  re.findall(r"(?<![0-9A-F])[0-9A-F]{2}(?![0-9A-F])",
									 byte_column))
		assembly = line[57:]
		mnemonic_match = re.search(r"(?<![A-Za-z0-9_])[A-Za-z][A-Za-z0-9_.]*",
								   assembly)
		mnemonic = mnemonic_match.group(0).lower() if mnemonic_match else ""
		rows.append((offset, machine_bytes, mnemonic))
	return rows


def expected_mnemonic_for(definition, encoded, arch):
	handler = definition.handler
	opcode = definition.opcode[-1]
	if arch == "x86_64":
		if handler in {"push", "x86_only", "aam_aad", "far_pointer", "op82"}:
			return "db"
		if handler == "segment_stack" and not (
				len(definition.opcode) == 2 and opcode in (0xA0, 0xA1, 0xA8, 0xA9)):
			return "db"
	if handler == "io":
		return "in" if opcode in (0xE4, 0xE5, 0xEC, 0xED) else "out"
	if handler == "integer_alias":
		if opcode == 0x98:
			return "cbw" if 0x66 in definition.prefixes else "cwde"
		return "cwd" if 0x66 in definition.prefixes else "cdq"
	if handler == "jrcxz":
		if arch == "x86_64":
			return "jecxz" if 0x67 in definition.prefixes else "jrcxz"
		return "jcxz" if 0x67 in definition.prefixes else "jecxz"
	if handler == "endbr":
		return "endbr64" if encoded[-1] == 0xFA else "endbr32"
	if handler == "string":
		if opcode == 0x6C:
			return "insb"
		if opcode == 0x6D:
			return "insw" if 0x66 in definition.prefixes else "insd"
		if opcode == 0x6E:
			return "outsb"
		if opcode == 0x6F:
			return "outsw" if 0x66 in definition.prefixes else "outsd"
		width = "w" if 0x66 in definition.prefixes else "d"
		return {
			0xA4: "movsb", 0xA5: "movs" + width,
			0xA6: "cmpsb", 0xA7: "cmps" + width,
			0xAA: "stosb", 0xAB: "stos" + width,
			0xAC: "lodsb", 0xAD: "lods" + width,
			0xAE: "scasb", 0xAF: "scas" + width,
		}[opcode]
	return definition.mnemonic.lower()


def fail(message):
	print(f"FAIL: {message}", file=sys.stderr)
	return 1


def main():
	if len(sys.argv) != 3:
		return fail("usage: test_disassembler.py DISASSEMBLER DEFINITIONS")
	executable = str(Path(sys.argv[1]).resolve())
	definitions_path = Path(sys.argv[2])
	definitions = parse_definitions(definitions_path)
	if not definitions:
		return fail(f"no opcode definitions found in {definitions_path}")
	unknown_handlers = sorted({definition.handler for definition in definitions} -
						  KNOWN_HANDLERS)
	if unknown_handlers:
		return fail("no generic test encoding rule for handler(s): " +
					", ".join(unknown_handlers) +
					"; add one handler rule before adding definitions that use it")

	issues = []
	with tempfile.TemporaryDirectory(prefix="x64id-tests-") as temp_dir:
		temp = Path(temp_dir)
		for arch in ("x86", "x86_64"):
			corpus = bytearray()
			expected = []
			for definition in definitions:
				for encoded in encodings(definition, arch):
					if not encoded:
						continue
					expected_mnemonic = expected_mnemonic_for(
						definition, encoded, arch)
					expected.append((len(corpus), encoded, expected_mnemonic,
								 definition.line, definition.handler))
					corpus.extend(encoded)
			binary = temp / f"coverage-{arch}.bin"
			binary.write_bytes(corpus)
			result = run_disassembler(executable, binary, arch)
			if result.returncode != 0:
				return fail(f"{arch} CLI exited {result.returncode}: {result.stderr.strip()}")
			rows = parse_rows(result.stdout)
			by_offset = {row[0]: row for row in rows}
			for offset, encoded, mnemonic, source_line, handler in expected:
				row = by_offset.get(offset)
				if row is None:
					issues.append(f"{arch} definitions.txt:{source_line} {mnemonic}/{handler}: "
							  f"no instruction row at 0x{offset:x}")
					continue
				if row[1] != encoded:
					issues.append(f"{arch} definitions.txt:{source_line} {mnemonic}/{handler}: "
							  f"expected bytes {encoded.hex(' ').upper()}, "
							  f"got {row[1].hex(' ').upper()} at 0x{offset:x}")
					continue
				if row[2] != mnemonic.lower():
					issues.append(f"{arch} definitions.txt:{source_line} {mnemonic}/{handler}: "
							  f"expected mnemonic {mnemonic}, got {row[2]!r} "
							  f"for {encoded.hex(' ').upper()}")
			if len(rows) != len(expected):
				issues.append(f"{arch} corpus produced {len(rows)} rows for "
							  f"{len(expected)} generated instructions")
			if not any(issue.startswith(arch + " ") for issue in issues):
				print(f"PASS {arch}: {len(expected)} definition/encoding cases")
			else:
				print(f"FAIL {arch}: {len(expected)} definition/encoding cases")

		# VEX dispatch is maintained outside definitions.txt, so keep a small
		# explicit matrix for the currently implemented VEX mnemonics and both
		# vector lengths, including the reported SIB/displacement regression.
		vex_cases = (
			(bytes.fromhex("C5 FA 12 C0"), "vmovsldup"),
			(bytes.fromhex("C5 FE 12 C0"), "vmovsldup"),
			(bytes.fromhex("C5 FB 12 C0"), "vmovddup"),
			(bytes.fromhex("C5 FE 16 C0"), "vmovshdup"),
			(bytes.fromhex("C5 FE 12 0C AD 00 10 00 00"), "vmovsldup"),
		)
		vex_corpus = b"".join(encoded for encoded, _ in vex_cases)
		vex_binary = temp / "vex-regressions.bin"
		vex_binary.write_bytes(vex_corpus)
		result = run_disassembler(executable, vex_binary, "x86_64")
		if result.returncode != 0:
			issues.append(f"VEX regression CLI exited {result.returncode}: "
					  f"{result.stderr.strip()}")
		else:
			rows = parse_rows(result.stdout)
			offset = 0
			for encoded, mnemonic in vex_cases:
				row = next((candidate for candidate in rows
							if candidate[0] == offset), None)
				if row is None or row[1] != encoded or row[2] != mnemonic:
					issues.append(f"VEX case {encoded.hex(' ').upper()}: expected "
							  f"{mnemonic} and full bytes, got {row!r}")
				offset += len(encoded)
			if not any(issue.startswith("VEX case") for issue in issues):
				print(f"PASS VEX regressions: {len(vex_cases)} cases")

		# An unsupported two-byte opcode must be printed as data, and the next
		# valid instruction must still be decoded. Keep this separate from the
		# generated supported-opcode matrix so it also documents fallback policy.
		unknown = temp / "unknown-followed-by-known.bin"
		unknown.write_bytes(bytes((0x0f, 0x0c, 0x90)))
		result = run_disassembler(executable, unknown, "x86_64")
		if result.returncode != 0:
			return fail(f"unknown-opcode CLI exited {result.returncode}: "
						+ result.stderr.strip())
		rows = parse_rows(result.stdout)
		if not rows or rows[0][0] != 0 or rows[0][1] != b"\x0f\x0c" or rows[0][2] != "db":
			issues.append("unsupported bytes 0F 0C were not preserved together in a db row")
		if not rows or rows[-1][0] != 2 or rows[-1][1] != b"\x90" or rows[-1][2] != "nop":
			issues.append("decoder did not resume at the NOP after unsupported bytes 0F 0C")
		if not any("unsupported" in issue and "0F 0C" in issue for issue in issues):
			print("PASS unknown-opcode fallback: all bytes shown and decoding resumes")

	if issues:
		print(f"\n{len(issues)} issue(s); showing up to 25:", file=sys.stderr)
		for issue in issues[:25]:
			print(f"- {issue}", file=sys.stderr)
		if len(issues) > 25:
			print(f"- ... {len(issues) - 25} more", file=sys.stderr)
		return 1
	return 0


if __name__ == "__main__":
	sys.exit(main())
