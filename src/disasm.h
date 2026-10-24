/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef X64ID_DISASM_H
#define X64ID_DISASM_H

#include "x64id.h"

void x64id_disasm(struct instruction *instr);
void handler_Gv_Ev(struct instruction *instr);
void handler_Gv_Ew(struct instruction *instr);
void handler_Gv_Eb(struct instruction *instr);
void handler_Gv_Ev_Iz(struct instruction *instr);
void handler_Gv_Ev_Ib(struct instruction *instr);
void handler_Ev_Gv_Ib(struct instruction *instr);
void handler_Ev_Gv(struct instruction *instr);
void handler_Eb_Gb(struct instruction *instr);
void handler_Gb_Eb(struct instruction *instr);
void handler_Eb_Ib(struct instruction *instr);
void handler_Ev_Iz(struct instruction *instr);
void handler_Ew(struct instruction *instr);
void handler_Ev(struct instruction *instr);
void handler_Eb(struct instruction *instr);
void handler_Ev64(struct instruction *instr);
void handler_Lea(struct instruction *instr);
void handler_pop_Ev(struct instruction *instr);
void handler_push_imm(struct instruction *instr);
void handler_xchg_accumulator(struct instruction *instr);
void handler_ret_imm(struct instruction *instr);
void handler_int_imm(struct instruction *instr);
void handler_shift_one(struct instruction *instr);
void handler_shift_cl(struct instruction *instr);
void handler_segment_stack(struct instruction *instr);
void handler_far_load(struct instruction *instr);
void handler_endbr(struct instruction *instr);
void handler_moffs(struct instruction *instr);
void handler_integer_alias(struct instruction *instr);
void handler_enter(struct instruction *instr);
void handler_far_pointer(struct instruction *instr);
void handler_io(struct instruction *instr);
void handler_segment_move(struct instruction *instr);
void handler_arpl_movsxd(struct instruction *instr);
void handler_bound(struct instruction *instr);
void handler_x86_only(struct instruction *instr);
void handler_op82(struct instruction *instr);
void handler_string(struct instruction *instr);
void handler_jrcxz(struct instruction *instr);
void handler_aam_aad(struct instruction *instr);
void handler_special_move(struct instruction *instr);
void handler_Ev_Gv_CL(struct instruction *instr);
void handler_bswap(struct instruction *instr);
void handler_M(struct instruction *instr);
void handler_Al_Ib(struct instruction *instr);
void handler_Al_Iz(struct instruction *instr);
void handler_Reg_In_Opcode(struct instruction *instr);
void handler_Reg8_In_Opcode_Ib(struct instruction *instr);
void handler_Reg_In_Opcode_Iz(struct instruction *instr);
void handler_push(struct instruction *instr);
void handler_Jb(struct instruction *instr);
void handler_Jz(struct instruction *instr);
void handler_None(struct instruction *instr);
void handler_nop(struct instruction *instr);

#endif
