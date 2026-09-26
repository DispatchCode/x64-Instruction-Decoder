#!/usr/bin/env python3
"""Generate the opcode dispatch included by disasm.c from definitions.txt."""

from pathlib import Path
import re
import sys


TOOLS_DIR = Path(__file__).resolve().parent
INPUT_FILE = TOOLS_DIR / "definitions.txt"
OUTPUT_FILE = TOOLS_DIR / "generated_opcodes.h"
IDENTIFIER = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")
PREFIX_FLAGS = {"66": "OS", "F2": "REPNE", "F3": "REPE"}


def parse_prefix(value, line_number):
    value = value.strip().upper()
    if value in ("", "00", "0X00"):
        return ()

    tokens = re.findall(r"(?:0X)?[0-9A-F]{2}", value)
    if not tokens or re.sub(r"(?:0X)?[0-9A-F]{2}|[\s,+]+", "", value):
        raise ValueError(f"line {line_number}: invalid prefix {value!r}")

    prefixes = tuple(token.removeprefix("0X") for token in tokens)
    unsupported = set(prefixes) - PREFIX_FLAGS.keys()
    if unsupported:
        bad = ", ".join(sorted(unsupported))
        raise ValueError(f"line {line_number}: unsupported mandatory prefix(es): {bad}")
    if len(set(prefixes)) != len(prefixes):
        raise ValueError(f"line {line_number}: duplicate mandatory prefix")
    return prefixes


def parse_opcode(opcode_text, line_number):
    extension = None
    if "/" in opcode_text:
        opcode_text, extension_text = opcode_text.split("/", 1)
        try:
            extension = int(extension_text)
        except ValueError as error:
            raise ValueError(f"line {line_number}: invalid ModRM extension") from error
        if not 0 <= extension <= 7:
            raise ValueError(f"line {line_number}: ModRM extension must be 0..7")

    if ":" in opcode_text:
        start_text, end_text = opcode_text.split(":", 1)
        try:
            start, end = int(start_text, 16), int(end_text, 16)
        except ValueError as error:
            raise ValueError(f"line {line_number}: invalid opcode range") from error
        if end < start:
            raise ValueError(f"line {line_number}: opcode range is reversed")
        values = range(start, end + 1)
    else:
        try:
            values = (int(opcode_text, 16),)
        except ValueError as error:
            raise ValueError(f"line {line_number}: invalid opcode {opcode_text!r}") from error

    entries = []
    for value in values:
        if not 0 <= value <= 0xFFFFFF:
            raise ValueError(f"line {line_number}: opcode must fit in 1..3 bytes")
        width = 1 if value <= 0xFF else 2 if value <= 0xFFFF else 3
        encoded = tuple((value >> shift) & 0xFF for shift in range((width - 1) * 8, -1, -8))
        entries.append((encoded, extension))
    return entries


def parse_definitions(path):
    entries = []
    seen = set()
    with path.open(encoding="utf-8") as definitions:
        for line_number, line in enumerate(definitions, start=1):
            raw = line.split("#", 1)[0].strip()
            if not raw:
                continue

            fields = [field.strip() for field in raw.split("|")]
            if len(fields) != 4:
                raise ValueError(f"line {line_number}: expected prefix | opcode | mnemonic | handler")
            prefix_text, opcode_text, mnemonic, handler = fields
            prefixes = parse_prefix(prefix_text, line_number)
            if not IDENTIFIER.fullmatch(mnemonic) or not IDENTIFIER.fullmatch(handler):
                raise ValueError(f"line {line_number}: mnemonic and handler must be identifiers")

            for opcode, extension in parse_opcode(opcode_text, line_number):
                key = (opcode, extension, prefixes)
                if key in seen:
                    raise ValueError(f"line {line_number}: duplicate opcode/prefix definition")
                seen.add(key)
                entries.append({
                    "opcode": opcode,
                    "extension": extension,
                    "prefixes": prefixes,
                    "mnemonic": mnemonic,
                    "handler": handler,
                    "line": line_number,
                })
    return entries


