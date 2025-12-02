import sys

INPUT_FILE = "definitions.txt"
OUTPUT_FILE = "generated_opcodes.h"

def parse_opcode_string(op_str):
    op_str = op_str.strip()
    extension = None
    
    # Check for Group Extension (e.g., 0x80/2)
    if '/' in op_str:
        base, ext_str = op_str.split('/')
        extension = int(ext_str) # 0-7
        op_str = base # Continue processing the base opcode
        
    if ':' in op_str:
        start_str, end_str = op_str.split(':')
        start_val = int(start_str, 16)
        end_val = int(end_str, 16)
        ops = range(start_val, end_val + 1)
    else:
        ops = [int(op_str, 16)]
        
    result = []
    for i in ops:
        if i > 0xFFFF: seq = [(i >> 16) & 0xFF, (i >> 8) & 0xFF, i & 0xFF]
        elif i > 0xFF: seq = [(i >> 8) & 0xFF, i & 0xFF]
        else:          seq = [i]
        result.append((seq, extension))
        
    return result

def parse_definitions(filename):
    entries = []
    try:
        with open(filename, "r") as f:
            lines = f.readlines()
    except FileNotFoundError:
        print("File not found.")
        sys.exit(1)

    for line in lines:
        raw = line.split("#")[0].strip()
        if not raw: continue
        parts = [p.strip() for p in raw.split('|')]
        if len(parts) != 4: continue
            
        prefix, op_str, mnemonic, handler = parts
        
        # Get list of (byte_seq, extension) tuples
        opcode_data = parse_opcode_string(op_str)
        
        for bytes_seq, ext in opcode_data:
            entries.append({
                "bytes": bytes_seq,
                "prefix": prefix,
                "mnemonic": mnemonic,
                "handler": handler,
                "extension": ext # New field: None or 0-7
            })
    return entries

def build_tree(entries):
    root = {}
    for e in entries:
        curr = root
        for i, b in enumerate(e['bytes']):
            if b not in curr: curr[b] = {'__candidates__': []}
            node = curr[b]
            if i == len(e['bytes']) - 1:
                node['__candidates__'].append(e)
            else:
                if '__children__' not in node: node['__children__'] = {}
                curr = node['__children__']
    return root

def generate_switch(node, depth, indent_level):
    indent = "    " * indent_level
    out = f"{indent}switch (instr->op[{depth}]) {{\n"
    
    for byte_val in sorted([k for k in node.keys() if isinstance(k, int)]):
        child = node[byte_val]
        candidates = child.get('__candidates__', [])
        has_children = '__children__' in child
        
        out += f"{indent}    case 0x{byte_val:02X}: {{\n"
        
        # 1. Recursive Children (e.g. 0x0F...)
        if has_children:
            out += generate_switch(child['__children__'], depth + 1, indent_level + 2)
            out += f"{indent}        break;\n"
            out += f"{indent}    }}\n" # End case
            continue

        # 2. Check if this is a GROUP (uses /0, /1 extensions)
        # We group candidates by their extension ID
        groups = {} # Key: int (0-7), Value: list of candidates
        simple_candidates = []
        
        for c in candidates:
            if c['extension'] is not None:
                if c['extension'] not in groups: groups[c['extension']] = []
                groups[c['extension']].append(c)
            else:
                simple_candidates.append(c)

        if groups:
            # IT IS A GROUP! Generate switch on ModRM.Reg
            out += f"{indent}        switch (instr->modrm.reg) {{\n"
            for ext_id, group_cands in groups.items():
                out += f"{indent}            case {ext_id}:\n"
                # Handle Prefixes inside the group case
                for c in group_cands:
                    if c['prefix'] == '00':
                        out += f"{indent}                INSTR_CONCAT(\"{c['mnemonic']} \", \"%s\"); handler_{c['handler']}(instr);\n"
                    else:
                        out += f"{indent}                if (instr->prefixes[0] == 0x{c['prefix']}) {{ INSTR_CONCAT(\"{c['mnemonic']} \",\"%s\"); handler_{c['handler']}(instr); }}\n"
                out += f"{indent}                break;\n"
            
            # Default for undefined extensions in this group
            out += f"{indent}            default: INSTR_CONCAT(\"(UD Group)\"); break;\n"
            out += f"{indent}        }}\n"
            
        elif simple_candidates:
            # Standard instruction (No group extension)
            c = simple_candidates[0] # taking first for brevity
            # (Insert logic for prefix handling here if needed, simplified for clarity)
            out += f"{indent}        INSTR_CONCAT(\"{c['mnemonic']} \", \"%s\");\n"
            out += f"{indent}        handler_{c['handler']}(instr);\n"
        
        out += f"{indent}        break;\n"
        out += f"{indent}    }}\n"

    out += f"{indent}    default:\n"
    out += f"{indent}        INSTR_CONCAT(instr->op[{depth}], \"db 0x%02X \");\n"
    out += f"{indent}        break;\n"
    out += f"{indent}}}\n"
    return out

if __name__ == "__main__":
    data = parse_definitions(INPUT_FILE)
    root = build_tree(data)
    with open(OUTPUT_FILE, "w") as f:
        f.write(generate_switch(root, 0, 0))
    print("Done.")
