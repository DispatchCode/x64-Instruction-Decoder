; ------------------------------------------
; VOL. 2D, Appendix A, pg. 7-8 (Intel Manual)
; ------------------------------------------

[BITS 32]

; Macros
pad     equ   16

; -------------------------------
; 3-byte 38 opcodes tests
; -------------------------------

op00:   vpshufb  ymm1, ymm2, [var]
times   pad - ($ - $op00) db 0xCC

op01:   phaddw  mm2, [var]
times   pad - ($ - $op01) db 0xCC

op02:   phaddd  xmm0, [var]
times   pad - ($ - $op02) db 0xCC

op03:   phaddsw mm4, [var]
times   pad - ($ - $op03) db 0xCC

op04:   pmaddubsw mm2, [var]
times   pad - ($ - $op04) db 0xCC

op05:   phsubw  mm0, mm1
times   pad - ($ - $op05) db 0xCC

op06:   phsubd  xmm1, [var]
times   pad - ($ - $op06) db 0xCC

op07:   phsubsw xmm5, [var]
times   pad - ($ - $op07) db 0xCC

op08:   psignb  xmm4, [var]
times   pad - ($ - $op08) db 0xCC

op09:   psignw  mm4, [var]
times   pad - ($ - $op09) db 0xCC

op0A:   psignd  xmm3, [var]
times   pad - ($ - $op0A) db 0xCC

op0B:    pmulhrsw xmm3, xmm2
times   pad - ($ - $op0B) db 0xCC

op0C:   times pad - ($ - $op0C) db 0xCC

op0D:   times    pad - ($ - $op0D) db 0xCC

op0E:   times    pad - ($ - $op0E) db 0xCC

op0F:   times    pad - ($ - $op0F) db 0xCC

op10:   pblendvb xmm1, xmm2
times    pad - ($ - $op10) db 0xCC

op11:   ; invalid
times    pad - ($ - $op11) db 0xCC

op12:   ; invalid
times    pad - ($ - $op12) db 0xCC

op13:   times    pad - ($ - $op13) db 0xCC

op14:    blendvps xmm1, xmm2
times    pad - ($ - $op14) db 0xCC

op15:    blendvpd xmm3, xmm4
times    pad - ($ - $op15) db 0xCC

op16:    times    pad - ($ - $op16) db 0xCC

op17:    ptest    xmm3, xmm1
times    pad - ($ - $op17) db 0xCC

op18:    times    pad - ($ - $op18) db 0xCC

op19:    times    pad - ($ - $op19) db 0xCC

op1A:    times    pad - ($ - $op1A) db 0xCC

op1B:    times    pad - ($ - $op1B) db 0xCC

op1C:    pabsb    xmm1, xmm2
times    pad - ($ - $op1C) db 0xCC

op1D:    pabsw    mm4, mm3
times    pad - ($ - $op1D) db 0xCC

op1E:    pabsd    mm5, mm6
times    pad - ($ - $op1E) db 0xCC

op1F:    ; invalid / reserved
times    pad - ($ - $op1F) db 0xCC

op20:    pmovsxbw xmm1, xmm2
times    pad - ($ - $op20) db 0xCC

op21:    pmovsxbd xmm1, xmm2
times    pad - ($ - $op21) db 0xCC

op22:    pmovsxbq xmm1, xmm2
times    pad - ($ - $op22) db 0xCC

op23:    pmovsxwd xmm1, [var]
times    pad - ($ - $op23) db 0xCC

op24:    pmovsxwq xmm1, xmm2
times    pad - ($ - $op24) db 0xCC

op25:    pmovsxdq xmm1, xmm2
times    pad - ($ - $op25) db 0xCC

op26:    ; invalid
times    pad - ($ - $op26) db 0xCC

op27:    ; invalid
times    pad - ($ - $op27) db 0xCC

op28:    pmuldq   xmm1, xmm2
times    pad - ($ - $op28) db 0xCC

op29:    pcmpeqq  xmm1, xmm2
times    pad - ($ - $op29) db 0xCC

op2A:    movntdqa xmm1, [var]
times    pad - ($ - $op2A) db 0xCC

op2B:    packusdw xmm1, xmm2
times    pad - ($ - $op2B) db 0xCC

op2C:    times    pad - ($ - $op2C) db 0xCC

op2D:    times    pad - ($ - $op2D) db 0xCC

op2E:    times    pad - ($ - $op2E) db 0xCC

op2F:    times    pad - ($ - $op2F) db 0xCC

