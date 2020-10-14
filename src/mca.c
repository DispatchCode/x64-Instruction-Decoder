#include "mca.h"

static inline bool check_vex(struct instruction *instr, char *data, enum supported_architecture arch) {

}

static inline bool mca_check_sib(uint8_t mod, uint8_t rm) {
    return mod < 3 && rm == 4;
}

static inline int mca_displacement_size(uint8_t mod, uint8_t rm) {
    if((mod == 0x02) || (rm == 0x05 && !mod))
        return 4;
    else if(mod == 0x01)
        return 1;
    return 0;
}

static inline int mca_imm_size(struct instruction *instr, size_t val, enum supported_architecture arch) {
    switch (val) {
        case b:
        case b1:
            return 1;
        case v:
            if(arch == X64 && instr->set_prefix & OP64)
                return 8;
            else if(instr->set_prefix & OS)
                return 2;
            return 4;
        case z:
        case z1:
            if(instr->set_prefix & OS)
                return 2;
            return 4;
        case p:
            if(instr->set_prefix & OS) {
                if (arch == X86)
                    return 2;
                return 8;
            }
            return 4;
        case w:
            return 2;
        case wb:
            return 3; // TODO  ENTER iw, ib
        case gr3b:
            if(!instr->modrm.bits.reg)
                return 1;
            return 0;
        case gr3z:
            if(!instr->modrm.bits.reg)
            {
                if(instr->set_prefix & OS)
                    return 2;
                return 4;
            }
            return 0;

        default:
            return 0;
    }
}

static void mca_decode_modrm(struct instruction *instr, enum supported_architecture arch, const char *start_data, const size_t *modrm_table, const size_t *imm_table) {
    size_t val = 0;
    if((val = modrm_table[instr->op])) {
        instr->set_field |= MODRM;

        if(val == X87_FPU)
            instr->set_field |= FPU;

        uint8_t curr = (uint8_t) *(start_data + instr->length);

        instr->modrm.value = curr;
        instr->length++;

        uint8_t mod_val = instr->modrm.bits.mod, rm_val = instr->modrm.bits.rm;

        if(mca_check_sib(instr->modrm.bits.mod,instr->modrm.bits.rm)) {
            instr->set_field |= SIB;

            instr->sib.value = (uint8_t) *(start_data + instr->length);
            instr->length++;

            if(instr->sib.bits.base == 0x05) {
                mod_val = instr->sib.bits.scaled;
                rm_val  = instr->sib.bits.base;
            }
        }

        // displacement
        if(instr->modrm.bits.mod < 3) {
            instr->set_field |= DISP;
            instr->disp_len = mca_displacement_size(mod_val, rm_val);
            memcpy(&instr->disp, (start_data + instr->length), instr->disp_len);
            instr->length += instr->disp_len;
        }
    }

    instr->imm_len = mca_imm_size(instr, imm_table[instr->op], arch);
    if(instr->imm_len) {
        instr->set_field |= IMM;
        memcpy(&instr->imm, (start_data + instr->length), instr->imm_len);
        instr->length += instr->imm_len;
    }
}

static int mca_decode_2b(struct instruction *instr, enum supported_architecture arch, const char *data_src)
{
    instr->set_prefix |= ESCAPE;
    uint8_t curr = (uint8_t) *(data_src + instr->length);

    if(curr == 0x3A || curr == 0x38)
    {
        // TODO  3-byte OP decode
    }

    instr->op = curr;
    instr->length++;

    mca_decode_modrm(instr, arch, data_src, modrm_2b, imm_byte_2b);

    return instr->length;
}

int mca_decode(struct instruction *instr, enum supported_architecture arch, char *data, int offset) {
    memset(instr, 0, sizeof(struct instruction));

    char *start_data = (data + offset);
    uint8_t curr = (uint8_t) *(start_data);

    // TODO  vex prefix decode
    //  x64 -> C4, C5, 8F -> VEX present
    //  x86 ->            -> VEX present only if the 2nd byte MSBs == 11b

    while(x86_64_prefix[curr] & arch)
    {
        switch(curr) {
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
                if(arch == X64)
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
        }

        instr->set_field |= PREFIX;
        instr->prefixes[instr->prefix_cnt] = curr;
        instr->prefix_cnt++;
        instr->length++;

        // Rex prefix
        // TODO 64-bit mode: IF OP == 90h and REX.B == 1,
        //  then the instruction is XCHG r8, rAX
        if(arch == X64 && (curr & 0x40))
        {
            instr->rex.value = curr;
            instr->set_field |= REX;
        }
        else if(curr == 0x0F)
        {
            mca_decode_2b(instr, arch, start_data);
            #ifdef _ENABLE_RAW_BYTES
            memcpy(instr->instr, start_data, instr->length);
            #endif
            return instr->length;
        }

        curr = (uint8_t) *(start_data + instr->length);
    }
    instr->length++;
    instr->op = curr;

    mca_decode_modrm(instr, arch, start_data, modrm_1b, imm_byte_1b);

#ifdef _ENABLE_RAW_BYTES
    memcpy(instr->instr, start_data, instr->length);
#endif

    return instr->length;
}