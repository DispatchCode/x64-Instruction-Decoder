switch (instr->op[0]) {
    case 0x00: {
        INSTR_CONCAT("add ", "%s");
        handler_Eb_Gb(instr);
        break;
    }
    case 0x01: {
        INSTR_CONCAT("add ", "%s");
        handler_Ev_Gv(instr);
        break;
    }
    case 0x02: {
        INSTR_CONCAT("add ", "%s");
        handler_Gb_Eb(instr);
        break;
    }
    case 0x03: {
        INSTR_CONCAT("add ", "%s");
        handler_Gv_Ev(instr);
        break;
    }
    case 0x04: {
        INSTR_CONCAT("add ", "%s");
        handler_Al_Ib(instr);
        break;
    }
    case 0x05: {
        INSTR_CONCAT("add ", "%s");
        handler_Al_Iz(instr);
        break;
    }
    case 0x08: {
        INSTR_CONCAT("or ", "%s");
        handler_Eb_Gb(instr);
        break;
    }
    case 0x09: {
        INSTR_CONCAT("or ", "%s");
        handler_Ev_Gv(instr);
        break;
    }
    case 0x0A: {
        INSTR_CONCAT("or ", "%s");
        handler_Gb_Eb(instr);
        break;
    }
    case 0x0B: {
        INSTR_CONCAT("or ", "%s");
        handler_Gv_Ev(instr);
        break;
    }
    case 0x0C: {
        INSTR_CONCAT("or ", "%s");
        handler_Al_Ib(instr);
        break;
    }
    case 0x0D: {
        INSTR_CONCAT("or ", "%s");
        handler_Al_Iz(instr);
        break;
    }
    case 0x0F: {
        switch (instr->op[1]) {
            case 0x05: {
                INSTR_CONCAT("syscall ", "%s");
                handler_None(instr);
                break;
            }
            case 0x07: {
                INSTR_CONCAT("sysret ", "%s");
                handler_None(instr);
                break;
            }
            case 0x0B: {
                INSTR_CONCAT("ud2 ", "%s");
                handler_None(instr);
                break;
            }
            case 0x31: {
                INSTR_CONCAT("rdtsc ", "%s");
                handler_None(instr);
                break;
            }
            case 0x34: {
                INSTR_CONCAT("sysenter ", "%s");
                handler_None(instr);
                break;
            }
            case 0x35: {
                INSTR_CONCAT("sysexit ", "%s");
                handler_None(instr);
                break;
            }
            case 0x40: {
                INSTR_CONCAT("cmovo ", "%s");
                handler_Gv_Ev(instr);
                break;
            }
            case 0x41: {
                INSTR_CONCAT("cmovno ", "%s");
                handler_Gv_Ev(instr);
                break;
            }
            case 0x42: {
                INSTR_CONCAT("cmovb ", "%s");
                handler_Gv_Ev(instr);
                break;
            }
            case 0x43: {
                INSTR_CONCAT("cmovae ", "%s");
                handler_Gv_Ev(instr);
                break;
            }
            case 0x44: {
                INSTR_CONCAT("cmove ", "%s");
                handler_Gv_Ev(instr);
                break;
            }
            case 0x45: {
                INSTR_CONCAT("cmovne ", "%s");
                handler_Gv_Ev(instr);
                break;
            }
            case 0x46: {
                INSTR_CONCAT("cmovbe ", "%s");
                handler_Gv_Ev(instr);
                break;
            }
            case 0x47: {
                INSTR_CONCAT("cmova ", "%s");
                handler_Gv_Ev(instr);
                break;
            }
            case 0x48: {
                INSTR_CONCAT("cmovs ", "%s");
                handler_Gv_Ev(instr);
                break;
            }
            case 0x49: {
                INSTR_CONCAT("cmovns ", "%s");
                handler_Gv_Ev(instr);
                break;
            }
            case 0x4A: {
                INSTR_CONCAT("cmovp ", "%s");
                handler_Gv_Ev(instr);
                break;
            }
            case 0x4B: {
                INSTR_CONCAT("cmovnp ", "%s");
                handler_Gv_Ev(instr);
                break;
            }
            case 0x4C: {
                INSTR_CONCAT("cmovl ", "%s");
                handler_Gv_Ev(instr);
                break;
            }
            case 0x4D: {
                INSTR_CONCAT("cmovge ", "%s");
                handler_Gv_Ev(instr);
                break;
            }
            case 0x4E: {
                INSTR_CONCAT("cmovle ", "%s");
                handler_Gv_Ev(instr);
                break;
            }
            case 0x4F: {
                INSTR_CONCAT("cmovg ", "%s");
                handler_Gv_Ev(instr);
                break;
            }
            case 0x77: {
                INSTR_CONCAT("emms ", "%s");
                handler_None(instr);
                break;
            }
            case 0x80: {
                INSTR_CONCAT("jo ", "%s");
                handler_Jz(instr);
                break;
            }
            case 0x81: {
                INSTR_CONCAT("jno ", "%s");
                handler_Jz(instr);
                break;
            }
            case 0x82: {
                INSTR_CONCAT("jb ", "%s");
                handler_Jz(instr);
                break;
            }
            case 0x83: {
                INSTR_CONCAT("jae ", "%s");
                handler_Jz(instr);
                break;
            }
            case 0x84: {
                INSTR_CONCAT("je ", "%s");
                handler_Jz(instr);
                break;
            }
            case 0x85: {
                INSTR_CONCAT("jne ", "%s");
                handler_Jz(instr);
                break;
            }
            case 0x86: {
                INSTR_CONCAT("jbe ", "%s");
                handler_Jz(instr);
                break;
            }
            case 0x87: {
                INSTR_CONCAT("ja ", "%s");
                handler_Jz(instr);
                break;
            }
            case 0x88: {
                INSTR_CONCAT("js ", "%s");
                handler_Jz(instr);
                break;
            }
            case 0x89: {
                INSTR_CONCAT("jns ", "%s");
                handler_Jz(instr);
                break;
            }
            case 0x8A: {
                INSTR_CONCAT("jp ", "%s");
                handler_Jz(instr);
                break;
            }
            case 0x8B: {
                INSTR_CONCAT("jnp ", "%s");
                handler_Jz(instr);
                break;
            }
            case 0x8C: {
                INSTR_CONCAT("jl ", "%s");
                handler_Jz(instr);
                break;
            }
            case 0x8D: {
                INSTR_CONCAT("jge ", "%s");
                handler_Jz(instr);
                break;
            }
            case 0x8E: {
                INSTR_CONCAT("jle ", "%s");
                handler_Jz(instr);
                break;
            }
            case 0x8F: {
                INSTR_CONCAT("jg ", "%s");
                handler_Jz(instr);
                break;
            }
            case 0xA2: {
                INSTR_CONCAT("cpuid ", "%s");
                handler_None(instr);
                break;
            }
            case 0xAF: {
                INSTR_CONCAT("imul ", "%s");
                handler_Gv_Ev(instr);
                break;
            }
            case 0xB0: {
                INSTR_CONCAT("cmpxchg ", "%s");
                handler_Eb_Gb(instr);
                break;
            }
            case 0xB1: {
                INSTR_CONCAT("cmpxchg ", "%s");
                handler_Ev_Gv(instr);
                break;
            }
            case 0xC0: {
                INSTR_CONCAT("xadd ", "%s");
                handler_Eb_Gb(instr);
                break;
            }
            case 0xC1: {
                INSTR_CONCAT("xadd ", "%s");
                handler_Ev_Gv(instr);
                break;
            }
            default:
                INSTR_CONCAT(instr->op[1], "db 0x%02X ");
                break;
        }
        break;
    }
    case 0x10: {
        INSTR_CONCAT("adc ", "%s");
        handler_Eb_Gb(instr);
        break;
    }
    case 0x11: {
        INSTR_CONCAT("adc ", "%s");
        handler_Ev_Gv(instr);
        break;
    }
    case 0x12: {
        INSTR_CONCAT("adc ", "%s");
        handler_Gb_Eb(instr);
        break;
    }
    case 0x13: {
        INSTR_CONCAT("adc ", "%s");
        handler_Gv_Ev(instr);
        break;
    }
    case 0x14: {
        INSTR_CONCAT("adc ", "%s");
        handler_Al_Ib(instr);
        break;
    }
    case 0x15: {
        INSTR_CONCAT("adc ", "%s");
        handler_Al_Iz(instr);
        break;
    }
    case 0x18: {
        INSTR_CONCAT("sbb ", "%s");
        handler_Eb_Gb(instr);
        break;
    }
    case 0x19: {
        INSTR_CONCAT("sbb ", "%s");
        handler_Ev_Gv(instr);
        break;
    }
    case 0x1A: {
        INSTR_CONCAT("sbb ", "%s");
        handler_Gb_Eb(instr);
        break;
    }
    case 0x1B: {
        INSTR_CONCAT("sbb ", "%s");
        handler_Gv_Ev(instr);
        break;
    }
    case 0x1C: {
        INSTR_CONCAT("sbb ", "%s");
        handler_Al_Ib(instr);
        break;
    }
    case 0x1D: {
        INSTR_CONCAT("sbb ", "%s");
        handler_Al_Iz(instr);
        break;
    }
    case 0x20: {
        INSTR_CONCAT("and ", "%s");
        handler_Eb_Gb(instr);
        break;
    }
    case 0x21: {
        INSTR_CONCAT("and ", "%s");
        handler_Ev_Gv(instr);
        break;
    }
    case 0x22: {
        INSTR_CONCAT("and ", "%s");
        handler_Gb_Eb(instr);
        break;
    }
    case 0x23: {
        INSTR_CONCAT("and ", "%s");
        handler_Gv_Ev(instr);
        break;
    }
    case 0x24: {
        INSTR_CONCAT("and ", "%s");
        handler_Al_Ib(instr);
        break;
    }
    case 0x25: {
        INSTR_CONCAT("and ", "%s");
        handler_Al_Iz(instr);
        break;
    }
    case 0x28: {
        INSTR_CONCAT("sub ", "%s");
        handler_Eb_Gb(instr);
        break;
    }
    case 0x29: {
        INSTR_CONCAT("sub ", "%s");
        handler_Ev_Gv(instr);
        break;
    }
    case 0x2A: {
        INSTR_CONCAT("sub ", "%s");
        handler_Gb_Eb(instr);
        break;
    }
    case 0x2B: {
        INSTR_CONCAT("sub ", "%s");
        handler_Gv_Ev(instr);
        break;
    }
    case 0x2C: {
        INSTR_CONCAT("sub ", "%s");
        handler_Al_Ib(instr);
        break;
    }
    case 0x2D: {
        INSTR_CONCAT("sub ", "%s");
        handler_Al_Iz(instr);
        break;
    }
    case 0x30: {
        INSTR_CONCAT("xor ", "%s");
        handler_Eb_Gb(instr);
        break;
    }
    case 0x31: {
        INSTR_CONCAT("xor ", "%s");
        handler_Ev_Gv(instr);
        break;
    }
    case 0x32: {
        INSTR_CONCAT("xor ", "%s");
        handler_Gb_Eb(instr);
        break;
    }
    case 0x33: {
        INSTR_CONCAT("xor ", "%s");
        handler_Gv_Ev(instr);
        break;
    }
    case 0x34: {
        INSTR_CONCAT("xor ", "%s");
        handler_Al_Ib(instr);
        break;
    }
    case 0x35: {
        INSTR_CONCAT("xor ", "%s");
        handler_Al_Iz(instr);
        break;
    }
    case 0x38: {
        INSTR_CONCAT("cmp ", "%s");
        handler_Eb_Gb(instr);
        break;
    }
    case 0x39: {
        INSTR_CONCAT("cmp ", "%s");
        handler_Ev_Gv(instr);
        break;
    }
    case 0x3A: {
        INSTR_CONCAT("cmp ", "%s");
        handler_Gb_Eb(instr);
        break;
    }
    case 0x3B: {
        INSTR_CONCAT("cmp ", "%s");
        handler_Gv_Ev(instr);
        break;
    }
    case 0x3C: {
        INSTR_CONCAT("cmp ", "%s");
        handler_Al_Ib(instr);
        break;
    }
    case 0x3D: {
        INSTR_CONCAT("cmp ", "%s");
        handler_Al_Iz(instr);
        break;
    }
    case 0x40: {
        INSTR_CONCAT("inc ", "%s");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x41: {
        INSTR_CONCAT("inc ", "%s");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x42: {
        INSTR_CONCAT("inc ", "%s");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x43: {
        INSTR_CONCAT("inc ", "%s");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x44: {
        INSTR_CONCAT("inc ", "%s");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x45: {
        INSTR_CONCAT("inc ", "%s");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x46: {
        INSTR_CONCAT("inc ", "%s");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x47: {
        INSTR_CONCAT("inc ", "%s");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x48: {
        INSTR_CONCAT("dec ", "%s");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x49: {
        INSTR_CONCAT("dec ", "%s");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x4A: {
        INSTR_CONCAT("dec ", "%s");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x4B: {
        INSTR_CONCAT("dec ", "%s");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x4C: {
        INSTR_CONCAT("dec ", "%s");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x4D: {
        INSTR_CONCAT("dec ", "%s");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x4E: {
        INSTR_CONCAT("dec ", "%s");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x4F: {
        INSTR_CONCAT("dec ", "%s");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x50: {
        INSTR_CONCAT("push ", "%s");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x51: {
        INSTR_CONCAT("push ", "%s");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x52: {
        INSTR_CONCAT("push ", "%s");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x53: {
        INSTR_CONCAT("push ", "%s");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x54: {
        INSTR_CONCAT("push ", "%s");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x55: {
        INSTR_CONCAT("push ", "%s");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x56: {
        INSTR_CONCAT("push ", "%s");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x57: {
        INSTR_CONCAT("push ", "%s");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x58: {
        INSTR_CONCAT("pop ", "%s");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x59: {
        INSTR_CONCAT("pop ", "%s");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x5A: {
        INSTR_CONCAT("pop ", "%s");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x5B: {
        INSTR_CONCAT("pop ", "%s");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x5C: {
        INSTR_CONCAT("pop ", "%s");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x5D: {
        INSTR_CONCAT("pop ", "%s");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x5E: {
        INSTR_CONCAT("pop ", "%s");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x5F: {
        INSTR_CONCAT("pop ", "%s");
        handler_Reg_In_Opcode(instr);
        break;
    }
    case 0x70: {
        INSTR_CONCAT("jo ", "%s");
        handler_Jb(instr);
        break;
    }
    case 0x71: {
        INSTR_CONCAT("jno ", "%s");
        handler_Jb(instr);
        break;
    }
    case 0x72: {
        INSTR_CONCAT("jb ", "%s");
        handler_Jb(instr);
        break;
    }
    case 0x73: {
        INSTR_CONCAT("jae ", "%s");
        handler_Jb(instr);
        break;
    }
    case 0x74: {
        INSTR_CONCAT("je ", "%s");
        handler_Jb(instr);
        break;
    }
    case 0x75: {
        INSTR_CONCAT("jne ", "%s");
        handler_Jb(instr);
        break;
    }
    case 0x76: {
        INSTR_CONCAT("jbe ", "%s");
        handler_Jb(instr);
        break;
    }
    case 0x77: {
        INSTR_CONCAT("ja ", "%s");
        handler_Jb(instr);
        break;
    }
    case 0x78: {
        INSTR_CONCAT("js ", "%s");
        handler_Jb(instr);
        break;
    }
    case 0x79: {
        INSTR_CONCAT("jns ", "%s");
        handler_Jb(instr);
        break;
    }
    case 0x7A: {
        INSTR_CONCAT("jp ", "%s");
        handler_Jb(instr);
        break;
    }
    case 0x7B: {
        INSTR_CONCAT("jnp ", "%s");
        handler_Jb(instr);
        break;
    }
    case 0x7C: {
        INSTR_CONCAT("jl ", "%s");
        handler_Jb(instr);
        break;
    }
    case 0x7D: {
        INSTR_CONCAT("jge ", "%s");
        handler_Jb(instr);
        break;
    }
    case 0x7E: {
        INSTR_CONCAT("jle ", "%s");
        handler_Jb(instr);
        break;
    }
    case 0x7F: {
        INSTR_CONCAT("jg ", "%s");
        handler_Jb(instr);
        break;
    }
    case 0x80: {
        switch (instr->modrm.bits.reg) {
            case 0:
                INSTR_CONCAT("add ", "%s"); handler_Eb_Ib(instr);
                break;
            case 1:
                INSTR_CONCAT("or ", "%s"); handler_Eb_Ib(instr);
                break;
            case 2:
                INSTR_CONCAT("adc ", "%s"); handler_Eb_Ib(instr);
                break;
            case 3:
                INSTR_CONCAT("sbb ", "%s"); handler_Eb_Ib(instr);
                break;
            case 4:
                INSTR_CONCAT("and ", "%s"); handler_Eb_Ib(instr);
                break;
            case 5:
                INSTR_CONCAT("sub ", "%s"); handler_Eb_Ib(instr);
                break;
            case 6:
                INSTR_CONCAT("xor ", "%s"); handler_Eb_Ib(instr);
                break;
            case 7:
                INSTR_CONCAT("cmp ", "%s"); handler_Eb_Ib(instr);
                break;
            default: INSTR_CONCAT("(UD Group)", "%s"); break;
        }
        break;
    }
    case 0x81: {
        switch (instr->modrm.bits.reg) {
            case 0:
                INSTR_CONCAT("add ", "%s"); handler_Ev_Iz(instr);
                break;
            case 1:
                INSTR_CONCAT("or ", "%s"); handler_Ev_Iz(instr);
                break;
            case 2:
                INSTR_CONCAT("adc ", "%s"); handler_Ev_Iz(instr);
                break;
            case 3:
                INSTR_CONCAT("sbb ", "%s"); handler_Ev_Iz(instr);
                break;
            case 4:
                INSTR_CONCAT("and ", "%s"); handler_Ev_Iz(instr);
                break;
            case 5:
                INSTR_CONCAT("sub ", "%s"); handler_Ev_Iz(instr);
                break;
            case 6:
                INSTR_CONCAT("xor ", "%s"); handler_Ev_Iz(instr);
                break;
            case 7:
                INSTR_CONCAT("cmp ", "%s"); handler_Ev_Iz(instr);
                break;
            default: INSTR_CONCAT("(UD Group)", "%s"); break;
        }
        break;
    }
    case 0x83: {
        switch (instr->modrm.bits.reg) {
            case 0:
                INSTR_CONCAT("add ", "%s"); handler_Ev_Iz(instr);
                break;
            case 1:
                INSTR_CONCAT("or ", "%s"); handler_Ev_Iz(instr);
                break;
            case 2:
                INSTR_CONCAT("adc ", "%s"); handler_Ev_Iz(instr);
                break;
            case 3:
                INSTR_CONCAT("sbb ", "%s"); handler_Ev_Iz(instr);
                break;
            case 4:
                INSTR_CONCAT("and ", "%s"); handler_Ev_Iz(instr);
                break;
            case 5:
                INSTR_CONCAT("sub ", "%s"); handler_Ev_Iz(instr);
                break;
            case 6:
                INSTR_CONCAT("xor ", "%s"); handler_Ev_Iz(instr);
                break;
            case 7:
                INSTR_CONCAT("cmp ", "%s"); handler_Ev_Iz(instr);
                break;
            default: INSTR_CONCAT("(UD Group)", "%s"); break;
        }
        break;
    }
    case 0x84: {
        INSTR_CONCAT("test ", "%s");
        handler_Eb_Gb(instr);
        break;
    }
    case 0x85: {
        INSTR_CONCAT("test ", "%s");
        handler_Ev_Gv(instr);
        break;
    }
    case 0x86: {
        INSTR_CONCAT("xchg ", "%s");
        handler_Eb_Gb(instr);
        break;
    }
    case 0x87: {
        INSTR_CONCAT("xchg ", "%s");
        handler_Ev_Gv(instr);
        break;
    }
    case 0x88: {
        INSTR_CONCAT("mov ", "%s");
        handler_Eb_Gb(instr);
        break;
    }
    case 0x89: {
        INSTR_CONCAT("mov ", "%s");
        handler_Ev_Gv(instr);
        break;
    }
    case 0x8A: {
        INSTR_CONCAT("mov ", "%s");
        handler_Gb_Eb(instr);
        break;
    }
    case 0x8B: {
        INSTR_CONCAT("mov ", "%s");
        handler_Gv_Ev(instr);
        break;
    }
    case 0x90: {
        INSTR_CONCAT("nop ", "%s");
        handler_None(instr);
        break;
    }
    case 0x9B: {
        INSTR_CONCAT("wait ", "%s");
        handler_None(instr);
        break;
    }
    case 0x9E: {
        INSTR_CONCAT("sahf ", "%s");
        handler_None(instr);
        break;
    }
    case 0x9F: {
        INSTR_CONCAT("lahf ", "%s");
        handler_None(instr);
        break;
    }
    case 0xA8: {
        INSTR_CONCAT("test ", "%s");
        handler_Al_Ib(instr);
        break;
    }
    case 0xA9: {
        INSTR_CONCAT("test ", "%s");
        handler_Al_Iz(instr);
        break;
    }
    case 0xB0: {
        INSTR_CONCAT("mov ", "%s");
        handler_Reg8_In_Opcode_Ib(instr);
        break;
    }
    case 0xB1: {
        INSTR_CONCAT("mov ", "%s");
        handler_Reg8_In_Opcode_Ib(instr);
        break;
    }
    case 0xB2: {
        INSTR_CONCAT("mov ", "%s");
        handler_Reg8_In_Opcode_Ib(instr);
        break;
    }
    case 0xB3: {
        INSTR_CONCAT("mov ", "%s");
        handler_Reg8_In_Opcode_Ib(instr);
        break;
    }
    case 0xB4: {
        INSTR_CONCAT("mov ", "%s");
        handler_Reg8_In_Opcode_Ib(instr);
        break;
    }
    case 0xB5: {
        INSTR_CONCAT("mov ", "%s");
        handler_Reg8_In_Opcode_Ib(instr);
        break;
    }
    case 0xB6: {
        INSTR_CONCAT("mov ", "%s");
        handler_Reg8_In_Opcode_Ib(instr);
        break;
    }
    case 0xB7: {
        INSTR_CONCAT("mov ", "%s");
        handler_Reg8_In_Opcode_Ib(instr);
        break;
    }
    case 0xB8: {
        INSTR_CONCAT("mov ", "%s");
        handler_Reg_In_Opcode_Iz(instr);
        break;
    }
    case 0xB9: {
        INSTR_CONCAT("mov ", "%s");
        handler_Reg_In_Opcode_Iz(instr);
        break;
    }
    case 0xBA: {
        INSTR_CONCAT("mov ", "%s");
        handler_Reg_In_Opcode_Iz(instr);
        break;
    }
    case 0xBB: {
        INSTR_CONCAT("mov ", "%s");
        handler_Reg_In_Opcode_Iz(instr);
        break;
    }
    case 0xBC: {
        INSTR_CONCAT("mov ", "%s");
        handler_Reg_In_Opcode_Iz(instr);
        break;
    }
    case 0xBD: {
        INSTR_CONCAT("mov ", "%s");
        handler_Reg_In_Opcode_Iz(instr);
        break;
    }
    case 0xBE: {
        INSTR_CONCAT("mov ", "%s");
        handler_Reg_In_Opcode_Iz(instr);
        break;
    }
    case 0xBF: {
        INSTR_CONCAT("mov ", "%s");
        handler_Reg_In_Opcode_Iz(instr);
        break;
    }
    case 0xC3: {
        INSTR_CONCAT("ret ", "%s");
        handler_None(instr);
        break;
    }
    case 0xC6: {
        switch (instr->modrm.bits.reg) {
            case 0:
                INSTR_CONCAT("mov ", "%s"); handler_Eb_Ib(instr);
                break;
            default: INSTR_CONCAT("(UD Group)", "%s"); break;
        }
        break;
    }
    case 0xC7: {
        switch (instr->modrm.bits.reg) {
            case 0:
                INSTR_CONCAT("mov ", "%s"); handler_Ev_Iz(instr);
                break;
            default: INSTR_CONCAT("(UD Group)", "%s"); break;
        }
        break;
    }
    case 0xC9: {
        INSTR_CONCAT("leave ", "%s");
        handler_None(instr);
        break;
    }
    case 0xCC: {
        INSTR_CONCAT("int3 ", "%s");
        handler_None(instr);
        break;
    }
    case 0xE9: {
        INSTR_CONCAT("jmp ", "%s");
        handler_Jz(instr);
        break;
    }
    case 0xEB: {
        INSTR_CONCAT("jmp ", "%s");
        handler_Jb(instr);
        break;
    }
    case 0xF4: {
        INSTR_CONCAT("hlt ", "%s");
        handler_None(instr);
        break;
    }
    case 0xF5: {
        INSTR_CONCAT("cmc ", "%s");
        handler_None(instr);
        break;
    }
    case 0xF8: {
        INSTR_CONCAT("clc ", "%s");
        handler_None(instr);
        break;
    }
    case 0xF9: {
        INSTR_CONCAT("stc ", "%s");
        handler_None(instr);
        break;
    }
    case 0xFA: {
        INSTR_CONCAT("cli ", "%s");
        handler_None(instr);
        break;
    }
    case 0xFB: {
        INSTR_CONCAT("sti ", "%s");
        handler_None(instr);
        break;
    }
    case 0xFC: {
        INSTR_CONCAT("cld ", "%s");
        handler_None(instr);
        break;
    }
    case 0xFD: {
        INSTR_CONCAT("std ", "%s");
        handler_None(instr);
        break;
    }
    default:
        INSTR_CONCAT(instr->op[0], "db 0x%02X ");
        break;
}