op30:    pmovzxbw xmm1, [var]
times    pad - ($ - $op30) db 0xCC

op31:    pmovzxbd xmm1, xmm2
times    pad - ($ - $op31) db 0xCC

op32:    pmovzxbq xmm1, [var]
times    pad - ($ - $op32) db 0xCC

op33:    pmovzxwd xmm1, xmm2
times    pad - ($ - $op33) db 0xCC

op34:    pmovzxwq xmm1, [var]
times    pad - ($ - $op34) db 0xCC

op35:    pmovzxdq xmm1, xmm2
times    pad - ($ - $op35) db 0xCC

op36:    times    pad - ($ - $op36) db 0xCC

op37:    pcmpgtq  xmm1, [var]
times    pad - ($ - $op37) db 0xCC

op38:    pminsb   xmm1, [var]
times    pad - ($ - $op38) db 0xCC

op39:    pminsd   xmm1, xmm2
times    pad - ($ - $op39) db 0xCC

op3A:    pminuw   xmm1, xmm2
times    pad - ($ - $op3A) db 0xCC

op3B:    pminud   xmm1, xmm2
times    pad - ($ - $op3B) db 0xCC

op3C:    pmaxsb   xmm1, [var]
times    pad - ($ - $op3C) db 0xCC

op3D:    pmaxsd   xmm1, xmm2
times    pad - ($ - $op3D) db 0xCC

op3E:    pmaxuw   xmm1, [var]
times    pad - ($ - $op3E) db 0xCC

op3F:    pmaxud   xmm1, xmm2
times    pad - ($ - $op3F) db 0xCC

op40:    pmulld   xmm1, [var]
times    pad - ($ - $op40) db 0xCC

op41:    phminposuw xmm1, xmm2
times    pad - ($ - $op41) db 0xCC

op42:    ; invalid reserved
times    pad - ($ - $op42) db 0xCC

op43:    ; invalid reserved
times    pad - ($ - $op43) db 0xCC

op44:    ; invalid reserved
times    pad - ($ - $op44) db 0xCC

op45:    times    pad - ($ - $op45) db 0xCC

op46:    times    pad - ($ - $op46) db 0xCC

op47:    times    pad - ($ - $op47) db 0xCC

op48:    ; invalid reserved
times    pad - ($ - $op48) db 0xCC

op49:    ; invalid reserved
times    pad - ($ - $op49) db 0xCC

op4A:    ; invalid reserved
times    pad - ($ - $op4A) db 0xCC

op4B:    ; invalid reserved
times    pad - ($ - $op4B) db 0xCC

op4C:    ; invalid reserved
times    pad - ($ - $op4C) db 0xCC

op4D:    ; invalid reserved
times    pad - ($ - $op4D) db 0xCC

op4E:    ; invalid reserved
times    pad - ($ - $op4E) db 0xCC

op4F:    ; invalid reserved
times    pad - ($ - $op4F) db 0xCC

op50:    ; invalid reserved
times    pad - ($ - $op50) db 0xCC

op51:    ; invalid reserved
times    pad - ($ - $op51) db 0xCC

op52:    ; invalid reserved
times    pad - ($ - $op52) db 0xCC

op53:    ; invalid reserved
times    pad - ($ - $op53) db 0xCC

op54:    ; invalid reserved
times    pad - ($ - $op54) db 0xCC

op55:    ; invalid reserved
times    pad - ($ - $op55) db 0xCC

op56:    ; invalid reserved
times    pad - ($ - $op56) db 0xCC

op57:    ; invalid reserved
times    pad - ($ - $op57) db 0xCC

op58:    times    pad - ($ - $op58) db 0xCC

op59:    times    pad - ($ - $op59) db 0xCC

op5A:    times    pad - ($ - $op5A) db 0xCC

op5B:    ; invalid reserved
times    pad - ($ - $op5B) db 0xCC

op5C:    ; invalid reserved
times    pad - ($ - $op5C) db 0xCC

op5D:    ; invalid reserved
times    pad - ($ - $op5D) db 0xCC

op5E:    ; invalid reserved
times    pad - ($ - $op5E) db 0xCC

op5F:    ; invalid reserved
times    pad - ($ - $op5F) db 0xCC

op60:    ; invalid reserved
times    pad - ($ - $op60) db 0xCC

op61:    ; invalid reserved
times    pad - ($ - $op61) db 0xCC

op62:    ; invalid reserved
times    pad - ($ - $op62) db 0xCC