def build_tree(entries):
    root = {}
    for entry in entries:
        node = root
        for index, byte in enumerate(entry["opcode"]):
            child = node.setdefault(byte, {"entries": [], "children": {}})
            if index == len(entry["opcode"]) - 1:
                child["entries"].append(entry)
            else:
                node = child["children"]
    return root


def prefix_condition(prefixes):
    if not prefixes:
        return None
    return " && ".join(f"(instr->set_prefix & {PREFIX_FLAGS[prefix]})" for prefix in prefixes)


def emit_instruction(entry, indent):
    return [
        f'{indent}append_mnemonic(instr, "{entry["mnemonic"]}");',
        f'{indent}handler_{entry["handler"]}(instr);',
    ]


def emit_selection(entries, indent, fallback):
    """Select a mandatory-prefix variant, falling back to the unprefixed form."""
    prefixed = [entry for entry in entries if entry["prefixes"]]
    unprefixed = [entry for entry in entries if not entry["prefixes"]]
    lines = []

    if not prefixed:
        if unprefixed:
            return emit_instruction(unprefixed[0], indent)
        return [f"{indent}{fallback}"]

    for index, entry in enumerate(prefixed):
        condition = prefix_condition(entry["prefixes"])
        keyword = "if" if index == 0 else "else if"
        lines.append(f"{indent}{keyword} ({condition}) {{")
        lines.extend(emit_instruction(entry, indent + "    "))
        lines.append(f"{indent}}}")

    if unprefixed:
        lines.append(f"{indent}else {{")
        lines.extend(emit_instruction(unprefixed[0], indent + "    "))
        lines.append(f"{indent}}}")
    else:
        lines.append(f"{indent}else {{")
        lines.append(f"{indent}    {fallback}")
        lines.append(f"{indent}}}")

    return lines


def emit_node(node, depth, indent_level):
    indent = "    " * indent_level
    lines = [f"{indent}switch (instr->op[{depth}]) {{"]

    for byte in sorted(node):
        child = node[byte]
        case_indent = indent + "    "
        lines.append(f"{case_indent}case 0x{byte:02X}: {{")

        if child["children"]:
            if child["entries"]:
                raise ValueError(f"opcode 0x{byte:02X} is both complete and a prefix of another opcode")
            lines.extend(emit_node(child["children"], depth + 1, indent_level + 2))
        else:
            entries = child["entries"]
            grouped = {}
            plain = []
            for entry in entries:
                if entry["extension"] is None:
                    plain.append(entry)
                else:
                    grouped.setdefault(entry["extension"], []).append(entry)

            if grouped:
                lines.append(f"{case_indent}    switch (instr->modrm.bits.reg) {{")
                for extension in sorted(grouped):
                    lines.append(f"{case_indent}        case {extension}: {{")
                    lines.extend(emit_selection(grouped[extension], case_indent + "            ", 'append_text(instr, "(UD Group)");'))
                    lines.append(f"{case_indent}            break;")
                    lines.append(f"{case_indent}        }}")
                lines.append(f"{case_indent}        default:")
                lines.append(f'{case_indent}            append_text(instr, "(UD Group)");')
                lines.append(f"{case_indent}            break;")
                lines.append(f"{case_indent}    }}")
            elif plain:
                lines.extend(emit_selection(plain, case_indent + "    ", f"append_unknown_opcode(instr, {depth});"))

        lines.append(f"{case_indent}    break;")
        lines.append(f"{case_indent}}}")

    lines.append(f"{indent}    default:")
    lines.append(f'{indent}        append_unknown_opcode(instr, {depth});')
    lines.append(f"{indent}        break;")
    lines.append(f"{indent}}}")
    return lines


def generate_header(entries):
    lines = [
        "/* Generated from definitions.txt by defs2header.py. Do not edit. */",
        *emit_node(build_tree(entries), 0, 0),
        "",
    ]
    return "\n".join(lines)


def main():
    try:
        entries = parse_definitions(INPUT_FILE)
        OUTPUT_FILE.write_text(generate_header(entries), encoding="utf-8")
    except (OSError, ValueError) as error:
        print(f"defs2header: {error}", file=sys.stderr)
        return 1

    print(f"Generated {OUTPUT_FILE.name} from {INPUT_FILE.name} ({len(entries)} opcode entries).")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
