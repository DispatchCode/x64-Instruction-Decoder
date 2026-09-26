#include "x64id.h"
#include "disasm.h"
#include <stdio.h>

// 32 or 64 bti mode: this must be set before use the decode function!
// By default, select x64
int x64id_arch = X64;

static size_t *imm_table[4] = {0, imm_byte_2b, imm_byte_3b_38, imm_byte_3b_3A};
static size_t *modrm_table[4] = {0, modrm_2b, modreg_3b_38, modreg_3b_3A};

static int x64id_address_size(const struct instruction *instr)
{
	if (x64id_arch == X64)
		return (instr->set_prefix & AS) ? 4 : 8;
	return (instr->set_prefix & AS) ? 2 : 4;
}

static int64_t x64id_signed_displacement(const struct instruction *instr)
{
	if (instr->disp_len == 1)
		return (int8_t)instr->disp;
	if (instr->disp_len == 4)
		return (int32_t)instr->disp;
	return 0;
}

static uint8_t x64id_vex_prefix_byte2(const struct instruction *instr)
{
	return instr->vex[1];
}

static uint8_t x64id_vex_ext_r(const struct instruction *instr)
{
	if (!(instr->set_prefix & VEX))
		return 0;
	return (uint8_t)((~x64id_vex_prefix_byte2(instr) >> 7) & 1);
}

static uint8_t x64id_vex_ext_x(const struct instruction *instr)
{
	if (!(instr->set_prefix & VEX) || instr->vex[0] != 0xC4)
		return 0;
	return (uint8_t)((~instr->vex[1] >> 6) & 1);
}

static uint8_t x64id_vex_ext_b(const struct instruction *instr)
{
	if (!(instr->set_prefix & VEX) || instr->vex[0] != 0xC4)
		return 0;
	return (uint8_t)((~instr->vex[1] >> 5) & 1);
}

/* Build a stable operand view once decoding is complete.  The disassembler
 * then works with these operands instead of interpreting ModRM/SIB/REX. */
static void x64id_decode_operands(struct instruction *instr)
{
	uint8_t op_index = instr->op_cnt > 1 ? 1 : 0;

	if (instr->set_field & MODRM) {
		struct decoded_operand *rm = &instr->operands[instr->operand_count++];
		uint8_t mod = instr->modrm.bits.mod;
		uint8_t rm_index = instr->modrm.bits.rm;
		uint8_t rex_b = instr->rex.bits.rex_b | x64id_vex_ext_b(instr);

		if (mod == 3) {
			rm->kind = DECODED_OPERAND_REGISTER;
			rm->reg = (uint8_t)(rm_index + (rex_b << 3));
		} else {
			rm->kind = DECODED_OPERAND_MEMORY;
			rm->address_size = (uint8_t)x64id_address_size(instr);
			rm->displacement = x64id_signed_displacement(instr);

			if (instr->set_field & SIB) {
				uint8_t sib_base = instr->sib.bits.base;
				uint8_t sib_index = instr->sib.bits.index;
				rm->scale = (uint8_t)(1u << instr->sib.bits.scaled);
				if (!(mod == 0 && sib_base == 5)) {
					rm->has_base = true;
					rm->base = (uint8_t)(sib_base + (rex_b << 3));
				}
				if (sib_index != 4 || instr->rex.bits.rex_x ||
					x64id_vex_ext_x(instr)) {
					rm->has_index = true;
					rm->index = (uint8_t)(sib_index + ((instr->rex.bits.rex_x |
														x64id_vex_ext_x(instr))
													   << 3));
				}
			} else if (mod == 0 && rm_index == 5) {
				rm->rip_relative = x64id_arch == X64 && rm->address_size == 8;
				if (!rm->rip_relative)
					rm->has_base = false;
			} else {
				rm->has_base = true;
				rm->base = (uint8_t)(rm_index + (rex_b << 3));
			}
			/* A displacement-only address is an absolute unsigned offset. */
			if (!rm->has_base && !rm->has_index && !rm->rip_relative &&
				instr->disp_len == 4)
				rm->displacement = (int64_t)(uint32_t)instr->disp;
		}

		struct decoded_operand *reg = &instr->operands[instr->operand_count++];
		reg->kind = DECODED_OPERAND_REGISTER;
		reg->reg =
			(uint8_t)(instr->modrm.bits.reg +
					  ((instr->rex.bits.rex_r | x64id_vex_ext_r(instr)) << 3));
	}

	if (instr->set_field & IMM) {
		struct decoded_operand *imm = &instr->operands[instr->operand_count++];
		imm->kind = DECODED_OPERAND_IMMEDIATE;
		imm->immediate = instr->imm;
	}

	/* INC/DEC in 32-bit mode and PUSH/POP use the low opcode bits as a
	 * register number. */
	if (!(instr->set_field & MODRM)) {
		uint8_t opcode = instr->op[op_index];
		if ((opcode >= 0x40 && opcode <= 0x5f) ||
			(opcode >= 0xb0 && opcode <= 0xbf)) {
			struct decoded_operand *reg =
				&instr->operands[instr->operand_count++];
			reg->kind = DECODED_OPERAND_REGISTER;
			reg->reg = (uint8_t)((opcode & 7) + (instr->rex.bits.rex_b << 3));
		}
	}
}