op63:    ; invalid reserved
times    pad - ($ - $op63) db 0xCC

op64:    ; invalid reserved
times    pad - ($ - $op64) db 0xCC

op65:    ; invalid reserved
times    pad - ($ - $op65) db 0xCC

op66:    ; invalid reserved
times    pad - ($ - $op66) db 0xCC

op67:    ; invalid reserved
times    pad - ($ - $op67) db 0xCC

op68:    ; invalid reserved
times    pad - ($ - $op68) db 0xCC

op69:    ; invalid reserved
times    pad - ($ - $op69) db 0xCC

op6A:    ; invalid reserved
times    pad - ($ - $op6A) db 0xCC

op6B:    ; invalid reserved
times    pad - ($ - $op6B) db 0xCC

op6C:    ; invalid reserved
times    pad - ($ - $op6C) db 0xCC

op6D:    ; invalid reserved
times    pad - ($ - $op6D) db 0xCC

op6E:    ; invalid reserved
times    pad - ($ - $op6E) db 0xCC

op6F:    ; invalid reserved
times    pad - ($ - $op6F) db 0xCC

op70:    ; invalid reserved
times    pad - ($ - $op70) db 0xCC

op71:    ; invalid reserved
times    pad - ($ - $op71) db 0xCC

op72:    ; invalid reserved
times    pad - ($ - $op72) db 0xCC

op73:    ; invalid reserved
times    pad - ($ - $op73) db 0xCC

op74:    ; invalid reserved
times    pad - ($ - $op74) db 0xCC

op75:    ; invalid reserved
times    pad - ($ - $op75) db 0xCC

op76:    ; invalid reserved
times    pad - ($ - $op76) db 0xCC

op77:    ; invalid reserved
times    pad - ($ - $op77) db 0xCC

op78:    ; invalid reserved
times    pad - ($ - $op78) db 0xCC

op79:    ; invalid reserved
times    pad - ($ - $op79) db 0xCC

op7A:    ; invalid reserved
times    pad - ($ - $op7A) db 0xCC

op7B:    ; invalid reserved
times    pad - ($ - $op7B) db 0xCC

op7C:    ; invalid reserved
times    pad - ($ - $op7C) db 0xCC

op7D:    ; invalid reserved
times    pad - ($ - $op7D) db 0xCC

op7E:    ; invalid reserved
times    pad - ($ - $op7E) db 0xCC

op7F:    ; invalid reserved
times    pad - ($ - $op7F) db 0xCC

op80:    ; not supported in 32bit mode
INVEPT   eax, [var]
times    pad - ($ - $op80) db 0xCC

op81:    INVVPID  eax, [var]
times    pad - ($ - $op81) db 0xCC

op82:    INVPCID  eax, [var]
times    pad - ($ - $op82) db 0xCC

op83:    ;invalid reserved
times    pad - ($ - $op83) db 0xCC

op84:    ;invalid reserved
times    pad - ($ - $op84) db 0xCC

op85:    ;invalid reserved
times    pad - ($ - $op85) db 0xCC

op86:    ;invalid reserved
times    pad - ($ - $op86) db 0xCC

op87:    ;invalid reserved
times    pad - ($ - $op87) db 0xCC

op88:    ;invalid reserved
times    pad - ($ - $op88) db 0xCC

op89:    ;invalid reserved
times    pad - ($ - $op89) db 0xCC

op8A:    ;invalid reserved
times    pad - ($ - $op8A) db 0xCC

op8B:    ;invalid reserved
times    pad - ($ - $op8B) db 0xCC

op8C:    times    pad - ($ - $op8C) db 0xCC

op8D:    ;invalid reserved
times    pad - ($ - $op8D) db 0xCC

op8E:    times    pad - ($ - $op8E) db 0xCC

op8F:    ;invalid reserved
times    pad - ($ - $op8F) db 0xCC

op90:    times    pad - ($ - $op90) db 0xCC

op91:    times    pad - ($ - $op91) db 0xCC

op92:    times    pad - ($ - $op92) db 0xCC

op93:    times    pad - ($ - $op93) db 0xCC

op94:    ; invalid reserved
times    pad - ($ - $op94) db 0xCC

op95:    ; invalid reserved
times    pad - ($ - $op95) db 0xCC

op96:    times    pad - ($ - $op96) db 0xCC

op97:    times    pad - ($ - $op97) db 0xCC

op98:    times    pad - ($ - $op98) db 0xCC

