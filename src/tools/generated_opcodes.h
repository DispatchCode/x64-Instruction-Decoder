/* SPDX-License-Identifier: GPL-2.0-only */
/* Generated from definitions.txt by defs2header.py. Do not edit. */
switch (instr->op[0]) {
    case 0x00: {
        append_mnemonic(instr, "add");
        handler_Eb_Gb(instr);
        break;
    }
    case 0x01: {
        append_mnemonic(instr, "add");
        handler_Ev_Gv(instr);
        break;
    }
    case 0x02: {
        append_mnemonic(instr, "add");
        handler_Gb_Eb(instr);
        break;
    }
    case 0x03: {
        append_mnemonic(instr, "add");
        handler_Gv_Ev(instr);
        break;
    }
    case 0x04: {
        append_mnemonic(instr, "add");
        handler_Al_Ib(instr);
        break;
    }
    case 0x05: {
        append_mnemonic(instr, "add");
        handler_Al_Iz(instr);
        break;
    }
    case 0x06: {
        append_mnemonic(instr, "push");
        handler_push(instr);
        break;
    }
    case 0x07: {
        append_mnemonic(instr, "pop");
        handler_segment_stack(instr);
        break;
    }
    case 0x08: {
        append_mnemonic(instr, "or");
        handler_Eb_Gb(instr);
        break;
    }
    case 0x09: {
        append_mnemonic(instr, "or");
        handler_Ev_Gv(instr);
        break;
    }
    case 0x0A: {
        append_mnemonic(instr, "or");
        handler_Gb_Eb(instr);
        break;
    }
    case 0x0B: {
        append_mnemonic(instr, "or");
        handler_Gv_Ev(instr);
        break;
    }
    case 0x0C: {
        append_mnemonic(instr, "or");
        handler_Al_Ib(instr);
        break;
    }
    case 0x0D: {
        append_mnemonic(instr, "or");
        handler_Al_Iz(instr);
        break;
    }
    case 0x0E: {
        append_mnemonic(instr, "push");
        handler_segment_stack(instr);
        break;
    }
    case 0x0F: {
        switch (instr->op[1]) {
            case 0x00: {
                switch (instr->modrm.bits.reg) {
                    case 0: {
                        append_mnemonic(instr, "sldt");
                        handler_Ew(instr);
                        break;
                    }
                    case 1: {
                        append_mnemonic(instr, "str");
                        handler_Ew(instr);
                        break;
                    }
                    case 2: {
                        append_mnemonic(instr, "lldt");
                        handler_Ew(instr);
                        break;
                    }
                    case 3: {
                        append_mnemonic(instr, "ltr");
                        handler_Ew(instr);
                        break;
                    }
                    case 4: {
                        append_mnemonic(instr, "verr");
                        handler_Ew(instr);
                        break;
                    }
                    case 5: {
                        append_mnemonic(instr, "verw");
                        handler_Ew(instr);
                        break;
                    }
                    default:
                        append_text(instr, "(UD Group)");
                        break;
                }
                break;
            }
            case 0x01: {
                switch (instr->modrm.bits.reg) {
                    case 0: {
                        append_mnemonic(instr, "sgdt");
                        handler_M(instr);
                        break;
                    }
                    case 1: {
                        append_mnemonic(instr, "sidt");
                        handler_M(instr);
                        break;
                    }
                    case 2: {
                        append_mnemonic(instr, "lgdt");
                        handler_M(instr);
                        break;
                    }
                    case 3: {
                        append_mnemonic(instr, "lidt");
                        handler_M(instr);
                        break;
                    }
                    case 4: {
                        append_mnemonic(instr, "smsw");
                        handler_Ew(instr);
                        break;
                    }
                    case 6: {
                        append_mnemonic(instr, "lmsw");
                        handler_Ew(instr);
                        break;
                    }
                    case 7: {
                        append_mnemonic(instr, "invlpg");
                        handler_M(instr);
                        break;
                    }
                    default:
                        append_text(instr, "(UD Group)");
                        break;
                }
                break;
            }
            case 0x02: {
                append_mnemonic(instr, "lar");
                handler_Gv_Ew(instr);
                break;
            }
            case 0x03: {
                append_mnemonic(instr, "lsl");
                handler_Gv_Ew(instr);
                break;
            }
            case 0x05: {
                append_mnemonic(instr, "syscall");
                handler_None(instr);
                break;
            }
            case 0x06: {
                append_mnemonic(instr, "clts");
                handler_None(instr);
                break;
            }
            case 0x07: {
                append_mnemonic(instr, "sysret");
                handler_None(instr);
                break;
            }
            case 0x08: {
                append_mnemonic(instr, "invd");
                handler_None(instr);
                break;
            }
            case 0x09: {
                append_mnemonic(instr, "wbinvd");
                handler_None(instr);
                break;
            }
            case 0x0B: {
                append_mnemonic(instr, "ud2");
                handler_None(instr);
                break;
            }
            case 0x18: {
                switch (instr->modrm.bits.reg) {
                    case 0: {
                        append_mnemonic(instr, "prefetchnta");
                        handler_M(instr);
                        break;
                    }
                    case 1: {
                        append_mnemonic(instr, "prefetcht0");
                        handler_M(instr);
                        break;
                    }
                    case 2: {
                        append_mnemonic(instr, "prefetcht1");
                        handler_M(instr);
                        break;
                    }
                    case 3: {
                        append_mnemonic(instr, "prefetcht2");
                        handler_M(instr);
                        break;
                    }
                    default:
                        append_text(instr, "(UD Group)");
                        break;
                }
                break;
            }
            case 0x1E: {
                if ((instr->set_prefix & REPE)) {
                    append_mnemonic(instr, "endbr");
                    handler_endbr(instr);
                }
                else {
                    append_unknown_opcode(instr, 1);
                }
                break;
            }
            case 0x1F: {
                switch (instr->modrm.bits.reg) {
                    case 0: {
                        append_mnemonic(instr, "nop");
                        handler_None(instr);
                        break;
                    }
                    default:
                        append_text(instr, "(UD Group)");
                        break;
                }
                break;
            }
            case 0x20: {
                append_mnemonic(instr, "mov");
                handler_special_move(instr);
                break;
            }
            case 0x21: {
                append_mnemonic(instr, "mov");
                handler_special_move(instr);
                break;
            }
            case 0x22: {
                append_mnemonic(instr, "mov");
                handler_special_move(instr);
                break;
            }
            case 0x23: {
                append_mnemonic(instr, "mov");
                handler_special_move(instr);
                break;
            }
            case 0x30: {
                append_mnemonic(instr, "wrmsr");
                handler_None(instr);
                break;
            }
            case 0x31: {
                append_mnemonic(instr, "rdtsc");
                handler_None(instr);
                break;
            }
            case 0x32: {
                append_mnemonic(instr, "rdmsr");
                handler_None(instr);
                break;
            }
            case 0x33: {
                append_mnemonic(instr, "rdpmc");
                handler_None(instr);
                break;
            }
            case 0x34: {
                append_mnemonic(instr, "sysenter");
                handler_None(instr);
                break;
            }
            case 0x35: {
                append_mnemonic(instr, "sysexit");
                handler_None(instr);
                break;
            }
            case 0x40: {
                append_mnemonic(instr, "cmovo");
                handler_Gv_Ev(instr);
                break;
            }
            case 0x41: {
                append_mnemonic(instr, "cmovno");
                handler_Gv_Ev(instr);
                break;
            }
            case 0x42: {
                append_mnemonic(instr, "cmovb");
                handler_Gv_Ev(instr);
                break;
            }
            case 0x43: {
                append_mnemonic(instr, "cmovae");
                handler_Gv_Ev(instr);
                break;
            }
            case 0x44: {
                append_mnemonic(instr, "cmove");
                handler_Gv_Ev(instr);
                break;
            }
            case 0x45: {
                append_mnemonic(instr, "cmovne");
                handler_Gv_Ev(instr);
                break;
            }
            case 0x46: {
                append_mnemonic(instr, "cmovbe");
                handler_Gv_Ev(instr);
                break;
            }
            case 0x47: {
                append_mnemonic(instr, "cmova");
                handler_Gv_Ev(instr);
                break;
            }
            case 0x48: {
                append_mnemonic(instr, "cmovs");
                handler_Gv_Ev(instr);
                break;
            }
            case 0x49: {
                append_mnemonic(instr, "cmovns");
                handler_Gv_Ev(instr);
                break;
            }
            case 0x4A: {
                append_mnemonic(instr, "cmovp");
                handler_Gv_Ev(instr);
                break;
            }
            case 0x4B: {
                append_mnemonic(instr, "cmovnp");
                handler_Gv_Ev(instr);
                break;
            }
            case 0x4C: {
                append_mnemonic(instr, "cmovl");
                handler_Gv_Ev(instr);
                break;
            }
            case 0x4D: {
                append_mnemonic(instr, "cmovge");
                handler_Gv_Ev(instr);
                break;
            }
            case 0x4E: {
                append_mnemonic(instr, "cmovle");
                handler_Gv_Ev(instr);
                break;
            }
            case 0x4F: {
                append_mnemonic(instr, "cmovg");
                handler_Gv_Ev(instr);
                break;
            }
            case 0x77: {
                append_mnemonic(instr, "emms");
                handler_None(instr);
                break;
            }
            case 0x80: {
                append_mnemonic(instr, "jo");
                handler_Jz(instr);
                break;
            }
            case 0x81: {
                append_mnemonic(instr, "jno");
                handler_Jz(instr);
                break;
            }
            case 0x82: {
                append_mnemonic(instr, "jb");
                handler_Jz(instr);
                break;
            }
            case 0x83: {
                append_mnemonic(instr, "jae");
                handler_Jz(instr);
                break;
            }
            case 0x84: {
                append_mnemonic(instr, "je");
                handler_Jz(instr);
                break;
            }
            case 0x85: {
                append_mnemonic(instr, "jne");
                handler_Jz(instr);
                break;
            }
            case 0x86: {
                append_mnemonic(instr, "jbe");
                handler_Jz(instr);
                break;
            }
            case 0x87: {
                append_mnemonic(instr, "ja");
                handler_Jz(instr);
                break;
            }
            case 0x88: {
                append_mnemonic(instr, "js");
                handler_Jz(instr);
                break;
            }
            case 0x89: {
                append_mnemonic(instr, "jns");
                handler_Jz(instr);
                break;
            }
            case 0x8A: {
                append_mnemonic(instr, "jp");
                handler_Jz(instr);
                break;
            }
            case 0x8B: {
                append_mnemonic(instr, "jnp");
                handler_Jz(instr);
                break;
            }
            case 0x8C: {
                append_mnemonic(instr, "jl");
                handler_Jz(instr);
                break;
            }
            case 0x8D: {
                append_mnemonic(instr, "jge");
                handler_Jz(instr);
                break;
            }
            case 0x8E: {
                append_mnemonic(instr, "jle");
                handler_Jz(instr);
                break;
            }
            case 0x8F: {
                append_mnemonic(instr, "jg");
                handler_Jz(instr);
                break;
            }
            case 0x90: {
                append_mnemonic(instr, "seto");
                handler_Eb(instr);
                break;
            }
            case 0x91: {
                append_mnemonic(instr, "setno");
                handler_Eb(instr);
                break;
            }
            case 0x92: {
                append_mnemonic(instr, "setb");
                handler_Eb(instr);
                break;
            }
            case 0x93: {
                append_mnemonic(instr, "setae");
                handler_Eb(instr);
                break;
            }
            case 0x94: {
                append_mnemonic(instr, "sete");
                handler_Eb(instr);
                break;
            }
            case 0x95: {
                append_mnemonic(instr, "setne");
                handler_Eb(instr);
                break;
            }
            case 0x96: {
                append_mnemonic(instr, "setbe");
                handler_Eb(instr);
                break;
            }
            case 0x97: {
                append_mnemonic(instr, "seta");
                handler_Eb(instr);
                break;
            }
            case 0x98: {
                append_mnemonic(instr, "sets");
                handler_Eb(instr);
                break;
            }
            case 0x99: {
                append_mnemonic(instr, "setns");
                handler_Eb(instr);
                break;
            }
            case 0x9A: {
                append_mnemonic(instr, "setp");
                handler_Eb(instr);
                break;
            }
            case 0x9B: {
                append_mnemonic(instr, "setnp");
                handler_Eb(instr);
                break;
            }
            case 0x9C: {
                append_mnemonic(instr, "setl");
                handler_Eb(instr);
                break;
            }
            case 0x9D: {
                append_mnemonic(instr, "setge");
                handler_Eb(instr);
                break;
            }
            case 0x9E: {
                append_mnemonic(instr, "setle");
                handler_Eb(instr);
                break;
            }
            case 0x9F: {
                append_mnemonic(instr, "setg");
                handler_Eb(instr);
                break;
            }
            case 0xA0: {
                append_mnemonic(instr, "push");
                handler_segment_stack(instr);
                break;
            }
            case 0xA1: {
                append_mnemonic(instr, "pop");
                handler_segment_stack(instr);
                break;
            }
            case 0xA2: {
                append_mnemonic(instr, "cpuid");
                handler_None(instr);
                break;
            }
            case 0xA3: {
                append_mnemonic(instr, "bt");
                handler_Ev_Gv(instr);
                break;
            }
            case 0xA4: {
                append_mnemonic(instr, "shld");
                handler_Ev_Gv_Ib(instr);
                break;
            }
            case 0xA5: {
                append_mnemonic(instr, "shld");
                handler_Ev_Gv_CL(instr);
                break;
            }
            case 0xA8: {
                append_mnemonic(instr, "push");
                handler_segment_stack(instr);
                break;
            }
            case 0xA9: {
                append_mnemonic(instr, "pop");
                handler_segment_stack(instr);
                break;
            }
            case 0xAB: {
                append_mnemonic(instr, "bts");
                handler_Ev_Gv(instr);
                break;
            }
            case 0xAC: {
                append_mnemonic(instr, "shrd");
                handler_Ev_Gv_Ib(instr);
                break;
            }
            case 0xAD: {
                append_mnemonic(instr, "shrd");
                handler_Ev_Gv_CL(instr);
                break;
            }
            case 0xAF: {
                append_mnemonic(instr, "imul");
                handler_Gv_Ev(instr);
                break;
            }
            case 0xB0: {
                append_mnemonic(instr, "cmpxchg");
                handler_Eb_Gb(instr);
                break;
            }
            case 0xB1: {
                append_mnemonic(instr, "cmpxchg");
                handler_Ev_Gv(instr);
                break;
            }
            case 0xB3: {
                append_mnemonic(instr, "btr");
                handler_Ev_Gv(instr);
                break;
            }
            case 0xB6: {
                append_mnemonic(instr, "movzx");
                handler_Gv_Eb(instr);
                break;
            }
            case 0xB7: {
                append_mnemonic(instr, "movzx");
                handler_Gv_Ew(instr);
                break;
            }
            case 0xB8: {
                if ((instr->set_prefix & REPE)) {
                    append_mnemonic(instr, "popcnt");
                    handler_Gv_Ev(instr);
                }
                else {
                    append_unknown_opcode(instr, 1);
                }
                break;
            }
            case 0xBA: {
                switch (instr->modrm.bits.reg) {
                    case 4: {
                        append_mnemonic(instr, "bt");
                        handler_Ev_Iz(instr);
                        break;
                    }
                    case 5: {
                        append_mnemonic(instr, "bts");
                        handler_Ev_Iz(instr);
                        break;
                    }
                    case 6: {
                        append_mnemonic(instr, "btr");
                        handler_Ev_Iz(instr);
                        break;
                    }
                    case 7: {
                        append_mnemonic(instr, "btc");
                        handler_Ev_Iz(instr);
                        break;
                    }
                    default:
                        append_text(instr, "(UD Group)");
                        break;
                }
                break;
            }
            case 0xBB: {
                append_mnemonic(instr, "btc");
                handler_Ev_Gv(instr);
                break;
            }
            case 0xBC: {
                append_mnemonic(instr, "bsf");
                handler_Gv_Ev(instr);
                break;
            }
            case 0xBD: {
                append_mnemonic(instr, "bsr");
                handler_Gv_Ev(instr);
                break;
            }
            case 0xBE: {
                append_mnemonic(instr, "movsx");
                handler_Gv_Eb(instr);
                break;
            }
            case 0xBF: {
                append_mnemonic(instr, "movsx");
                handler_Gv_Ew(instr);
                break;
            }
            case 0xC0: {
                append_mnemonic(instr, "xadd");
                handler_Eb_Gb(instr);
                break;
            }
            case 0xC1: {
                append_mnemonic(instr, "xadd");
                handler_Ev_Gv(instr);
                break;
            }
            case 0xC8: {
                append_mnemonic(instr, "bswap");
                handler_bswap(instr);
                break;
            }
            case 0xC9: {
                append_mnemonic(instr, "bswap");
                handler_bswap(instr);
                break;
            }
            case 0xCA: {
                append_mnemonic(instr, "bswap");
                handler_bswap(instr);
                break;
            }
            case 0xCB: {
                append_mnemonic(instr, "bswap");
                handler_bswap(instr);
                break;
            }
            case 0xCC: {
                append_mnemonic(instr, "bswap");
                handler_bswap(instr);
                break;
            }
            case 0xCD: {
                append_mnemonic(instr, "bswap");
                handler_bswap(instr);
                break;
            }
            case 0xCE: {
                append_mnemonic(instr, "bswap");
                handler_bswap(instr);
                break;
            }
            case 0xCF: {
                append_mnemonic(instr, "bswap");
                handler_bswap(instr);
                break;
            }
            default:
                append_unknown_opcode(instr, 1);
                break;
        }
        break;
    }
    case 0x10: {
        append_mnemonic(instr, "adc");
        handler_Eb_Gb(instr);
        break;
    }
    case 0x11: {
        append_mnemonic(instr, "adc");
        handler_Ev_Gv(instr);
        break;
    }
    case 0x12: {
        append_mnemonic(instr, "adc");
        handler_Gb_Eb(instr);
        break;
    }
    case 0x13: {
        append_mnemonic(instr, "adc");
        handler_Gv_Ev(instr);
        break;
    }
    case 0x14: {
        append_mnemonic(instr, "adc");
        handler_Al_Ib(instr);
        break;
    }
    case 0x15: {
        append_mnemonic(instr, "adc");
        handler_Al_Iz(instr);
        break;
    }
    case 0x16: {
        append_mnemonic(instr, "push");
        handler_segment_stack(instr);
        break;
    }
    case 0x17: {
        append_mnemonic(instr, "pop");
        handler_segment_stack(instr);
        break;
    }
    case 0x18: {
        append_mnemonic(instr, "sbb");
        handler_Eb_Gb(instr);
        break;
    }
    case 0x19: {
        append_mnemonic(instr, "sbb");
        handler_Ev_Gv(instr);
        break;
    }
    case 0x1A: {
        append_mnemonic(instr, "sbb");
        handler_Gb_Eb(instr);
        break;
    }
    case 0x1B: {
        append_mnemonic(instr, "sbb");
        handler_Gv_Ev(instr);
        break;
    }
    case 0x1C: {
        append_mnemonic(instr, "sbb");
        handler_Al_Ib(instr);
        break;
    }
    case 0x1D: {
        append_mnemonic(instr, "sbb");
        handler_Al_Iz(instr);
        break;
    }
    case 0x1E: {
        append_mnemonic(instr, "push");
        handler_segment_stack(instr);
        break;
    }
    case 0x1F: {
        append_mnemonic(instr, "pop");
        handler_segment_stack(instr);
        break;
    }
    case 0x20: {
        append_mnemonic(instr, "and");
        handler_Eb_Gb(instr);
        break;
    }
    case 0x21: {
        append_mnemonic(instr, "and");
        handler_Ev_Gv(instr);
        break;
    }
    case 0x22: {
        append_mnemonic(instr, "and");
        handler_Gb_Eb(instr);
        break;
    }
    case 0x23: {
        append_mnemonic(instr, "and");
        handler_Gv_Ev(instr);
        break;
    }
    case 0x24: {
        append_mnemonic(instr, "and");
        handler_Al_Ib(instr);
        break;
    }
    case 0x25: {
        append_mnemonic(instr, "and");
        handler_Al_Iz(instr);
        break;
    }
    case 0x27: {
        append_mnemonic(instr, "daa");
        handler_x86_only(instr);
        break;
    }
    case 0x28: {
        append_mnemonic(instr, "sub");
        handler_Eb_Gb(instr);
        break;
    }
    case 0x29: {
        append_mnemonic(instr, "sub");
        handler_Ev_Gv(instr);
        break;
    }
    case 0x2A: {
        append_mnemonic(instr, "sub");
        handler_Gb_Eb(instr);
        break;
    }
    case 0x2B: {
        append_mnemonic(instr, "sub");
        handler_Gv_Ev(instr);
        break;
    }
    case 0x2C: {
        append_mnemonic(instr, "sub");
        handler_Al_Ib(instr);
        break;
    }
    case 0x2D: {
        append_mnemonic(instr, "sub");
        handler_Al_Iz(instr);
        break;
    }
    case 0x2F: {
        append_mnemonic(instr, "das");
        handler_x86_only(instr);
        break;
    }
    case 0x30: {
        append_mnemonic(instr, "xor");
        handler_Eb_Gb(instr);
        break;
    }
    case 0x31: {
        append_mnemonic(instr, "xor");
        handler_Ev_Gv(instr);
        break;
    }
    case 0x32: {
        append_mnemonic(instr, "xor");
        handler_Gb_Eb(instr);
        break;
    }
    case 0x33: {
        append_mnemonic(instr, "xor");
        handler_Gv_Ev(instr);
        break;
    }
    case 0x34: {
        append_mnemonic(instr, "xor");
        handler_Al_Ib(instr);
        break;
    }
    case 0x35: {
        append_mnemonic(instr, "xor");
        handler_Al_Iz(instr);
        break;
    }
    case 0x37: {
        append_mnemonic(instr, "aaa");
        handler_x86_only(instr);
        break;
    }
    case 0x38: {
        append_mnemonic(instr, "cmp");
        handler_Eb_Gb(instr);
        break;
    }
    case 0x39: {
        append_mnemonic(instr, "cmp");
        handler_Ev_Gv(instr);
        break;
    }
    case 0x3A: {
        append_mnemonic(instr, "cmp");
        handler_Gb_Eb(instr);
        break;
    }
    case 0x3B: {
        append_mnemonic(instr, "cmp");
        handler_Gv_Ev(instr);
        break;
    }
    case 0x3C: {
        append_mnemonic(instr, "cmp");
        handler_Al_Ib(instr);
        break;
    }
    case 0x3D: {
        append_mnemonic(instr, "cmp");
        handler_Al_Iz(instr);
        break;
    }
    case 0x3F: {
        append_mnemonic(instr, "aas");
        handler_x86_only(instr);
        break;
    }
    case 0x40: {
        append_mnemonic(instr, "inc");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x41: {
        append_mnemonic(instr, "inc");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x42: {
        append_mnemonic(instr, "inc");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x43: {
        append_mnemonic(instr, "inc");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x44: {
        append_mnemonic(instr, "inc");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x45: {
        append_mnemonic(instr, "inc");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x46: {
        append_mnemonic(instr, "inc");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x47: {
        append_mnemonic(instr, "inc");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x48: {
        append_mnemonic(instr, "dec");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x49: {
        append_mnemonic(instr, "dec");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x4A: {
        append_mnemonic(instr, "dec");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x4B: {
        append_mnemonic(instr, "dec");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x4C: {
        append_mnemonic(instr, "dec");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x4D: {
        append_mnemonic(instr, "dec");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x4E: {
        append_mnemonic(instr, "dec");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x4F: {
        append_mnemonic(instr, "dec");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x50: {
        append_mnemonic(instr, "push");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x51: {
        append_mnemonic(instr, "push");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x52: {
        append_mnemonic(instr, "push");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x53: {
        append_mnemonic(instr, "push");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x54: {
        append_mnemonic(instr, "push");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x55: {
        append_mnemonic(instr, "push");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x56: {
        append_mnemonic(instr, "push");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x57: {
        append_mnemonic(instr, "push");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x58: {
        append_mnemonic(instr, "pop");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x59: {
        append_mnemonic(instr, "pop");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x5A: {
        append_mnemonic(instr, "pop");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x5B: {
        append_mnemonic(instr, "pop");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x5C: {
        append_mnemonic(instr, "pop");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x5D: {
        append_mnemonic(instr, "pop");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x5E: {
        append_mnemonic(instr, "pop");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x5F: {
        append_mnemonic(instr, "pop");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x60: {
        append_mnemonic(instr, "pusha");
        handler_x86_only(instr);
        break;
    }
    case 0x61: {
        append_mnemonic(instr, "popa");
        handler_x86_only(instr);
        break;
    }
    case 0x63: {
        append_mnemonic(instr, "arpl");
        handler_arpl_movsxd(instr);
        break;
    }
    case 0x68: {
        append_mnemonic(instr, "push");
        handler_push_imm(instr);
        break;
    }
    case 0x69: {
        append_mnemonic(instr, "imul");
        handler_Gv_Ev_Iz(instr);
        break;
    }
    case 0x6A: {
        append_mnemonic(instr, "push");
        handler_push_imm(instr);
        break;
    }
    case 0x6B: {
        append_mnemonic(instr, "imul");
        handler_Gv_Ev_Ib(instr);
        break;
    }
    case 0x6C: {
        append_mnemonic(instr, "string");
        handler_string(instr);
        break;
    }
    case 0x6D: {
        append_mnemonic(instr, "string");
        handler_string(instr);
        break;
    }
    case 0x6E: {
        append_mnemonic(instr, "string");
        handler_string(instr);
        break;
    }
    case 0x6F: {
        append_mnemonic(instr, "string");
        handler_string(instr);
        break;
    }
    case 0x70: {
        append_mnemonic(instr, "jo");
        handler_Jb(instr);
        break;
    }
    case 0x71: {
        append_mnemonic(instr, "jno");
        handler_Jb(instr);
        break;
    }
    case 0x72: {
        append_mnemonic(instr, "jb");
        handler_Jb(instr);
        break;
    }
    case 0x73: {
        append_mnemonic(instr, "jae");
        handler_Jb(instr);
        break;
    }
    case 0x74: {
        append_mnemonic(instr, "je");
        handler_Jb(instr);
        break;
    }
    case 0x75: {
        append_mnemonic(instr, "jne");
        handler_Jb(instr);
        break;
    }
    case 0x76: {
        append_mnemonic(instr, "jbe");
        handler_Jb(instr);
        break;
    }
    case 0x77: {
        append_mnemonic(instr, "ja");
        handler_Jb(instr);
        break;
    }
    case 0x78: {
        append_mnemonic(instr, "js");
        handler_Jb(instr);
        break;
    }
    case 0x79: {
        append_mnemonic(instr, "jns");
        handler_Jb(instr);
        break;
    }
    case 0x7A: {
        append_mnemonic(instr, "jp");
        handler_Jb(instr);
        break;
    }
    case 0x7B: {
        append_mnemonic(instr, "jnp");
        handler_Jb(instr);
        break;
    }
    case 0x7C: {
        append_mnemonic(instr, "jl");
        handler_Jb(instr);
        break;
    }
    case 0x7D: {
        append_mnemonic(instr, "jge");
        handler_Jb(instr);
        break;
    }
    case 0x7E: {
        append_mnemonic(instr, "jle");
        handler_Jb(instr);
        break;
    }
    case 0x7F: {
        append_mnemonic(instr, "jg");
        handler_Jb(instr);
        break;
    }
    case 0x80: {
        switch (instr->modrm.bits.reg) {
            case 0: {
                append_mnemonic(instr, "add");
                handler_Eb_Ib(instr);
                break;
            }
            case 1: {
                append_mnemonic(instr, "or");
                handler_Eb_Ib(instr);
                break;
            }
            case 2: {
                append_mnemonic(instr, "adc");
                handler_Eb_Ib(instr);
                break;
            }
            case 3: {
                append_mnemonic(instr, "sbb");
                handler_Eb_Ib(instr);
                break;
            }
            case 4: {
                append_mnemonic(instr, "and");
                handler_Eb_Ib(instr);
                break;
            }
            case 5: {
                append_mnemonic(instr, "sub");
                handler_Eb_Ib(instr);
                break;
            }
            case 6: {
                append_mnemonic(instr, "xor");
                handler_Eb_Ib(instr);
                break;
            }
            case 7: {
                append_mnemonic(instr, "cmp");
                handler_Eb_Ib(instr);
                break;
            }
            default:
                append_text(instr, "(UD Group)");
                break;
        }
        break;
    }
    case 0x81: {
        switch (instr->modrm.bits.reg) {
            case 0: {
                append_mnemonic(instr, "add");
                handler_Ev_Iz(instr);
                break;
            }
            case 1: {
                append_mnemonic(instr, "or");
                handler_Ev_Iz(instr);
                break;
            }
            case 2: {
                append_mnemonic(instr, "adc");
                handler_Ev_Iz(instr);
                break;
            }
            case 3: {
                append_mnemonic(instr, "sbb");
                handler_Ev_Iz(instr);
                break;
            }
            case 4: {
                append_mnemonic(instr, "and");
                handler_Ev_Iz(instr);
                break;
            }
            case 5: {
                append_mnemonic(instr, "sub");
                handler_Ev_Iz(instr);
                break;
            }
            case 6: {
                append_mnemonic(instr, "xor");
                handler_Ev_Iz(instr);
                break;
            }
            case 7: {
                append_mnemonic(instr, "cmp");
                handler_Ev_Iz(instr);
                break;
            }
            default:
                append_text(instr, "(UD Group)");
                break;
        }
        break;
    }
    case 0x82: {
        switch (instr->modrm.bits.reg) {
            case 0: {
                append_mnemonic(instr, "add");
                handler_op82(instr);
                break;
            }
            case 1: {
                append_mnemonic(instr, "or");
                handler_op82(instr);
                break;
            }
            case 2: {
                append_mnemonic(instr, "adc");
                handler_op82(instr);
                break;
            }
            case 3: {
                append_mnemonic(instr, "sbb");
                handler_op82(instr);
                break;
            }
            case 4: {
                append_mnemonic(instr, "and");
                handler_op82(instr);
                break;
            }
            case 5: {
                append_mnemonic(instr, "sub");
                handler_op82(instr);
                break;
            }
            case 6: {
                append_mnemonic(instr, "xor");
                handler_op82(instr);
                break;
            }
            case 7: {
                append_mnemonic(instr, "cmp");
                handler_op82(instr);
                break;
            }
            default:
                append_text(instr, "(UD Group)");
                break;
        }
        break;
    }
    case 0x83: {
        switch (instr->modrm.bits.reg) {
            case 0: {
                append_mnemonic(instr, "add");
                handler_Ev_Iz(instr);
                break;
            }
            case 1: {
                append_mnemonic(instr, "or");
                handler_Ev_Iz(instr);
                break;
            }
            case 2: {
                append_mnemonic(instr, "adc");
                handler_Ev_Iz(instr);
                break;
            }
            case 3: {
                append_mnemonic(instr, "sbb");
                handler_Ev_Iz(instr);
                break;
            }
            case 4: {
                append_mnemonic(instr, "and");
                handler_Ev_Iz(instr);
                break;
            }
            case 5: {
                append_mnemonic(instr, "sub");
                handler_Ev_Iz(instr);
                break;
            }
            case 6: {
                append_mnemonic(instr, "xor");
                handler_Ev_Iz(instr);
                break;
            }
            case 7: {
                append_mnemonic(instr, "cmp");
                handler_Ev_Iz(instr);
                break;
            }
            default:
                append_text(instr, "(UD Group)");
                break;
        }
        break;
    }
    case 0x84: {
        append_mnemonic(instr, "test");
        handler_Eb_Gb(instr);
        break;
    }
    case 0x85: {
        append_mnemonic(instr, "test");
        handler_Ev_Gv(instr);
        break;
    }
    case 0x86: {
        append_mnemonic(instr, "xchg");
        handler_Eb_Gb(instr);
        break;
    }
    case 0x87: {
        append_mnemonic(instr, "xchg");
        handler_Ev_Gv(instr);
        break;
    }
    case 0x88: {
        append_mnemonic(instr, "mov");
        handler_Eb_Gb(instr);
        break;
    }
    case 0x89: {
        append_mnemonic(instr, "mov");
        handler_Ev_Gv(instr);
        break;
    }
    case 0x8A: {
        append_mnemonic(instr, "mov");
        handler_Gb_Eb(instr);
        break;
    }
    case 0x8B: {
        append_mnemonic(instr, "mov");
        handler_Gv_Ev(instr);
        break;
    }
    case 0x8C: {
        append_mnemonic(instr, "mov");
        handler_segment_move(instr);
        break;
    }
    case 0x8D: {
        append_mnemonic(instr, "lea");
        handler_Lea(instr);
        break;
    }
    case 0x8E: {
        append_mnemonic(instr, "mov");
        handler_segment_move(instr);
        break;
    }
    case 0x8F: {
        switch (instr->modrm.bits.reg) {
            case 0: {
                append_mnemonic(instr, "pop");
                handler_pop_Ev(instr);
                break;
            }
            default:
                append_text(instr, "(UD Group)");
                break;
        }
        break;
    }
    case 0x90: {
        append_mnemonic(instr, "nop");
        handler_nop(instr);
        break;
    }
    case 0x91: {
        append_mnemonic(instr, "xchg");
        handler_xchg_accumulator(instr);
        break;
    }
    case 0x92: {
        append_mnemonic(instr, "xchg");
        handler_xchg_accumulator(instr);
        break;
    }
    case 0x93: {
        append_mnemonic(instr, "xchg");
        handler_xchg_accumulator(instr);
        break;
    }
    case 0x94: {
        append_mnemonic(instr, "xchg");
        handler_xchg_accumulator(instr);
        break;
    }
    case 0x95: {
        append_mnemonic(instr, "xchg");
        handler_xchg_accumulator(instr);
        break;
    }
    case 0x96: {
        append_mnemonic(instr, "xchg");
        handler_xchg_accumulator(instr);
        break;
    }
    case 0x97: {
        append_mnemonic(instr, "xchg");
        handler_xchg_accumulator(instr);
        break;
    }
    case 0x98: {
        append_mnemonic(instr, "convert");
        handler_integer_alias(instr);
        break;
    }
    case 0x99: {
        append_mnemonic(instr, "convert");
        handler_integer_alias(instr);
        break;
    }
    case 0x9A: {
        append_mnemonic(instr, "call");
        handler_far_pointer(instr);
        break;
    }
    case 0x9B: {
        append_mnemonic(instr, "wait");
        handler_None(instr);
        break;
    }
    case 0x9C: {
        append_mnemonic(instr, "pushf");
        handler_None(instr);
        break;
    }
    case 0x9D: {
        append_mnemonic(instr, "popf");
        handler_None(instr);
        break;
    }
    case 0x9E: {
        append_mnemonic(instr, "sahf");
        handler_None(instr);
        break;
    }
    case 0x9F: {
        append_mnemonic(instr, "lahf");
        handler_None(instr);
        break;
    }
    case 0xA0: {
        append_mnemonic(instr, "mov");
        handler_moffs(instr);
        break;
    }
    case 0xA1: {
        append_mnemonic(instr, "mov");
        handler_moffs(instr);
        break;
    }
    case 0xA2: {
        append_mnemonic(instr, "mov");
        handler_moffs(instr);
        break;
    }
    case 0xA3: {
        append_mnemonic(instr, "mov");
        handler_moffs(instr);
        break;
    }
    case 0xA4: {
        append_mnemonic(instr, "string");
        handler_string(instr);
        break;
    }
    case 0xA5: {
        append_mnemonic(instr, "string");
        handler_string(instr);
        break;
    }
    case 0xA6: {
        append_mnemonic(instr, "string");
        handler_string(instr);
        break;
    }
    case 0xA7: {
        append_mnemonic(instr, "string");
        handler_string(instr);
        break;
    }
    case 0xA8: {
        append_mnemonic(instr, "test");
        handler_Al_Ib(instr);
        break;
    }
    case 0xA9: {
        append_mnemonic(instr, "test");
        handler_Al_Iz(instr);
        break;
    }
    case 0xAA: {
        append_mnemonic(instr, "string");
        handler_string(instr);
        break;
    }
    case 0xAB: {
        append_mnemonic(instr, "string");
        handler_string(instr);
        break;
    }
    case 0xAC: {
        append_mnemonic(instr, "string");
        handler_string(instr);
        break;
    }
    case 0xAD: {
        append_mnemonic(instr, "string");
        handler_string(instr);
        break;
    }
    case 0xAE: {
        append_mnemonic(instr, "string");
        handler_string(instr);
        break;
    }
    case 0xAF: {
        append_mnemonic(instr, "string");
        handler_string(instr);
        break;
    }
    case 0xB0: {
        append_mnemonic(instr, "mov");
        handler_Reg8_In_Opcode_Ib(instr);
        break;
    }
    case 0xB1: {
        append_mnemonic(instr, "mov");
        handler_Reg8_In_Opcode_Ib(instr);
        break;
    }
    case 0xB2: {
        append_mnemonic(instr, "mov");
        handler_Reg8_In_Opcode_Ib(instr);
        break;
    }
    case 0xB3: {
        append_mnemonic(instr, "mov");
        handler_Reg8_In_Opcode_Ib(instr);
        break;
    }
    case 0xB4: {
        append_mnemonic(instr, "mov");
        handler_Reg8_In_Opcode_Ib(instr);
        break;
    }
    case 0xB5: {
        append_mnemonic(instr, "mov");
        handler_Reg8_In_Opcode_Ib(instr);
        break;
    }
    case 0xB6: {
        append_mnemonic(instr, "mov");
        handler_Reg8_In_Opcode_Ib(instr);
        break;
    }
    case 0xB7: {
        append_mnemonic(instr, "mov");
        handler_Reg8_In_Opcode_Ib(instr);
        break;
    }
    case 0xB8: {
        append_mnemonic(instr, "mov");
        handler_Reg_In_Opcode_Iz(instr);
        break;
    }
    case 0xB9: {
        append_mnemonic(instr, "mov");
        handler_Reg_In_Opcode_Iz(instr);
        break;
    }
    case 0xBA: {
        append_mnemonic(instr, "mov");
        handler_Reg_In_Opcode_Iz(instr);
        break;
    }
    case 0xBB: {
        append_mnemonic(instr, "mov");
        handler_Reg_In_Opcode_Iz(instr);
        break;
    }
    case 0xBC: {
        append_mnemonic(instr, "mov");
        handler_Reg_In_Opcode_Iz(instr);
        break;
    }
    case 0xBD: {
        append_mnemonic(instr, "mov");
        handler_Reg_In_Opcode_Iz(instr);
        break;
    }
    case 0xBE: {
        append_mnemonic(instr, "mov");
        handler_Reg_In_Opcode_Iz(instr);
        break;
    }
    case 0xBF: {
        append_mnemonic(instr, "mov");
        handler_Reg_In_Opcode_Iz(instr);
        break;
    }
    case 0xC0: {
        switch (instr->modrm.bits.reg) {
            case 0: {
                append_mnemonic(instr, "rol");
                handler_Eb_Ib(instr);
                break;
            }
            case 1: {
                append_mnemonic(instr, "ror");
                handler_Eb_Ib(instr);
                break;
            }
            case 2: {
                append_mnemonic(instr, "rcl");
                handler_Eb_Ib(instr);
                break;
            }
            case 3: {
                append_mnemonic(instr, "rcr");
                handler_Eb_Ib(instr);
                break;
            }
            case 4: {
                append_mnemonic(instr, "shl");
                handler_Eb_Ib(instr);
                break;
            }
            case 5: {
                append_mnemonic(instr, "shr");
                handler_Eb_Ib(instr);
                break;
            }
            case 6: {
                append_mnemonic(instr, "sal");
                handler_Eb_Ib(instr);
                break;
            }
            case 7: {
                append_mnemonic(instr, "sar");
                handler_Eb_Ib(instr);
                break;
            }
            default:
                append_text(instr, "(UD Group)");
                break;
        }
        break;
    }
    case 0xC1: {
        switch (instr->modrm.bits.reg) {
            case 0: {
                append_mnemonic(instr, "rol");
                handler_Ev_Iz(instr);
                break;
            }
            case 1: {
                append_mnemonic(instr, "ror");
                handler_Ev_Iz(instr);
                break;
            }
            case 2: {
                append_mnemonic(instr, "rcl");
                handler_Ev_Iz(instr);
                break;
            }
            case 3: {
                append_mnemonic(instr, "rcr");
                handler_Ev_Iz(instr);
                break;
            }
            case 4: {
                append_mnemonic(instr, "shl");
                handler_Ev_Iz(instr);
                break;
            }
            case 5: {
                append_mnemonic(instr, "shr");
                handler_Ev_Iz(instr);
                break;
            }
            case 6: {
                append_mnemonic(instr, "sal");
                handler_Ev_Iz(instr);
                break;
            }
            case 7: {
                append_mnemonic(instr, "sar");
                handler_Ev_Iz(instr);
                break;
            }
            default:
                append_text(instr, "(UD Group)");
                break;
        }
        break;
    }
    case 0xC2: {
        append_mnemonic(instr, "ret");
        handler_ret_imm(instr);
        break;
    }
    case 0xC3: {
        append_mnemonic(instr, "ret");
        handler_None(instr);
        break;
    }
    case 0xC4: {
        append_mnemonic(instr, "les");
        handler_far_load(instr);
        break;
    }
    case 0xC5: {
        append_mnemonic(instr, "lds");
        handler_far_load(instr);
        break;
    }
    case 0xC6: {
        switch (instr->modrm.bits.reg) {
            case 0: {
                append_mnemonic(instr, "mov");
                handler_Eb_Ib(instr);
                break;
            }
            default:
                append_text(instr, "(UD Group)");
                break;
        }
        break;
    }
    case 0xC7: {
        switch (instr->modrm.bits.reg) {
            case 0: {
                append_mnemonic(instr, "mov");
                handler_Ev_Iz(instr);
                break;
            }
            default:
                append_text(instr, "(UD Group)");
                break;
        }
        break;
    }
    case 0xC8: {
        append_mnemonic(instr, "enter");
        handler_enter(instr);
        break;
    }
    case 0xC9: {
        append_mnemonic(instr, "leave");
        handler_None(instr);
        break;
    }
    case 0xCA: {
        append_mnemonic(instr, "retf");
        handler_ret_imm(instr);
        break;
    }
    case 0xCB: {
        append_mnemonic(instr, "retf");
        handler_None(instr);
        break;
    }
    case 0xCC: {
        append_mnemonic(instr, "int3");
        handler_None(instr);
        break;
    }
    case 0xCD: {
        append_mnemonic(instr, "int");
        handler_int_imm(instr);
        break;
    }
    case 0xCE: {
        append_mnemonic(instr, "into");
        handler_x86_only(instr);
        break;
    }
    case 0xCF: {
        append_mnemonic(instr, "iret");
        handler_None(instr);
        break;
    }
    case 0xD0: {
        switch (instr->modrm.bits.reg) {
            case 0: {
                append_mnemonic(instr, "rol");
                handler_shift_one(instr);
                break;
            }
            case 1: {
                append_mnemonic(instr, "ror");
                handler_shift_one(instr);
                break;
            }
            case 2: {
                append_mnemonic(instr, "rcl");
                handler_shift_one(instr);
                break;
            }
            case 3: {
                append_mnemonic(instr, "rcr");
                handler_shift_one(instr);
                break;
            }
            case 4: {
                append_mnemonic(instr, "shl");
                handler_shift_one(instr);
                break;
            }
            case 5: {
                append_mnemonic(instr, "shr");
                handler_shift_one(instr);
                break;
            }
            case 6: {
                append_mnemonic(instr, "sal");
                handler_shift_one(instr);
                break;
            }
            case 7: {
                append_mnemonic(instr, "sar");
                handler_shift_one(instr);
                break;
            }
            default:
                append_text(instr, "(UD Group)");
                break;
        }
        break;
    }
    case 0xD1: {
        switch (instr->modrm.bits.reg) {
            case 0: {
                append_mnemonic(instr, "rol");
                handler_shift_one(instr);
                break;
            }
            case 1: {
                append_mnemonic(instr, "ror");
                handler_shift_one(instr);
                break;
            }
            case 2: {
                append_mnemonic(instr, "rcl");
                handler_shift_one(instr);
                break;
            }
            case 3: {
                append_mnemonic(instr, "rcr");
                handler_shift_one(instr);
                break;
            }
            case 4: {
                append_mnemonic(instr, "shl");
                handler_shift_one(instr);
                break;
            }
            case 5: {
                append_mnemonic(instr, "shr");
                handler_shift_one(instr);
                break;
            }
            case 6: {
                append_mnemonic(instr, "sal");
                handler_shift_one(instr);
                break;
            }
            case 7: {
                append_mnemonic(instr, "sar");
                handler_shift_one(instr);
                break;
            }
            default:
                append_text(instr, "(UD Group)");
                break;
        }
        break;
    }
    case 0xD2: {
        switch (instr->modrm.bits.reg) {
            case 0: {
                append_mnemonic(instr, "rol");
                handler_shift_cl(instr);
                break;
            }
            case 1: {
                append_mnemonic(instr, "ror");
                handler_shift_cl(instr);
                break;
            }
            case 2: {
                append_mnemonic(instr, "rcl");
                handler_shift_cl(instr);
                break;
            }
            case 3: {
                append_mnemonic(instr, "rcr");
                handler_shift_cl(instr);
                break;
            }
            case 4: {
                append_mnemonic(instr, "shl");
                handler_shift_cl(instr);
                break;
            }
            case 5: {
                append_mnemonic(instr, "shr");
                handler_shift_cl(instr);
                break;
            }
            case 6: {
                append_mnemonic(instr, "sal");
                handler_shift_cl(instr);
                break;
            }
            case 7: {
                append_mnemonic(instr, "sar");
                handler_shift_cl(instr);
                break;
            }
            default:
                append_text(instr, "(UD Group)");
                break;
        }
        break;
    }
    case 0xD3: {
        switch (instr->modrm.bits.reg) {
            case 0: {
                append_mnemonic(instr, "rol");
                handler_shift_cl(instr);
                break;
            }
            case 1: {
                append_mnemonic(instr, "ror");
                handler_shift_cl(instr);
                break;
            }
            case 2: {
                append_mnemonic(instr, "rcl");
                handler_shift_cl(instr);
                break;
            }
            case 3: {
                append_mnemonic(instr, "rcr");
                handler_shift_cl(instr);
                break;
            }
            case 4: {
                append_mnemonic(instr, "shl");
                handler_shift_cl(instr);
                break;
            }
            case 5: {
                append_mnemonic(instr, "shr");
                handler_shift_cl(instr);
                break;
            }
            case 6: {
                append_mnemonic(instr, "sal");
                handler_shift_cl(instr);
                break;
            }
            case 7: {
                append_mnemonic(instr, "sar");
                handler_shift_cl(instr);
                break;
            }
            default:
                append_text(instr, "(UD Group)");
                break;
        }
        break;
    }
    case 0xD4: {
        append_mnemonic(instr, "aam");
        handler_aam_aad(instr);
        break;
    }
    case 0xD5: {
        append_mnemonic(instr, "aad");
        handler_aam_aad(instr);
        break;
    }
    case 0xD7: {
        append_mnemonic(instr, "xlat");
        handler_None(instr);
        break;
    }
    case 0xE0: {
        append_mnemonic(instr, "loopne");
        handler_Jb(instr);
        break;
    }
    case 0xE1: {
        append_mnemonic(instr, "loope");
        handler_Jb(instr);
        break;
    }
    case 0xE2: {
        append_mnemonic(instr, "loop");
        handler_Jb(instr);
        break;
    }
    case 0xE3: {
        append_mnemonic(instr, "jrcxz");
        handler_jrcxz(instr);
        break;
    }
    case 0xE4: {
        append_mnemonic(instr, "io");
        handler_io(instr);
        break;
    }
    case 0xE5: {
        append_mnemonic(instr, "io");
        handler_io(instr);
        break;
    }
    case 0xE6: {
        append_mnemonic(instr, "io");
        handler_io(instr);
        break;
    }
    case 0xE7: {
        append_mnemonic(instr, "io");
        handler_io(instr);
        break;
    }
    case 0xE8: {
        append_mnemonic(instr, "call");
        handler_Jz(instr);
        break;
    }
    case 0xE9: {
        append_mnemonic(instr, "jmp");
        handler_Jz(instr);
        break;
    }
    case 0xEA: {
        append_mnemonic(instr, "jmp");
        handler_far_pointer(instr);
        break;
    }
    case 0xEB: {
        append_mnemonic(instr, "jmp");
        handler_Jb(instr);
        break;
    }
    case 0xEC: {
        append_mnemonic(instr, "io");
        handler_io(instr);
        break;
    }
    case 0xED: {
        append_mnemonic(instr, "io");
        handler_io(instr);
        break;
    }
    case 0xEE: {
        append_mnemonic(instr, "io");
        handler_io(instr);
        break;
    }
    case 0xEF: {
        append_mnemonic(instr, "io");
        handler_io(instr);
        break;
    }
    case 0xF1: {
        append_mnemonic(instr, "int1");
        handler_None(instr);
        break;
    }
    case 0xF4: {
        append_mnemonic(instr, "hlt");
        handler_None(instr);
        break;
    }
    case 0xF5: {
        append_mnemonic(instr, "cmc");
        handler_None(instr);
        break;
    }
    case 0xF6: {
        switch (instr->modrm.bits.reg) {
            case 0: {
                append_mnemonic(instr, "test");
                handler_Eb_Ib(instr);
                break;
            }
            case 1: {
                append_mnemonic(instr, "test");
                handler_Eb_Ib(instr);
                break;
            }
            case 2: {
                append_mnemonic(instr, "not");
                handler_Eb(instr);
                break;
            }
            case 3: {
                append_mnemonic(instr, "neg");
                handler_Eb(instr);
                break;
            }
            case 4: {
                append_mnemonic(instr, "mul");
                handler_Eb(instr);
                break;
            }
            case 5: {
                append_mnemonic(instr, "imul");
                handler_Eb(instr);
                break;
            }
            case 6: {
                append_mnemonic(instr, "div");
                handler_Eb(instr);
                break;
            }
            case 7: {
                append_mnemonic(instr, "idiv");
                handler_Eb(instr);
                break;
            }
            default:
                append_text(instr, "(UD Group)");
                break;
        }
        break;
    }
    case 0xF7: {
        switch (instr->modrm.bits.reg) {
            case 0: {
                append_mnemonic(instr, "test");
                handler_Ev_Iz(instr);
                break;
            }
            case 1: {
                append_mnemonic(instr, "test");
                handler_Ev_Iz(instr);
                break;
            }
            case 2: {
                append_mnemonic(instr, "not");
                handler_Ev(instr);
                break;
            }
            case 3: {
                append_mnemonic(instr, "neg");
                handler_Ev(instr);
                break;
            }
            case 4: {
                append_mnemonic(instr, "mul");
                handler_Ev(instr);
                break;
            }
            case 5: {
                append_mnemonic(instr, "imul");
                handler_Ev(instr);
                break;
            }
            case 6: {
                append_mnemonic(instr, "div");
                handler_Ev(instr);
                break;
            }
            case 7: {
                append_mnemonic(instr, "idiv");
                handler_Ev(instr);
                break;
            }
            default:
                append_text(instr, "(UD Group)");
                break;
        }
        break;
    }
    case 0xF8: {
        append_mnemonic(instr, "clc");
        handler_None(instr);
        break;
    }
    case 0xF9: {
        append_mnemonic(instr, "stc");
        handler_None(instr);
        break;
    }
    case 0xFA: {
        append_mnemonic(instr, "cli");
        handler_None(instr);
        break;
    }
    case 0xFB: {
        append_mnemonic(instr, "sti");
        handler_None(instr);
        break;
    }
    case 0xFC: {
        append_mnemonic(instr, "cld");
        handler_None(instr);
        break;
    }
    case 0xFD: {
        append_mnemonic(instr, "std");
        handler_None(instr);
        break;
    }
    case 0xFE: {
        switch (instr->modrm.bits.reg) {
            case 0: {
                append_mnemonic(instr, "inc");
                handler_Eb(instr);
                break;
            }
            case 1: {
                append_mnemonic(instr, "dec");
                handler_Eb(instr);
                break;
            }
            default:
                append_text(instr, "(UD Group)");
                break;
        }
        break;
    }
    case 0xFF: {
        switch (instr->modrm.bits.reg) {
            case 0: {
                append_mnemonic(instr, "inc");
                handler_Ev(instr);
                break;
            }
            case 1: {
                append_mnemonic(instr, "dec");
                handler_Ev(instr);
                break;
            }
            case 2: {
                append_mnemonic(instr, "call");
                handler_Ev64(instr);
                break;
            }
            case 4: {
                append_mnemonic(instr, "jmp");
                handler_Ev64(instr);
                break;
            }
            case 6: {
                append_mnemonic(instr, "push");
                handler_Ev64(instr);
                break;
            }
            default:
                append_text(instr, "(UD Group)");
                break;
        }
        break;
    }
    default:
        append_unknown_opcode(instr, 0);
        break;
}
