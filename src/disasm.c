// SPDX-License-Identifier: GPL-2.0-only

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "disasm.h"

enum register_class {
	REG_GPR8,
	REG_GPR8_REX,
	REG_GPR16,
	REG_GPR32,
	REG_GPR64,
	REG_XMM,
	REG_YMM,
	REG_SEGMENT,
	REG_CONTROL,
	REG_DEBUG
};

static const char *const register_table[][16] = {
	{"al", "cl", "dl", "bl", "ah", "ch", "dh", "bh", "r8b", "r9b", "r10b",
	 "r11b", "r12b", "r13b", "r14b", "r15b"},
	{"al", "cl", "dl", "bl", "spl", "bpl", "sil", "dil", "r8b", "r9b", "r10b",
	 "r11b", "r12b", "r13b", "r14b", "r15b"},
	{"ax", "cx", "dx", "bx", "sp", "bp", "si", "di", "r8w", "r9w", "r10w",
	 "r11w", "r12w", "r13w", "r14w", "r15w"},
	{"eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi", "r8d", "r9d",
	 "r10d", "r11d", "r12d", "r13d", "r14d", "r15d"},
	{"rax", "rcx", "rdx", "rbx", "rsp", "rbp", "rsi", "rdi", "r8", "r9", "r10",
	 "r11", "r12", "r13", "r14", "r15"},
	{"xmm0", "xmm1", "xmm2", "xmm3", "xmm4", "xmm5", "xmm6", "xmm7", "xmm8",
	 "xmm9", "xmm10", "xmm11", "xmm12", "xmm13", "xmm14", "xmm15"},
	{"ymm0", "ymm1", "ymm2", "ymm3", "ymm4", "ymm5", "ymm6", "ymm7", "ymm8",
	 "ymm9", "ymm10", "ymm11", "ymm12", "ymm13", "ymm14", "ymm15"},
	{"es", "cs", "ss", "ds", "fs", "gs", "??", "??", "es", "cs", "ss", "ds",
	 "fs", "gs", "??", "??"},
	{"cr0", "cr1", "cr2", "cr3", "cr4", "cr5", "cr6", "cr7", "cr8", "cr9",
	 "cr10", "cr11", "cr12", "cr13", "cr14", "cr15"},
	{"dr0", "dr1", "dr2", "dr3", "dr4", "dr5", "dr6", "dr7", "dr8", "dr9",
	 "dr10", "dr11", "dr12", "dr13", "dr14", "dr15"}};

static size_t disasm_remaining(const struct instruction *instr)
{
	if (instr->disasm_str_len < 0 ||
		instr->disasm_str_len >= MAX_INSTR_LEN_STR - 1)
		return 0;

	return MAX_INSTR_LEN_STR - (size_t)instr->disasm_str_len;
}

static char *disasm_write_ptr(struct instruction *instr)
{
	return instr->disasm + instr->disasm_str_len;
}

static void append_char(struct instruction *instr, char value)
{
	if (disasm_remaining(instr) < 2)
		return;

	*disasm_write_ptr(instr) = value;
	instr->disasm_str_len++;
	instr->disasm[instr->disasm_str_len] = '\0';
}

static void reset_disasm(struct instruction *instr)
{
	instr->disasm_str_len = 0;
	instr->disasm[0] = '\0';
}

static void appendf(struct instruction *instr, const char *format, ...)
{
	va_list args;
	size_t remaining = disasm_remaining(instr);
	int written;

	if (!remaining)
		return;

	va_start(args, format);
	written = vsnprintf(disasm_write_ptr(instr), remaining, format, args);
	va_end(args);

	if (written > 0) {
		size_t added =
			(size_t)written < remaining ? (size_t)written : remaining - 1;
		instr->disasm_str_len += (int)added;
	}
}

