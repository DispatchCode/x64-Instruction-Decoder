#ifndef X64ID_DISASM_H
#define X64ID_DISASM_H

#include "x64id.h"

void x64id_disasm(struct instruction *instr);
void handler_Gv_Ev(struct instruction *instr);
void handler_Ev_Gv(struct instruction *instr);
void handler_Eb_Gb(struct instruction *instr);
void handler_Gb_Eb(struct instruction *instr);
void handler_Eb_Ib(struct instruction *instr);
void handler_Ev_Iz(struct instruction *instr);
void handler_Ew(struct instruction *instr);
void handler_M(struct instruction *instr);
void handler_Al_Ib(struct instruction *instr);
void handler_Al_Iz(struct instruction *instr);
void handler_Reg_In_Opcode(struct instruction *instr);
void handler_Reg8_In_Opcode_Ib(struct instruction *instr);
void handler_Reg_In_Opcode_Iz(struct instruction *instr);
void handler_Jb(struct instruction *instr);
void handler_Jz(struct instruction *instr);
void handler_None(struct instruction *instr);

#endif