op99:    times    pad - ($ - $op99) db 0xCC

op9A:    times    pad - ($ - $op9A) db 0xCC

op9B:    times    pad - ($ - $op9B) db 0xCC

op9C:    times    pad - ($ - $op9C) db 0xCC

op9D:    times    pad - ($ - $op9D) db 0xCC

op9E:    times    pad - ($ - $op9E) db 0xCC

op9F:    times    pad - ($ - $op9F) db 0xCC

opA0:    ; invalid reserved
times    pad - ($ - $opA0) db 0xCC

opA1:    ; invalid reserved
times    pad - ($ - $opA1) db 0xCC

opA2:    ; invalid reserved
times    pad - ($ - $opA2) db 0xCC

opA3:    ; invalid reserved
times    pad - ($ - $opA3) db 0xCC

opA4:    ; invalid reserved
times    pad - ($ - $opA4) db 0xCC

opA5:    ; invalid reserved
times    pad - ($ - $opA5) db 0xCC

opA6:    times    pad - ($ - $opA6) db 0xCC

opA7:    times    pad - ($ - $opA7) db 0xCC

opA8:    ; invalid reserved
times    pad - ($ - $opA8) db 0xCC

opA9:    ; invalid reserved
times    pad - ($ - $opA9) db 0xCC

opAA:    ; invalid reserved
times    pad - ($ - $opAA) db 0xCC

opAB:    ; invalid reserved
times    pad - ($ - $opAB) db 0xCC

opAC:    ; invalid reserved
times    pad - ($ - $opAC) db 0xCC

opAD:    ; invalid reserved
times    pad - ($ - $opAD) db 0xCC

opAE:    times    pad - ($ - $opAE) db 0xCC

opAF:    times    pad - ($ - $opAF) db 0xCC

opB0:    ; invalid reserved
times    pad - ($ - $opB0) db 0xCC

opB1:    ; invalid reserved
times    pad - ($ - $opB1) db 0xCC

opB2:    ; invalid reserved
times    pad - ($ - $opB2) db 0xCC

opB3:    ; invalid reserved
times    pad - ($ - $opB3) db 0xCC

opB4:    ; invalid reserved
times    pad - ($ - $opB4) db 0xCC

opB5:    ; invalid reserved
times    pad - ($ - $opB5) db 0xCC

opB6:    times    pad - ($ - $opB6) db 0xCC

opB7:    times    pad - ($ - $opB7) db 0xCC

opB8:    ; invalid reserved
times    pad - ($ - $opB8) db 0xCC

opB9:    ; invalid reserved
times    pad - ($ - $opB9) db 0xCC

opBA:    ; invalid reserved
times    pad - ($ - $opBA) db 0xCC

opBB:    ; invalid reserved
times    pad - ($ - $opBB) db 0xCC

opBC:    ; invalid reserved
times    pad - ($ - $opBC) db 0xCC

opBD:    ; invalid reserved
times    pad - ($ - $opBD) db 0xCC

opBE:    times    pad - ($ - $opBE) db 0xCC

opBF:    times    pad - ($ - $opBF) db 0xCC

opC0:    ; invalid reserved
times    pad - ($ - $opC0) db 0xCC

opC1:    ; invalid reserved
times    pad - ($ - $opC1) db 0xCC

opC2:    ; invalid reserved
times    pad - ($ - $opC2) db 0xCC

opC3:    ; invalid reserved
times    pad - ($ - $opC3) db 0xCC

opC4:    ; invalid reserved
times    pad - ($ - $opC4) db 0xCC

opC5:    ; invalid reserved
times    pad - ($ - $opC5) db 0xCC

opC6:    ; invalid reserved
times    pad - ($ - $opC6) db 0xCC

opC7:    ; invalid reserved
times    pad - ($ - $opC7) db 0xCC

opC8:    sha1nexte xmm1, [var]
times    pad - ($ - $opC8) db 0xCC

opC9:    sha1msg1 xmm3, xmm4
times    pad - ($ - $opC9) db 0xCC

opCA:    sha1msg2 xmm2, xmm3
times    pad - ($ - $opCA) db 0xCC

opCB:    sha256rnds2 xmm2, [var]
times    pad - ($ - $opCB) db 0xCC

opCC:    sha256msg1 xmm1, [var]
times    pad - ($ - $opCC) db 0xCC

opCD:    sha256msg2 xmm2, xmm3
times    pad - ($ - $opCD) db 0xCC