static inline void x64id_vex_decode(struct instruction *instr, const char *data,
									uint8_t vex_size)
{
	memcpy(instr->vex, (data + instr->length), vex_size);
	instr->vex_cnt += vex_size;
	instr->length += vex_size;

	instr->op[0] = *(data + instr->length);
	instr->length++;

	instr->set_prefix |= VEX;

	if (instr->vex[0] == 0xC5) {
#ifdef _ENABLE_VEX_INFO
		instr->_vex.type = instr->vex[0];
		instr->_vex.val5 = instr->vex[1];
#endif

		x64id_decode_modrm(instr, data, modrm_2b, imm_byte_2b, NULL);
	} else if (instr->vex[0] == 0xC4) {

#ifdef _ENABLE_VEX_INFO
		instr->_vex.type = instr->vex[0];
		memcpy(&instr->_vex.val4, &instr->vex[1], 2);
#endif

		int8_t index = instr->vex[1] & 0x3;
		x64id_decode_modrm(instr, data, modrm_table[index], imm_table[index],
						   NULL);
	}
	// TODO  XOP, 0x8F
}

static inline int x64id_vex_size(struct instruction *instr, const char *data)
{
	uint8_t curr_byte = (uint8_t)*(data + instr->length);
	uint8_t next_byte = (uint8_t)*(data + instr->length + 1);

	// 3-byte VEX prefix
	if ((x64id_arch == X86 && curr_byte == 0xC4 && (next_byte >> 6) == 3) ||
		(x64id_arch == X64 && curr_byte == 0xC4))
		return 3;
	// 2-byte VEX prefix
	else if ((x64id_arch == X86 && curr_byte == 0xC5 && (next_byte & 0x80)) ||
			 (x64id_arch == X64 && curr_byte == 0xC5))
		return 2;

	return 0;
}

static inline bool x64id_check_sib(uint8_t mod, uint8_t rm)
{
	return mod < 3 && rm == 4;
}

static inline int x64id_displacement_size(uint8_t mod, uint8_t rm)
{
	if ((mod == 0x02) || (rm == 0x05 && !mod))
		return 4;
	else if (mod == 0x01)
		return 1;
	return 0;
}

static inline int x64id_imm_size(struct instruction *instr, size_t val)
{
	switch (val) {
	case b:
		return 1;
	case v:
		if (x64id_arch == X64 && instr->set_prefix & OP64)
			return 8;
		if (instr->set_prefix & OS)
			return 2;
		return 4;
	case z:
		if (instr->set_prefix & OS)
			return 2;
		return 4;
	case z1:
		if (x64id_arch == X64)
			return instr->set_prefix & AS ? 4 : 8;
		return instr->set_prefix & AS ? 2 : 4;
	case p:
		if (instr->set_prefix & OS) {
			if (x64id_arch == X86)
				return 4;
			return 8;
		}
		return 6;
	case w:
		return 2;
	case wb:
		return 3; // TODO  ENTER iw, ib
	case gr3b:
		if (!instr->modrm.bits.reg)
			return 1;
		return 0;
	case gr3z:
		if (!instr->modrm.bits.reg) {
			if (instr->set_prefix & OS)
				return 2;
			return 4;
		}
		return 0;

	default:
		return 0;
	}
}

static void x64id_decode_modrm(struct instruction *instr,
							   const char *start_data,
							   const size_t *modrm_table,
							   const size_t *imm_table, const size_t *jcc_table)
{
	int op_index = instr->op_cnt ? 1 : 0;

	size_t val;
	if ((val = modrm_table[instr->op[op_index]])) {
		instr->set_field |= MODRM;

		if (val == X87_FPU)
			instr->set_field |= FPU;

		uint8_t curr = *(start_data + instr->length);

		instr->modrm.value = curr;
		instr->length++;

		uint8_t mod_val = instr->modrm.bits.mod, rm_val = instr->modrm.bits.rm;

		if (x64id_check_sib(instr->modrm.bits.mod, instr->modrm.bits.rm)) {
			instr->set_field |= SIB;

			instr->sib.value = (uint8_t)*(start_data + instr->length);
			instr->length++;

			if (instr->sib.bits.base == 0x05) {
				instr->set_field |= DISP;
				mod_val = instr->modrm.bits.mod;
				rm_val = instr->sib.bits.base;
			}
		}

		instr->disp_len = x64id_displacement_size(mod_val, rm_val);
		if (instr->disp_len || instr->set_field & DISP) {
			memcpy(&instr->disp, (start_data + instr->length), instr->disp_len);
			instr->length += instr->disp_len;
			instr->set_field |= DISP;
		}
	}

	instr->imm_len = x64id_imm_size(instr, imm_table[instr->op[op_index]]);
	if (instr->imm_len) {
		instr->set_field |= IMM;
		memcpy(&instr->imm, (start_data + instr->length), instr->imm_len);
		instr->length += instr->imm_len;
	}

	uint16_t value = 0;
	if (jcc_table != NULL && ((value = jcc_table[instr->op[op_index]]))) {
		switch (value) {
		case j1:
			instr->jcc_type = JMP_SHORT;
			break;
		case j2:
			instr->jcc_type = JMP_FAR;
			break;
		case jc1:
			instr->jcc_type = JCC_SHORT;
			break;
		case jc2:
			instr->jcc_type = JCC_FAR;
		default:
			break; // avoid compiler warnings
		}

		// 1-byte
		if (value & 0x10)
			instr->label =
				(uint64_t)start_data + ((int8_t)instr->imm) + instr->length;
		// 4-byte
		else
			instr->label =
				(uint64_t)start_data + ((int64_t)instr->imm) + instr->length;
	}
}

