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
    case 0x0F: {
        switch (instr->op[1]) {
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
            case 0x05: {
                append_mnemonic(instr, "syscall");
                handler_None(instr);
                break;
            }
            case 0x07: {
                append_mnemonic(instr, "sysret");
                handler_None(instr);
                break;
            }
            case 0x0B: {
                append_mnemonic(instr, "ud2");
                handler_None(instr);
                break;
            }
            case 0x31: {
                append_mnemonic(instr, "rdtsc");
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
            case 0xA2: {
                append_mnemonic(instr, "cpuid");
                handler_None(instr);
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
    case 0x90: {
        append_mnemonic(instr, "nop");
        handler_None(instr);
        break;
    }
    case 0x9B: {
        append_mnemonic(instr, "wait");
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
    case 0xC3: {
        append_mnemonic(instr, "ret");
        handler_None(instr);
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
    case 0xC9: {
        append_mnemonic(instr, "leave");
        handler_None(instr);
        break;
    }
    case 0xCC: {
        append_mnemonic(instr, "int3");
        handler_None(instr);
        break;
    }
    case 0xE9: {
        append_mnemonic(instr, "jmp");
        handler_Jz(instr);
        break;
    }
    case 0xEB: {
        append_mnemonic(instr, "jmp");
        handler_Jb(instr);
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
    default:
        append_unknown_opcode(instr, 0);
        break;
}
