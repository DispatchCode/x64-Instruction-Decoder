#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "disasm.h"

extern int x64id_arch;

enum register_class {
    REG_GPR8, REG_GPR8_REX, REG_GPR16, REG_GPR32, REG_GPR64,
    REG_XMM, REG_YMM, REG_SEGMENT, REG_CONTROL, REG_DEBUG
};

static const char *const register_table[][16] = {
    {"al", "cl", "dl", "bl", "ah", "ch", "dh", "bh", "r8b", "r9b", "r10b", "r11b", "r12b", "r13b", "r14b", "r15b"},
    {"al", "cl", "dl", "bl", "spl", "bpl", "sil", "dil", "r8b", "r9b", "r10b", "r11b", "r12b", "r13b", "r14b", "r15b"},
    {"ax", "cx", "dx", "bx", "sp", "bp", "si", "di", "r8w", "r9w", "r10w", "r11w", "r12w", "r13w", "r14w", "r15w"},
    {"eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi", "r8d", "r9d", "r10d", "r11d", "r12d", "r13d", "r14d", "r15d"},
    {"rax", "rcx", "rdx", "rbx", "rsp", "rbp", "rsi", "rdi", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15"},
    {"xmm0", "xmm1", "xmm2", "xmm3", "xmm4", "xmm5", "xmm6", "xmm7", "xmm8", "xmm9", "xmm10", "xmm11", "xmm12", "xmm13", "xmm14", "xmm15"},
    {"ymm0", "ymm1", "ymm2", "ymm3", "ymm4", "ymm5", "ymm6", "ymm7", "ymm8", "ymm9", "ymm10", "ymm11", "ymm12", "ymm13", "ymm14", "ymm15"},
    {"es", "cs", "ss", "ds", "fs", "gs", "??", "??", "es", "cs", "ss", "ds", "fs", "gs", "??", "??"},
    {"cr0", "cr1", "cr2", "cr3", "cr4", "cr5", "cr6", "cr7", "cr8", "cr9", "cr10", "cr11", "cr12", "cr13", "cr14", "cr15"},
    {"dr0", "dr1", "dr2", "dr3", "dr4", "dr5", "dr6", "dr7", "dr8", "dr9", "dr10", "dr11", "dr12", "dr13", "dr14", "dr15"}
};

static void appendf(struct instruction *instr, const char *format, ...)
{
    va_list args;
    size_t remaining;
    int written;

    if (instr->disasm_str_len < 0 || instr->disasm_str_len >= MAX_INSTR_LEN_STR - 1)
        return;

    remaining = MAX_INSTR_LEN_STR - (size_t)instr->disasm_str_len;
    va_start(args, format);
    written = vsnprintf(instr->disasm + instr->disasm_str_len, remaining, format, args);
    va_end(args);

    if (written > 0) {
        size_t added = (size_t)written < remaining ? (size_t)written : remaining - 1;
        instr->disasm_str_len += (int)added;
    }
}

const char *get_reg_name(uint8_t size, bool has_rex, unsigned index)
{
    enum register_class reg_class;

    switch (size) {
        case 1: reg_class = has_rex ? REG_GPR8_REX : REG_GPR8; break;
        case 2: reg_class = REG_GPR16; break;
        case 4: reg_class = REG_GPR32; break;
        case 8: reg_class = REG_GPR64; break;
        case 16: reg_class = REG_XMM; break;
        case 32: reg_class = REG_YMM; break;
        default: return "??";
    }
    return index < 16 ? register_table[reg_class][index] : "??";
}

static uint8_t get_operand_size(const struct instruction *instr)
{
    if (instr->set_prefix & OP64)
        return 8;
    if (instr->set_prefix & OS)
        return 2;
    return 4;
}

static uint64_t displacement_magnitude(int64_t displacement)
{
    return displacement < 0 ? (uint64_t)(-(displacement + 1)) + 1 : (uint64_t)displacement;
}

static void print_memory(struct instruction *instr, const struct decoded_operand *op)
{
    bool has_term = false;

    if (op->rip_relative) {
        appendf(instr, "RIP");
        has_term = true;
    } else if (op->has_base) {
        appendf(instr, "%s", get_reg_name(op->address_size, !!(instr->set_field & REX), op->base));
        has_term = true;
    }

    if (op->has_index) {
        if (has_term) appendf(instr, "+");
        appendf(instr, "%s", get_reg_name(op->address_size, !!(instr->set_field & REX), op->index));
        if (op->scale > 1) appendf(instr, "*%u", op->scale);
        has_term = true;
    }

    if (op->displacement || !has_term) {
        if (has_term)
            appendf(instr, op->displacement < 0 ? "-0x%llx" : "+0x%llx",
                    (unsigned long long)displacement_magnitude(op->displacement));
        else
            appendf(instr, "0x%llx", (unsigned long long)displacement_magnitude(op->displacement));
    }
}

static void print_operand(struct instruction *instr, const struct decoded_operand *op,
                          uint8_t size, bool memory_qualifier)
{
    switch (op->kind) {
        case DECODED_OPERAND_REGISTER:
            appendf(instr, "%s", get_reg_name(size, !!(instr->set_field & REX), op->reg));
            break;
        case DECODED_OPERAND_MEMORY:
            if (memory_qualifier) {
                switch (size) {
                    case 1: appendf(instr, "BYTE PTR "); break;
                    case 2: appendf(instr, "WORD PTR "); break;
                    case 4: appendf(instr, "DWORD PTR "); break;
                    case 8: appendf(instr, "QWORD PTR "); break;
                    case 16: appendf(instr, "XMMWORD PTR "); break;
                    case 32: appendf(instr, "YMMWORD PTR "); break;
                    default: break;
                }
            }

	    appendf(instr, "[");
            print_memory(instr, op);
            appendf(instr, "]");
            break;
        case DECODED_OPERAND_IMMEDIATE:
            appendf(instr, "0x%llx", (unsigned long long)op->immediate);
            break;
        default:
            appendf(instr, "??");
            break;
    }
}

static void handle_modrm_pair(struct instruction *instr, uint8_t size, bool reg_first)
{
    if (instr->operand_count < 2)
        return;

    const struct decoded_operand *rm = &instr->operands[0];
    const struct decoded_operand *reg = &instr->operands[1];
    const struct decoded_operand *first = reg_first ? reg : rm;
    const struct decoded_operand *second = reg_first ? rm : reg;

    print_operand(instr, first, size, true);
    appendf(instr, ", ");
    print_operand(instr, second, size, true);
}

void handler_Gv_Ev(struct instruction *instr) { handle_modrm_pair(instr, get_operand_size(instr), true); }
void handler_Ev_Gv(struct instruction *instr) { handle_modrm_pair(instr, get_operand_size(instr), false); }
void handler_Eb_Gb(struct instruction *instr) { handle_modrm_pair(instr, 1, false); }
void handler_Gb_Eb(struct instruction *instr) { handle_modrm_pair(instr, 1, true); }

static void handle_rm_immediate(struct instruction *instr, uint8_t size)
{
    if (instr->operand_count < 3)
        return;

    print_operand(instr, &instr->operands[0], size, true);
    appendf(instr, ", ");
    print_operand(instr, &instr->operands[instr->operand_count - 1], size, false);
}

void handler_Eb_Ib(struct instruction *instr) { handle_rm_immediate(instr, 1); }
void handler_Ev_Iz(struct instruction *instr) { handle_rm_immediate(instr, get_operand_size(instr)); }

static void handle_accumulator_immediate(struct instruction *instr, uint8_t size)
{
    if (instr->operand_count == 0)
        return;

    appendf(instr, "%s, ", get_reg_name(size, !!(instr->set_field & REX), 0));
    print_operand(instr, &instr->operands[instr->operand_count - 1], size, false);
}

void handler_Al_Ib(struct instruction *instr) { handle_accumulator_immediate(instr, 1); }
void handler_Al_Iz(struct instruction *instr) { handle_accumulator_immediate(instr, get_operand_size(instr)); }

void handler_Reg_In_Opcode(struct instruction *instr)
{
    uint8_t size;

    if (instr->operand_count == 0)
        return;
    
    size = x64id_arch == X64 ? 8 : 4;
    
    if (instr->set_prefix & OS) size = x64id_arch == X64 ? 4 : 2;
    print_operand(instr, &instr->operands[instr->operand_count - 1], size, false);
}

static void handle_opcode_register_immediate(struct instruction *instr, uint8_t size)
{
    if (instr->operand_count < 2)
        return;
    
    print_operand(instr, &instr->operands[instr->operand_count - 1], size, false);
    appendf(instr, ", ");
    print_operand(instr, &instr->operands[0], size, false);
}

void handler_Reg8_In_Opcode_Ib(struct instruction *instr)
{
    handle_opcode_register_immediate(instr, 1);
}

void handler_Reg_In_Opcode_Iz(struct instruction *instr)
{
    handle_opcode_register_immediate(instr, get_operand_size(instr));
}

static void handler_relative_target(struct instruction *instr)
{
    appendf(instr, "0x%llx", (unsigned long long)instr->label);
}

void handler_Jb(struct instruction *instr) { handler_relative_target(instr); }
void handler_Jz(struct instruction *instr) { handler_relative_target(instr); }

void handler_None(struct instruction *instr) { (void)instr; }

static uint8_t vex_map(const struct instruction *instr)
{
    return instr->vex[0] == 0xC5 ? 1 : (uint8_t)(instr->vex[1] & 0x1f);
}

static uint8_t vex_pp(const struct instruction *instr)
{
    return instr->vex[instr->vex[0] == 0xC5 ? 1 : 2] & 3;
}

static uint8_t vex_vector_size(const struct instruction *instr)
{
    uint8_t prefix_index = instr->vex[0] == 0xC5 ? 1 : 2;
    return (instr->vex[prefix_index] & 4) ? 32 : 16;
}

static void disasm_vex(struct instruction *instr)
{
    if (vex_map(instr) == 1 && (instr->op[0] == 0x12 || instr->op[0] == 0x16)) {
        uint8_t pp = vex_pp(instr);
        const char *mnemonic = NULL;

	if (pp == 2 && instr->op[0] == 0x12) mnemonic = "vmovsldup";
        if (pp == 2 && instr->op[0] == 0x16) mnemonic = "vmovshdup";
        if (pp == 3 && instr->op[0] == 0x12) mnemonic = "vmovddup";
        if (mnemonic != NULL) {
            appendf(instr, "%s ", mnemonic);
            handle_modrm_pair(instr, vex_vector_size(instr), true);
            return;
        }
    }

    appendf(instr, "vex.%u 0x%02x", vex_map(instr), instr->op[0]);
}

void x64id_disasm(struct instruction *instr)
{
    instr->disasm[0] = '\0';
    instr->disasm_str_len = 0;

    if (instr->set_prefix & VEX) {
        disasm_vex(instr);
        return;
    }

    #include "tools/generated_opcodes.h"
}