static int x64id_decode_2b(struct instruction *instr, const char *data_src)
{
	instr->set_prefix |= ESCAPE;
	uint8_t curr = *(data_src + instr->length);

	instr->op[instr->op_cnt++] = curr;
	instr->length++;

	if (curr == 0x3A || curr == 0x38) {
		instr->set_prefix |= OP3B;

		instr->prefixes[instr->prefix_cnt++] = curr;
		instr->length++;
		instr->op[instr->op_cnt++] = *(data_src + instr->length);
		instr->length++;

		if (curr == 0x3A)
			x64id_decode_modrm(instr, data_src, modreg_3b_3A, imm_byte_3b_3A,
							   NULL);
		else
			x64id_decode_modrm(instr, data_src, modreg_3b_38, imm_byte_3b_38,
							   NULL);

		return instr->length;
	}

	x64id_decode_modrm(instr, data_src, modrm_2b, imm_byte_2b, op2b_labels);

	return instr->length;
}

int x64id_decode(struct instruction *instr, char *data, int offset)
{
	memset(instr, 0, sizeof(struct instruction));

	char *start_data = (data + offset);
	uint8_t curr = *start_data;

	while (x86_64_prefix[curr] & x64id_arch) {
		switch (curr) {
		case 0x26:
			instr->set_prefix |= ES;
			break;
		case 0x2E:
			instr->set_prefix |= CS;
			break;
		case 0x36:
			instr->set_prefix |= SS;
			break;
		case 0x3E:
			instr->set_prefix |= DS;
			break;
		case 0x48:
		case 0x49:
			if (x64id_arch == X64)
				instr->set_prefix |= OP64;
			break;
		case 0x64:
			instr->set_prefix |= FS;
			break;
		case 0x65:
			instr->set_prefix |= GS;
			break;
		case 0x66:
			instr->set_prefix |= OS;
			break;
		case 0x67:
			instr->set_prefix |= AS;
			break;
		case 0xF2:
			instr->set_prefix |= REPNE;
			break;
		case 0xF3:
			instr->set_prefix |= REPE;
			break;
		}

		instr->set_field |= PREFIX;
		instr->prefixes[instr->prefix_cnt] = curr;
		instr->prefix_cnt++;
		instr->length++;

		// Rex prefix
		// TODO 64-bit mode: IF OP == 90h and REX.B == 1,
		//  then the instruction is XCHG r8, rAX
		if (x64id_arch == X64 && (curr >= 0x40 && curr <= 0x4F)) {
			instr->rex.value = curr;
			instr->set_field |= REX;
			if (instr->rex.bits.rex_w)
				instr->set_prefix |= OP64;
		} else if (curr == 0x0F) {
			instr->op[instr->op_cnt++] = curr;
			x64id_decode_2b(instr, start_data);
#ifdef _ENABLE_RAW_BYTES
			memcpy(instr->instr, start_data, instr->length);
#endif
			x64id_decode_operands(instr);
			x64id_disasm(instr);
			return instr->length;
		}

		curr = (uint8_t)*(start_data + instr->length);
	}

	size_t vex_size = x64id_vex_size(instr, start_data);
	if (vex_size)
		x64id_vex_decode(instr, start_data, vex_size);
	else {
		instr->length++;
		instr->op[instr->op_cnt] = curr;
		x64id_decode_modrm(instr, start_data, modrm_1b, imm_byte_1b,
						   op1b_labels);
	}

#ifdef _ENABLE_RAW_BYTES
	memcpy(instr->instr, start_data, instr->length);
#endif

	x64id_decode_operands(instr);
	x64id_disasm(instr);

	return instr->length;
}

void x64id_set_arch(int arch) { x64id_arch = arch; }
