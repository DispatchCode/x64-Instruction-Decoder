#include <stdio.h>
#include "disasm.h"

// 32 or 64 bti mode: this must be set before use the decode function!
extern int x64id_arch;


#define  MAX_STR_LEN   256

#define INSTR_CONCAT(s, fmt) \
		instr->disasm_str_len += snprintf(instr->disasm + instr->disasm_str_len, MAX_INSTR_LEN_STR, fmt, s) 


// TODO  this is just temporary, the register table must be changed or this should be handled in another way
static inline const char* get_reg_name(struct instruction *instr, uint8_t size, int reg_index) {
	int size_index = size;

	switch(size) {
		case 1:
			if (instr->set_field & REX)
				size_index = 1;
		break;
		case 4: size_index = 3; break;
		case 8: size_index = 4; break;
		case 16: size_index = 5; break;
		case 32: size_index = 6; break;
		default: return "??";
	}

	return REGISTER_TABLE[size_index][reg_index];
}


// Returns the operand size in bytes (2, 4, or 8)
// Note: This is for "v" operands (Ev, Gv, Iz), NOT for "b" (byte) operands.
static int get_operand_size(struct instruction *instr) {
    if (instr->rex.bits.rex_w)
        return 8;

	if(instr->set_prefix & OS)
		return 2;

    return 4;
}

// Address Size operand: this is used when registers are used in the memory access
static int get_address_size(struct instruction *instr) {
	// 64-bit mode
	bool has_addr_size = instr->set_prefix & AS;

	if(x64id_arch == X64) {
		if(has_addr_size) return 4;
		return 8;
	}
	// 32-bit mode
	if(has_addr_size) return 2;
	return 4;
}

static inline void print_memory_operand(struct instruction *instr, uint8_t size) {
	uint8_t index  = instr->sib.bits.index;
	uint8_t base   = instr->sib.bits.base;
	uint8_t mod	   = instr->modrm.bits.mod;
	uint8_t rm     = instr->modrm.bits.rm;
	uint8_t scaled = 1 << instr->sib.bits.scaled;
	bool has_base  = 0;

	int addr_size = get_address_size(instr);

	if (instr->set_field & SIB) {
		index += (instr->rex.bits.rex_x << 3);
		base  += (instr->rex.bits.rex_b << 3);

		// SIB.base = 0x05 && mod = 0 is a special encoding
		// used for displacement only. If is not the case,
		// then we have "base"
		if (! (mod == 0 && base == 5)) {
			has_base = 1;
			INSTR_CONCAT(get_reg_name(instr, addr_size, base), "%s");
		}

		// There is also "index"?
		if (index != 4) {
			if (has_base) INSTR_CONCAT("+", "%s");
			INSTR_CONCAT(get_reg_name(instr, addr_size, index), "%s");
			if (scaled > 1) {
				INSTR_CONCAT("*", "%s");
				INSTR_CONCAT(scaled, "%x");
			}
			has_base = 1;
		}
	}

	// RIP relative addressing
	else if (mod == 0 && rm == 5) {
		has_base = 1;
		INSTR_CONCAT("RIP", "%s");
	}
	
	// Register addressing
	else {
		base = rm;
		base += (instr->rex.bits.rex_b << 3);

		INSTR_CONCAT(get_reg_name(instr, addr_size, base), "%s");
		has_base = 1;
	}

	// Displacement
	if (mod == 1 || mod == 2 || (mod == 0 && rm == 5) ||
		(mod == 0 && rm == 4 && (instr->sib.bits.base & 7) == 5)
	) {
		
		if(!has_base) INSTR_CONCAT(instr->disp,"0x%x");
		else {
			if(instr->disp >= 0)
				INSTR_CONCAT(" + ", "%s");
			else
				INSTR_CONCAT(" - ", "%s");

			INSTR_CONCAT(instr->disp, "0x%x");
		}
	}
}

static inline void print_op_G(struct instruction *instr, uint8_t size) {
	uint8_t reg_index = instr->modrm.bits.reg;

	reg_index += (instr->rex.bits.rex_r << 3);
	INSTR_CONCAT(get_reg_name(instr,size,reg_index), "%s");
}

static inline void print_op_E(struct instruction *instr, uint8_t size) {
	uint8_t mod = instr->modrm.bits.mod;

	// registers only
	if (mod == 3) {
		uint8_t rm  = instr->modrm.bits.rm;
		rm += (instr->rex.bits.rex_b << 3);
		INSTR_CONCAT(get_reg_name(instr, size, rm), "%s");
	}
	else {
		switch(size) {
			case 1: INSTR_CONCAT("BYTE PTR [", "%s"); break;
			case 2: INSTR_CONCAT("WORD PTR [", "%s"); break;
			case 4: INSTR_CONCAT("DWORD PTR [", "%s"); break;
			case 8: INSTR_CONCAT("QWORD PTR [", "%s"); break;
			default: INSTR_CONCAT("Invalid size", "%s"); break;
		}

		print_memory_operand(instr, size);

		INSTR_CONCAT("]", "%s");
	}
}

// TODO that's very likely this can be refactored along with the opcode counter.
//		Use the direction bit and create a counter for the opcode array
static void generic_handler_EG(struct instruction *instr, uint8_t size) {
	// 2nd bit is the direction (operation to or from register)
	uint8_t direction = instr->op[instr->op_cnt ? 1 : 0] & 2;	

	// Gv_Ev case
	if(direction) {
		print_op_G(instr, size);
		INSTR_CONCAT(",", "%s");
		print_op_E(instr, size);
	}
	// Ev_Gv case
	else {
		print_op_E(instr, size);
		INSTR_CONCAT(",", "%s");
		print_op_G(instr, size);
	}
}

void handler_Gv_Ev(struct instruction *instr) {
	uint8_t size = get_operand_size(instr); 
	generic_handler_EG(instr, size);
}

void handler_Ev_Gv(struct instruction *instr) {
	uint8_t size = get_operand_size(instr); 
	generic_handler_EG(instr, size);
}

/*
 * Kind of special compared to others: register encoded into the opcode
 * Currently handle PUSH / POP
 */
static void generic_handler_reg_in_opcode(struct instruction *instr) {
	bool has_operand_size = !!(instr->set_prefix & OS);
	uint8_t opcode = instr->op[instr->op_cnt ? 1 : 0]; // "primary" opcode, after 0x0f if any
	// rex.b: extension to ModRm.rm field (or SIB byte)
	uint8_t op_index = (instr->rex.bits.rex_b << 3);
	uint8_t size = 8; // default size

	// 64-bit mode...
	if(x64id_arch == X64) {
		// ... with operand size prefix: 4-byte
		if(has_operand_size) size = 4;
	}
	// 32-bit mode, default to 4 bytes
	else {
		size = 4;
		if(has_operand_size) size = 2;
	}
	
	// TODO this is currently implemented only for 0x50xx
	if(opcode & 0x50) {
		op_index += (opcode & 0x7);
		INSTR_CONCAT(get_reg_name(instr, size, op_index), "%s");
	}
}

void handler_Reg_In_Opcode(struct instruction *instr) {
	generic_handler_reg_in_opcode(instr);
}

void handler_None(struct instruction *instr) {
	/* Nothing to do, 1-byte instr. (eg. RET, NOP,...)*/
}

void x64id_disasm(struct instruction *instr) {
	#include "tools/generated_opcodes.h"
}

