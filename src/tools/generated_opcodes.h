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
    case 0x03: {
        INSTR_CONCAT("add ", "%s");
        handler_Gv_Ev(instr);
        break;
    }
    case 0x11: {
        INSTR_CONCAT("adc ", "%s");
        handler_Ev_Gv(instr);
        break;
    }
    case 0x13: {
        INSTR_CONCAT("adc ", "%s");
        handler_Gv_Ev(instr);
        break;
    }
    case 0x21: {
        INSTR_CONCAT("and ", "%s");
        handler_Ev_Gv(instr);
        break;
    }
    case 0x23: {
        INSTR_CONCAT("and ", "%s");
        handler_Gv_Ev(instr);
        break;
    }
    case 0x31: {
        INSTR_CONCAT("xor ", "%s");
        handler_Ev_Gv(instr);
        break;
    }
    case 0x33: {
        INSTR_CONCAT("xor ", "%s");
        handler_Gv_Ev(instr);
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
    case 0xC3: {
        INSTR_CONCAT("ret ", "%s");
        handler_None(instr);
        break;
    }
    default:
        INSTR_CONCAT(instr->op[0], "db 0x%02X ");
        break;
}