opCE:    ; invalid reserved
times    pad - ($ - $opCE) db 0xCC

opCF:    ; invalid reserved
times    pad - ($ - $opCF) db 0xCC

opD0:    ; invalid reserved
times    pad - ($ - $opD0) db 0xCC

opD1:    ; invalid reserved
times    pad - ($ - $opD1) db 0xCC

opD2:    ; invalid reserved
times    pad - ($ - $opD2) db 0xCC

opD3:    ; invalid reserved
times    pad - ($ - $opD3) db 0xCC

opD4:    ; invalid reserved
times    pad - ($ - $opD4) db 0xCC

opD5:    ; invalid reserved
times    pad - ($ - $opD5) db 0xCC

opD6:    ; invalid reserved
times    pad - ($ - $opD6) db 0xCC

opD7:    ; invalid reserved
times    pad - ($ - $opD7) db 0xCC

opD8:    ; invalid reserved
times    pad - ($ - $opD8) db 0xCC

opD9:    ; invalid reserved
times    pad - ($ - $opD9) db 0xCC

opDA:    ; invalid reserved
times    pad - ($ - $opDA) db 0xCC

opDB:    aesimc   xmm1, [var]
times    pad - ($ - $opDB) db 0xCC

opDC:    aesenc   xmm2, [var]
times    pad - ($ - $opDC) db 0xCC

opDD:    aesenclast  xmm2, xmm1
times    pad - ($ - $opDD) db 0xCC

opDE:    aesdec   xmm1, xmm2
times    pad - ($ - $opDE) db 0xCC

opDF:    aesdeclast  xmm0, xmm1
times    pad - ($ - $opDF) db 0xCC

opE0:    ; invalid reserved
times    pad - ($ - $opE0) db 0xCC

opE1:    ; invalid reserved
times    pad - ($ - $opE1) db 0xCC

opE2:    ; invalid reserved
times    pad - ($ - $opE2) db 0xCC

opE3:    ; invalid reserved
times    pad - ($ - $opE3) db 0xCC

opE4:    ; invalid reserved
times    pad - ($ - $opE4) db 0xCC

opE5:    ; invalid reserved
times    pad - ($ - $opE5) db 0xCC

opE6:    ; invalid reserved
times    pad - ($ - $opE6) db 0xCC

opE7:    ; invalid reserved
times    pad - ($ - $opE7) db 0xCC

opE8:    ; invalid reserved
times    pad - ($ - $opE8) db 0xCC

opE9:    ; invalid reserved
times    pad - ($ - $opE9) db 0xCC

opEA:    ; invalid reserved
times    pad - ($ - $opEA) db 0xCC

opEB:    ; invalid reserved
times    pad - ($ - $opEB) db 0xCC

opEC:    ; invalid reserved
times    pad - ($ - $opEC) db 0xCC

opED:    ; invalid reserved
times    pad - ($ - $opED) db 0xCC

opEE:    ; invalid reserved
times    pad - ($ - $opEE) db 0xCC

opEF:    ; invalid reserved
times    pad - ($ - $opEF) db 0xCC

opF0:    movbe    eax, [var]
times    pad - ($ - $opF0) db 0xCC

opF1:    movbe    [var], ebx
times    pad - ($ - $opF1) db 0xCC

opF2:    times    pad - ($ - $opF2) db 0xCC

opF3:    times    pad - ($ - $opF3) db 0xCC

opF4:    ; invalid unsupported
times    pad - ($ - $opF4) db 0xCC

opF5:    ; invalid unsupported
times    pad - ($ - $opF5) db 0xCC

opF6:    adcx     eax, [var]
times    pad - ($ - $opF6) db 0xCC

opF7:    ; invalid
times    pad - ($ - $opF7) db 0xCC

opF8:    ; invalid
times    pad - ($ - $opF8) db 0xCC

opF9:    ; invalid
times    pad - ($ - $opF9) db 0xCC

opFA:    ; invalid
times    pad - ($ - $opFA) db 0xCC

opFB:    ; invalid
times    pad - ($ - $opFB) db 0xCC

opFC:    ; invalid
times    pad - ($ - $opFC) db 0xCC

opFD:    ; invalid
times    pad - ($ - $opFD) db 0xCC

opFE:    ; invalid
times    pad - ($ - $opFE) db 0xCC

opFF:    ; invalid
times    pad - ($ - $opFF) db 0xCC


; Variables
; ---------------------------------
var:
    times pad - ($ - $var) db 0x90