static void append_text(struct instruction *instr, const char *text)
{
	size_t remaining = disasm_remaining(instr);
	size_t length;
	size_t added;

	if (!remaining)
		return;

	length = strlen(text);
	added = length < remaining ? length : remaining - 1;
	if (!added)
		return;

	memcpy(disasm_write_ptr(instr), text, added);
	instr->disasm_str_len += (int)added;
	instr->disasm[instr->disasm_str_len] = '\0';
}

static void append_mnemonic(struct instruction *instr, const char *mnemonic)
{
	append_text(instr, mnemonic);
	append_char(instr, ' ');
}

static void append_data_byte(struct instruction *instr, uint8_t byte)
{
	appendf(instr, "db 0x%02X ", byte);
}

static void replace_with_data(struct instruction *instr)
{
	reset_disasm(instr);
	for (int i = 0; i < instr->length && i < (int)sizeof(instr->instr); i++)
		append_data_byte(instr, instr->instr[i]);
}

static void append_unknown_opcode(struct instruction *instr, uint8_t last_index)
{
	for (uint8_t index = 0; index <= last_index && index < 3; ++index)
		append_data_byte(instr, instr->op[index]);
}

const char *get_reg_name(uint8_t size, bool has_rex, unsigned index)
{
	enum register_class reg_class;

	switch (size) {
	case 1:
		reg_class = has_rex ? REG_GPR8_REX : REG_GPR8;
		break;
	case 2:
		reg_class = REG_GPR16;
		break;
	case 4:
		reg_class = REG_GPR32;
		break;
	case 8:
		reg_class = REG_GPR64;
		break;
	case 16:
		reg_class = REG_XMM;
		break;
	case 32:
		reg_class = REG_YMM;
		break;
	default:
		return "??";
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
	return displacement < 0 ? (uint64_t)(-(displacement + 1)) + 1
							: (uint64_t)displacement;
}

static void print_memory(struct instruction *instr,
						 const struct decoded_operand *op)
{
	bool has_term = false;

	if (op->rip_relative) {
		append_text(instr, "RIP");
		has_term = true;
	} else if (op->has_base) {
		append_text(instr, get_reg_name(op->address_size,
										!!(instr->set_field & REX), op->base));
		has_term = true;
	}

	if (op->has_index) {
		if (has_term)
			append_char(instr, '+');
		append_text(instr, get_reg_name(op->address_size,
										!!(instr->set_field & REX), op->index));
		if (op->scale > 1)
			appendf(instr, "*%u", op->scale);
		has_term = true;
	}

	if (op->displacement || !has_term) {
		if (has_term)
			appendf(
				instr, op->displacement < 0 ? "-0x%llx" : "+0x%llx",
				(unsigned long long)displacement_magnitude(op->displacement));
		else
			appendf(
				instr, "0x%llx",
				(unsigned long long)displacement_magnitude(op->displacement));
	}
}

static const char *memory_size_name(uint8_t size)
{
	switch (size) {
	case 1:
		return "BYTE";
	case 2:
		return "WORD";
	case 4:
		return "DWORD";
	case 8:
		return "QWORD";
	case 16:
		return "XMMWORD";
	case 32:
		return "YMMWORD";
	default:
		return NULL;
	}
}

static void print_operand(struct instruction *instr,
						  const struct decoded_operand *op, uint8_t size,
						  bool memory_qualifier)
{
	switch (op->kind) {
	case DECODED_OPERAND_REGISTER:
		append_text(instr,
					get_reg_name(size, !!(instr->set_field & REX), op->reg));
		break;
	case DECODED_OPERAND_SEGMENT_REGISTER:
		append_text(instr,
					op->reg < 8 ? register_table[REG_SEGMENT][op->reg] : "??");
		break;
	case DECODED_OPERAND_CONTROL_REGISTER:
		append_text(instr,
					op->reg < 16 ? register_table[REG_CONTROL][op->reg] : "??");
		break;
	case DECODED_OPERAND_DEBUG_REGISTER:
		append_text(instr,
					op->reg < 16 ? register_table[REG_DEBUG][op->reg] : "??");
		break;
	case DECODED_OPERAND_MEMORY:
		if (memory_qualifier) {
			const char *size_name = memory_size_name(size);
			if (size_name) {
				append_text(instr, size_name);
				append_text(instr, " PTR ");
			}
		}

		append_char(instr, '[');
		print_memory(instr, op);
		append_char(instr, ']');
		break;
	case DECODED_OPERAND_IMMEDIATE:
		appendf(instr, "0x%llx", (unsigned long long)op->immediate);
		break;
	default:
		append_text(instr, "??");
		break;
	}
}

static void handle_modrm_pair_sizes(struct instruction *instr, uint8_t rm_size,
									uint8_t reg_size, bool reg_first)
{
	if (instr->operand_count < 2)
		return;

	const struct decoded_operand *rm = &instr->operands[0];
	const struct decoded_operand *reg = &instr->operands[1];
	const struct decoded_operand *first = reg_first ? reg : rm;
	const struct decoded_operand *second = reg_first ? rm : reg;

	print_operand(instr, first, reg_first ? reg_size : rm_size, true);
	append_text(instr, ", ");
	print_operand(instr, second, reg_first ? rm_size : reg_size, true);
}

static void handle_modrm_pair(struct instruction *instr, uint8_t size,
							  bool reg_first)
{
	handle_modrm_pair_sizes(instr, size, size, reg_first);
}

static void handle_modrm_pair_immediate(struct instruction *instr, uint8_t size,
										uint8_t immediate_size, bool reg_first)
{
	if (instr->operand_count < 3)
		return;

	handle_modrm_pair(instr, size, reg_first);
	append_text(instr, ", ");
	print_operand(instr, &instr->operands[instr->operand_count - 1],
				  immediate_size, false);
}

void handler_Gv_Ev(struct instruction *instr)
{
	handle_modrm_pair(instr, get_operand_size(instr), true);
}

void handler_Gv_Ew(struct instruction *instr)
{
	handle_modrm_pair_sizes(instr, 2, get_operand_size(instr), true);
}

void handler_Gv_Eb(struct instruction *instr)
{
	handle_modrm_pair_sizes(instr, 1, get_operand_size(instr), true);
}

void handler_Ev_Gv_CL(struct instruction *instr)
{
	if (instr->operand_count < 2)
		return;
	handle_modrm_pair(instr, get_operand_size(instr), false);
	append_text(instr, ", cl");
}

void handler_bswap(struct instruction *instr)
{
	uint8_t reg = (uint8_t)((instr->op[1] & 7) + (instr->rex.bits.rex_b << 3));
	uint8_t size = (instr->set_prefix & OP64) ? 8 : 4;
	append_text(instr, get_reg_name(size, !!(instr->set_field & REX), reg));
}

void handler_Gv_Ev_Iz(struct instruction *instr)
{
	uint8_t size = get_operand_size(instr);
	handle_modrm_pair_immediate(instr, size, size, true);
}

void handler_Gv_Ev_Ib(struct instruction *instr)
{
	handle_modrm_pair_immediate(instr, get_operand_size(instr), 1, true);
}

void handler_Ev_Gv_Ib(struct instruction *instr)
{
	handle_modrm_pair_immediate(instr, get_operand_size(instr), 1, false);
}

void handler_Ev_Gv(struct instruction *instr)
{
	handle_modrm_pair(instr, get_operand_size(instr), false);
}
void handler_Eb_Gb(struct instruction *instr)
{
	handle_modrm_pair(instr, 1, false);
}
void handler_Gb_Eb(struct instruction *instr)
{
	handle_modrm_pair(instr, 1, true);
}

void handler_Ew(struct instruction *instr)
{
	if (instr->operand_count > 0)
		print_operand(instr, &instr->operands[0], 2, true);
}

static void handle_rm_operand(struct instruction *instr, uint8_t size)
{
	if (instr->operand_count > 0)
		print_operand(instr, &instr->operands[0], size, true);
}

void handler_Ev(struct instruction *instr)
{
	handle_rm_operand(instr, get_operand_size(instr));
}

void handler_Eb(struct instruction *instr) { handle_rm_operand(instr, 1); }

void handler_Ev64(struct instruction *instr)
{
	handle_rm_operand(instr, x64id_is_64bit ? 8 : get_operand_size(instr));
}

void handler_Lea(struct instruction *instr)
{
	if (instr->operand_count < 2)
		return;
	print_operand(instr, &instr->operands[1], get_operand_size(instr), false);
	append_text(instr, ", ");
	print_operand(instr, &instr->operands[0], 0, false);
}

void handler_pop_Ev(struct instruction *instr)
{
	uint8_t size = x64id_is_64bit ? 8 : get_operand_size(instr);
	handle_rm_operand(instr, size);
}

void handler_push_imm(struct instruction *instr)
{
	if (instr->operand_count == 0)
		return;
	print_operand(instr, &instr->operands[instr->operand_count - 1], 0, false);
}

void handler_xchg_accumulator(struct instruction *instr)
{
	uint8_t size = get_operand_size(instr);
	uint8_t opcode = instr->op[0];
	uint8_t reg = (uint8_t)((opcode & 7) + (instr->rex.bits.rex_b << 3));

	append_text(instr, get_reg_name(size, !!(instr->set_field & REX), 0));
	append_text(instr, ", ");
	append_text(instr, get_reg_name(size, !!(instr->set_field & REX), reg));
}

void handler_ret_imm(struct instruction *instr)
{
	if (instr->operand_count > 0)
		print_operand(instr, &instr->operands[instr->operand_count - 1], 2,
					  false);
}

void handler_int_imm(struct instruction *instr)
{
	if (instr->operand_count > 0)
		print_operand(instr, &instr->operands[instr->operand_count - 1], 1,
					  false);
}

static void handle_shift(struct instruction *instr, bool count_is_cl)
{
	uint8_t opcode = instr->op[0];
	uint8_t size = (opcode == 0xC0 || opcode == 0xD0 || opcode == 0xD2)
					   ? 1
					   : get_operand_size(instr);

	handle_rm_operand(instr, size);
	append_text(instr, ", ");
	if (count_is_cl)
		append_text(instr, "cl");
	else if (opcode == 0xD0 || opcode == 0xD1)
		append_text(instr, "1");
	else if (instr->operand_count > 1)
		print_operand(instr, &instr->operands[instr->operand_count - 1], 1,
					  false);
}

void handler_shift_one(struct instruction *instr)
{
	handle_shift(instr, false);
}

void handler_shift_cl(struct instruction *instr) { handle_shift(instr, true); }

void handler_segment_stack(struct instruction *instr)
{
	static const char *const segments[8] = {"es", "cs", "ss", "ds",
											"fs", "gs", "??", "??"};
	uint8_t opcode = instr->op_cnt > 1 ? instr->op[1] : instr->op[0];
	uint8_t segment = (opcode == 0x06 || opcode == 0x07)   ? 0
					  : opcode == 0x0E					   ? 1
					  : (opcode == 0x16 || opcode == 0x17) ? 2
														   : 3;

	if (opcode == 0xA0 || opcode == 0xA1)
		segment = 4;
	else if (opcode == 0xA8 || opcode == 0xA9)
		segment = 5;

	if (x64id_is_64bit && segment < 4) {
		replace_with_data(instr);
		return;
	}
	append_text(instr, segments[segment]);
}

void handler_far_load(struct instruction *instr)
{
	if (x64id_is_64bit) {
		replace_with_data(instr);
		return;
	}
	if (instr->operand_count < 2)
		return;
	print_operand(instr, &instr->operands[1], get_operand_size(instr), false);
	append_text(instr, ", ");
	print_operand(instr, &instr->operands[0], 0, false);
}

void handler_endbr(struct instruction *instr)
{
	const char *mnemonic = instr->modrm.value == 0xFA ? "endbr64" : "endbr32";
	reset_disasm(instr);
	append_mnemonic(instr, mnemonic);
}

void handler_moffs(struct instruction *instr)
{
	uint8_t opcode = instr->op[0];
	uint8_t size =
		(opcode == 0xA0 || opcode == 0xA2) ? 1 : get_operand_size(instr);
	bool load = opcode == 0xA0 || opcode == 0xA1;
	const char *size_name = memory_size_name(size);

	if (load) {
		append_text(instr, get_reg_name(size, !!(instr->set_field & REX), 0));
		append_text(instr, ", ");
	}

	append_text(instr, size_name ? size_name : "DWORD");
	append_text(instr, " PTR [");
	appendf(instr, "0x%llx", (unsigned long long)instr->imm);
	append_char(instr, ']');

	if (!load) {
		append_text(instr, ", ");
		append_text(instr, get_reg_name(size, !!(instr->set_field & REX), 0));
	}
}

void handler_integer_alias(struct instruction *instr)
{
	bool wide = (instr->set_prefix & OP64) != 0;
	bool word = (instr->set_prefix & OS) != 0;
	const char *mnemonic;

	if (instr->op[0] == 0x98)
		mnemonic = wide ? "cdqe" : word ? "cbw" : "cwde";
	else
		mnemonic = wide ? "cqo" : word ? "cwd" : "cdq";

	reset_disasm(instr);
	append_mnemonic(instr, mnemonic);
}

void handler_enter(struct instruction *instr)
{
	uint8_t nesting = (uint8_t)(instr->imm >> 16);
	appendf(instr, "0x%04llx, 0x%02x",
			(unsigned long long)(instr->imm & 0xffff), nesting);
}

void handler_far_pointer(struct instruction *instr)
{
	if (x64id_is_64bit) {
		replace_with_data(instr);
		return;
	}

	uint8_t offset_size = instr->imm_len == 6 ? 4 : 2;
	uint64_t offset_mask = offset_size == 4 ? UINT32_MAX : UINT16_MAX;
	uint16_t segment = (uint16_t)(instr->imm >> (offset_size * 8));
	appendf(instr, "0x%04x:0x%llx", segment,
			(unsigned long long)(instr->imm & offset_mask));
}

void handler_jrcxz(struct instruction *instr)
{
	const char *mnemonic;
	if (x64id_is_64bit)
		mnemonic = instr->set_prefix & AS ? "jecxz" : "jrcxz";
	else
		mnemonic = instr->set_prefix & AS ? "jcxz" : "jecxz";
	reset_disasm(instr);
	append_mnemonic(instr, mnemonic);
	appendf(instr, "0x%llx", (unsigned long long)instr->label);
}

void handler_aam_aad(struct instruction *instr)
{
	if (x64id_is_64bit) {
		handler_x86_only(instr);
		return;
	}
	if (instr->operand_count > 0)
		print_operand(instr, &instr->operands[0], 1, false);
}

void handler_io(struct instruction *instr)
{
	uint8_t opcode = instr->op[0];
	bool input =
		opcode == 0xE4 || opcode == 0xE5 || opcode == 0xEC || opcode == 0xED;
	bool immediate_port = opcode >= 0xE4 && opcode <= 0xE7;
	uint8_t size =
		(opcode == 0xE4 || opcode == 0xE6 || opcode == 0xEC || opcode == 0xEE)
			? 1
			: get_operand_size(instr);

	if (input) {
		append_text(instr, get_reg_name(size, !!(instr->set_field & REX), 0));
		append_text(instr, ", ");
		if (immediate_port)
			appendf(instr, "0x%llx", (unsigned long long)instr->imm);
		else
			append_text(instr, "dx");
	} else {
		if (immediate_port)
			appendf(instr, "0x%llx, ", (unsigned long long)instr->imm);
		else
			append_text(instr, "dx, ");
		append_text(instr, get_reg_name(size, !!(instr->set_field & REX), 0));
	}
}

void handler_segment_move(struct instruction *instr)
{
	bool load_segment = instr->op[0] == 0x8E;

	if (instr->modrm.bits.reg >= 6 ||
		(load_segment && instr->modrm.bits.reg == 1)) {
		replace_with_data(instr);
		return;
	}
	if (instr->operand_count < 2)
		return;
	if (load_segment) {
		print_operand(instr, &instr->operands[1], 0, false);
		append_text(instr, ", ");
		print_operand(instr, &instr->operands[0], 2, true);
	} else {
		print_operand(instr, &instr->operands[0], 2, true);
		append_text(instr, ", ");
		print_operand(instr, &instr->operands[1], 0, false);
	}
}

void handler_special_move(struct instruction *instr)
{
	uint8_t gpr_size = x64id_is_64bit ? 8 : 4;

	if (instr->modrm.bits.mod != 3) {
		replace_with_data(instr);
		return;
	}
	if (instr->operand_count < 2)
		return;

	bool special_first = instr->op[1] == 0x22 || instr->op[1] == 0x23;
	handle_modrm_pair(instr, gpr_size, special_first);
}

void handler_arpl_movsxd(struct instruction *instr)
{
	if (instr->operand_count < 2)
		return;
	if (x64id_is_64bit) {
		reset_disasm(instr);
		append_mnemonic(instr, "movsxd");
		print_operand(instr, &instr->operands[1], get_operand_size(instr),
					  false);
		append_text(instr, ", ");
		print_operand(instr, &instr->operands[0], 4, true);
	} else {
		print_operand(instr, &instr->operands[0], 2, true);
		append_text(instr, ", ");
		print_operand(instr, &instr->operands[1], 2, false);
	}
}

void handler_bound(struct instruction *instr)
{
	if (x64id_is_64bit) {
		replace_with_data(instr);
		return;
	}
	if (instr->operand_count < 2)
		return;
	print_operand(instr, &instr->operands[1], get_operand_size(instr), false);
	append_text(instr, ", ");
	print_operand(instr, &instr->operands[0], 0, false);
}

void handler_x86_only(struct instruction *instr)
{
	if (!x64id_is_64bit)
		return;
	replace_with_data(instr);
}

static void handle_rm_immediate(struct instruction *instr, uint8_t size);

void handler_op82(struct instruction *instr)
{
	if (x64id_is_64bit) {
		handler_x86_only(instr);
		return;
	}
	handle_rm_immediate(instr, 1);
}

void handler_string(struct instruction *instr)
{
	uint8_t opcode = instr->op[0];
	const char *mnemonic;
	bool word = (instr->set_prefix & OS) != 0;
	bool qword = (instr->set_prefix & OP64) != 0;

	if (opcode >= 0x6C && opcode <= 0x6F) {
		if (opcode == 0x6C)
			mnemonic = "insb";
		else if (opcode == 0x6E)
			mnemonic = "outsb";
		else if (word)
			mnemonic = opcode == 0x6D ? "insw" : "outsw";
		else
			mnemonic = opcode == 0x6D ? "insd" : "outsd";
	} else {
		switch (opcode) {
		case 0xA4:
			mnemonic = "movsb";
			break;
		case 0xA5:
			mnemonic = qword ? "movsq" : word ? "movsw" : "movsd";
			break;
		case 0xA6:
			mnemonic = "cmpsb";
			break;
		case 0xA7:
			mnemonic = qword ? "cmpsq" : word ? "cmpsw" : "cmpsd";
			break;
		case 0xAA:
			mnemonic = "stosb";
			break;
		case 0xAB:
			mnemonic = qword ? "stosq" : word ? "stosw" : "stosd";
			break;
		case 0xAC:
			mnemonic = "lodsb";
			break;
		case 0xAD:
			mnemonic = qword ? "lodsq" : word ? "lodsw" : "lodsd";
			break;
		case 0xAE:
			mnemonic = "scasb";
			break;
		default:
			mnemonic = qword ? "scasq" : word ? "scasw" : "scasd";
			break;
		}
	}
	reset_disasm(instr);
	append_mnemonic(instr, mnemonic);
}

void handler_M(struct instruction *instr)
{
	if (instr->operand_count > 0 &&
		instr->operands[0].kind == DECODED_OPERAND_MEMORY) {
		print_operand(instr, &instr->operands[0], 0, false);
		return;
	}
	replace_with_data(instr);
}

static void handle_rm_immediate(struct instruction *instr, uint8_t size)
{
	if (instr->operand_count < 3)
		return;

	print_operand(instr, &instr->operands[0], size, true);
	append_text(instr, ", ");
	print_operand(instr, &instr->operands[instr->operand_count - 1], size,
				  false);
}

void handler_Eb_Ib(struct instruction *instr) { handle_rm_immediate(instr, 1); }
void handler_Ev_Iz(struct instruction *instr)
{
	handle_rm_immediate(instr, get_operand_size(instr));
}

static void handle_accumulator_immediate(struct instruction *instr,
										 uint8_t size)
{
	if (instr->operand_count == 0)
		return;

	append_text(instr, get_reg_name(size, !!(instr->set_field & REX), 0));
	append_text(instr, ", ");
	print_operand(instr, &instr->operands[instr->operand_count - 1], size,
				  false);
}

void handler_Al_Ib(struct instruction *instr)
{
	handle_accumulator_immediate(instr, 1);
}
void handler_Al_Iz(struct instruction *instr)
{
	handle_accumulator_immediate(instr, get_operand_size(instr));
}

void handler_Reg_In_Opcode(struct instruction *instr)
{
	uint8_t size;

	if (instr->operand_count == 0)
		return;

	size = x64id_is_64bit ? 8 : 4;

	if (instr->set_prefix & OS)
		size = x64id_is_64bit ? 4 : 2;
	print_operand(instr, &instr->operands[instr->operand_count - 1], size,
				  false);
}

static void handle_opcode_register_immediate(struct instruction *instr,
											 uint8_t size)
{
	if (instr->operand_count < 2)
		return;

	print_operand(instr, &instr->operands[instr->operand_count - 1], size,
				  false);
	append_text(instr, ", ");
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

void handler_push(struct instruction *instr)
{
	if (x64id_is_64bit) {
		replace_with_data(instr);
		return;
	}

	append_text(instr, "es");
}

void handler_Jb(struct instruction *instr) { handler_relative_target(instr); }
void handler_Jz(struct instruction *instr) { handler_relative_target(instr); }

void handler_None(struct instruction *instr) { (void)instr; }

void handler_nop(struct instruction *instr)
{
	if (x64id_is_64bit && instr->rex.bits.rex_b) {
		reset_disasm(instr);
		append_mnemonic(instr, "xchg");
		handler_xchg_accumulator(instr);
	}
}

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

		if (pp == 2 && instr->op[0] == 0x12)
			mnemonic = "vmovsldup";
		if (pp == 2 && instr->op[0] == 0x16)
			mnemonic = "vmovshdup";
		if (pp == 3 && instr->op[0] == 0x12)
			mnemonic = "vmovddup";
		if (mnemonic != NULL) {
			append_mnemonic(instr, mnemonic);
			handle_modrm_pair(instr, vex_vector_size(instr), true);
			return;
		}
	}

	appendf(instr, "vex.%u 0x%02x", vex_map(instr), instr->op[0]);
}

void x64id_disasm(struct instruction *instr)
{
	reset_disasm(instr);

	if (instr->set_prefix & VEX) {
		disasm_vex(instr);
		return;
	}

#include "tools/generated_opcodes.h"
}
