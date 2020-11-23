; ------------------------------------------
; VOL. 2D, Appendix A, pg. 14-15 (Intel Manual)
; ------------------------------------------

[BITS 32]

; Macros
pad     equ   16

; -------------------------------
; 3-byte 38 opcodes tests
; -------------------------------

op00:   vpermq   ymm1, [var], 0x12
times   pad - ($ - $op00) db 0xCC

op01:   times   pad - ($ - $op01) db 0xCC

op02:   times   pad - ($ - $op02) db 0xCC

;op03:   ; invalid / reserved
;times   pad - ($ - $op03) db 0xCC

;op04:   times   pad - ($ - $op04) db 0xCC

;op05:   times   pad - ($ - $op05) db 0xCC

;op06:   times   pad - ($ - $op06) db 0xCC

;op07:   ; invalid / reserved
;times   pad - ($ - $op07) db 0xCC

op08:   roundps xmm1, [var], 0x11
times   pad - ($ - $op08) db 0xCC

op09:   roundpd xmm2, [var], 0x11
times   pad - ($ - $op09) db 0xCC

op0A:   roundss xmm2, [var], 0x11
times   pad - ($ - $op0A) db 0xCC

op0B:   roundsd xmm2, [var], 0x11
times   pad - ($ - $op0B) db 0xCC

op0C:   blendps xmm2, xmm3, 0x11
times   pad - ($ - $op0C) db 0xCC

op0D:   blendpd xmm2, xmm3, 0x11
times   pad - ($ - $op0D) db 0xCC

op0E:   pblendw xmm3, [var], 0x11
times   pad - ($ - $op0E) db 0xCC

op0F:   palignr xmm1, [var], 0x22
times   pad - ($ - $op0F) db 0xCC

op10:
; invalid / reserved
times   pad - ($ - $op10) db 0xCC

op11:
; invalid / reserved
times   pad - ($ - $op11) db 0xCC

op12:
; invalid / reserved
times   pad - ($ - $op12) db 0xCC

op13:
; invalid / reserved
times   pad - ($ - $op13) db 0xCC

op14:   pextrb  [var], xmm1, 0x33
times   pad - ($ - $op14) db 0xCC

op15:   pextrw  [var], xmm2, 0x33
times   pad - ($ - $op15) db 0xCC

op16:   pextrd  [var], xmm0, 0x33
times   pad - ($ - $op16) db 0xCC

op17:   extractps  [var], xmm2, 0x44
times   pad - ($ - $op17) db 0xCC

;op18:   times   pad - ($ - $op18) db 0xCC

;op19:   times   pad - ($ - $op19) db 0xCC

op1A:   ; invalid
times   pad - ($ - $op1A) db 0xCC

op1B:   ; invalid
times   pad - ($ - $op1B) db 0xCC

op1C:   ; invalid
times   pad - ($ - $op1C) db 0xCC

op1D:   times   pad - ($ - $op1D) db 0xCC

op1E:   times   pad - ($ - $op1E) db 0xCC

op1F:   times   pad - ($ - $op1F) db 0xCC

op20:   pinsrb  xmm1, [var], 0x77
times   pad - ($ - $op20) db 0xCC

op21:   insertps  xmm2, [var], 0x77
times   pad - ($ - $op21) db 0xCC

op22:   pinsrd  xmm4, [var], 0x88
times   pad - ($ - $op22) db 0xCC

op23:   ; invalid
times   pad - ($ - $op23) db 0xCC

op24:   ; invalid
times   pad - ($ - $op24) db 0xCC

op25:   ; invalid
times   pad - ($ - $op25) db 0xCC

op26:   ; invalid
times   pad - ($ - $op26) db 0xCC

op27:   ; invalid
times   pad - ($ - $op27) db 0xCC

op28:   ; invalid
times   pad - ($ - $op28) db 0xCC

op29:   ; invalid
times   pad - ($ - $op29) db 0xCC

op2A:   ; invalid
times   pad - ($ - $op2A) db 0xCC

op2B:   ; invalid
times   pad - ($ - $op2B) db 0xCC

op2C:   ; invalid
times   pad - ($ - $op2C) db 0xCC

op2D:   ; invalid
times   pad - ($ - $op2D) db 0xCC

op2E:   ; invalid
times   pad - ($ - $op2E) db 0xCC

op2F:   ; invalid
times   pad - ($ - $op2F) db 0xCC

op30:   ; invalid
times   pad - ($ - $op30) db 0xCC

op31:   ; invalid
times   pad - ($ - $op31) db 0xCC

op32:   ; invalid
times   pad - ($ - $op32) db 0xCC

op33:   ; invalid
times   pad - ($ - $op33) db 0xCC

op34:   ; invalid
times   pad - ($ - $op34) db 0xCC

op35:   ; invalid
times   pad - ($ - $op35) db 0xCC

op36:   ; invalid
times   pad - ($ - $op36) db 0xCC

op37:   ; invalid
times   pad - ($ - $op37) db 0xCC

op38:   ; invalid
times   pad - ($ - $op38) db 0xCC

op39:   ; invalid
times   pad - ($ - $op39) db 0xCC

op3A:   ; invalid
times   pad - ($ - $op3A) db 0xCC

op3B:   ; invalid
times   pad - ($ - $op3B) db 0xCC

op3C:   ; invalid
times   pad - ($ - $op3C) db 0xCC

op3D:   ; invalid
times   pad - ($ - $op3D) db 0xCC

op3E:   ; invalid
times   pad - ($ - $op3E) db 0xCC

op3F:   ; invalid
times   pad - ($ - $op3F) db 0xCC

op40:   dpps    xmm1, [var], 0x22
times   pad - ($ - $op40) db 0xCC

op41:   dppd    xmm2, [var], 0x33
times   pad - ($ - $op41) db 0xCC

op42:   mpsadbw xmm0, xmm3, 0x33
times   pad - ($ - $op42) db 0xCC

op43:   ; unused, invalid
times   pad - ($ - $op43) db 0xCC

op44:   pclmulqdq xmm0, xmm2, 0x34
times   pad - ($ - $op44) db 0xCC

op45:   ; invalid, unused
times   pad - ($ - $op45) db 0xCC

op46:   ; invalid, unused
times   pad - ($ - $op46) db 0xCC

op47:   ; invalid, unused
times   pad - ($ - $op47) db 0xCC

op48:   ; invalid, unused
times   pad - ($ - $op48) db 0xCC

op49:   ; invalid, unused
times   pad - ($ - $op49) db 0xCC

op4A:   times   pad - ($ - $op4A) db 0xCC

op4B:   times   pad - ($ - $op4B) db 0xCC

op4C:   times   pad - ($ - $op4C) db 0xCC

op4D:   ; invalid, unused
times   pad - ($ - $op4D) db 0xCC

op4E:   ; invalid, unused
times   pad - ($ - $op4E) db 0xCC

op4F:   ; invalid, unused
times   pad - ($ - $op4F) db 0xCC

op50:   ; invalid, unused
times   pad - ($ - $op50) db 0xCC

op51:   ; invalid, unused
times   pad - ($ - $op51) db 0xCC

op52:   ; invalid, unused
times   pad - ($ - $op52) db 0xCC

op53:   ; invalid, unused
times   pad - ($ - $op53) db 0xCC

op54:   ; invalid, unused
times   pad - ($ - $op54) db 0xCC

op55:   ; invalid, unused
times   pad - ($ - $op55) db 0xCC

op56:   ; invalid, unused
times   pad - ($ - $op56) db 0xCC

op57:   ; invalid, unused
times   pad - ($ - $op57) db 0xCC

op58:   ; invalid, unused
times   pad - ($ - $op58) db 0xCC

op59:   ; invalid, unused
times   pad - ($ - $op59) db 0xCC

op5A:   ; invalid, unused
times   pad - ($ - $op5A) db 0xCC

op5B:   ; invalid, unused
times   pad - ($ - $op5B) db 0xCC

op5C:   ; invalid, unused
times   pad - ($ - $op5C) db 0xCC

op5D:   ; invalid, unused
times   pad - ($ - $op5D) db 0xCC

op5E:   ; invalid, unused
times   pad - ($ - $op5E) db 0xCC

op5F:   ; invalid, unused
times   pad - ($ - $op5F) db 0xCC

op60:   pcmpestrm xmm0, [var], 0x11
times   pad - ($ - $op60) db 0xCC

op61:   pcmpestri xmm0, [var], 0x11
times   pad - ($ - $op61) db 0xCC

op62:   pcmpistrm xmm0, [var], 0x11
times   pad - ($ - $op62) db 0xCC

op63:   pcmpistri xmm3, [var], 0x11
times   pad - ($ - $op63) db 0xCC

op64:   ; invalid
times   pad - ($ - $op64) db 0xCC

op65:   ; invalid
times   pad - ($ - $op65) db 0xCC

op66:   ; invalid
times   pad - ($ - $op66) db 0xCC

op67:   ; invalid
times   pad - ($ - $op67) db 0xCC

op68:   ; invalid
times   pad - ($ - $op68) db 0xCC

op69:   ; invalid
times   pad - ($ - $op69) db 0xCC

op6A:   ; invalid
times   pad - ($ - $op6A) db 0xCC

op6B:   ; invalid
times   pad - ($ - $op6B) db 0xCC

op6C:   ; invalid
times   pad - ($ - $op6C) db 0xCC

op6D:   ; invalid
times   pad - ($ - $op6D) db 0xCC

op6E:   ; invalid
times   pad - ($ - $op6E) db 0xCC

op6F:   ; invalid
times   pad - ($ - $op6F) db 0xCC

op70:   ; invalid
times   pad - ($ - $op70) db 0xCC

op71:   ; invalid
times   pad - ($ - $op71) db 0xCC

op72:   ; invalid
times   pad - ($ - $op72) db 0xCC

op73:   ; invalid
times   pad - ($ - $op73) db 0xCC

op74:   ; invalid
times   pad - ($ - $op74) db 0xCC

op75:   ; invalid
times   pad - ($ - $op75) db 0xCC

op76:   ; invalid
times   pad - ($ - $op76) db 0xCC

op77:   ; invalid
times   pad - ($ - $op77) db 0xCC

op78:   ; invalid
times   pad - ($ - $op78) db 0xCC

op79:   ; invalid
times   pad - ($ - $op79) db 0xCC

op7A:   ; invalid
times   pad - ($ - $op7A) db 0xCC

op7B:   ; invalid
times   pad - ($ - $op7B) db 0xCC

op7C:   ; invalid
times   pad - ($ - $op7C) db 0xCC

op7D:   ; invalid
times   pad - ($ - $op7D) db 0xCC

op7E:   ; invalid
times   pad - ($ - $op7E) db 0xCC

op7F:   ; invalid
times   pad - ($ - $op7F) db 0xCC

op80:   ; invalid
times   pad - ($ - $op80) db 0xCC

op81:   ; invalid
times   pad - ($ - $op81) db 0xCC

op82:   ; invalid
times   pad - ($ - $op82) db 0xCC

op83:   ; invalid
times   pad - ($ - $op83) db 0xCC

op84:   ; invalid
times   pad - ($ - $op84) db 0xCC

op85:   ; invalid
times   pad - ($ - $op85) db 0xCC

op86:   ; invalid
times   pad - ($ - $op86) db 0xCC

op87:   ; invalid
times   pad - ($ - $op87) db 0xCC

op88:   ; invalid
times   pad - ($ - $op88) db 0xCC

op89:   ; invalid
times   pad - ($ - $op89) db 0xCC

op8A:   ; invalid
times   pad - ($ - $op8A) db 0xCC

op8B:   ; invalid
times   pad - ($ - $op8B) db 0xCC

op8C:   ; invalid
times   pad - ($ - $op8C) db 0xCC

op8D:   ; invalid
times   pad - ($ - $op8D) db 0xCC

op8E:   ; invalid
times   pad - ($ - $op8E) db 0xCC

op8F:   ; invalid
times   pad - ($ - $op8F) db 0xCC

op90:   ; invalid
times   pad - ($ - $op90) db 0xCC

op91:   ; invalid
times   pad - ($ - $op91) db 0xCC

op92:   ; invalid
times   pad - ($ - $op92) db 0xCC

op93:   ; invalid
times   pad - ($ - $op93) db 0xCC

op94:   ; invalid
times   pad - ($ - $op94) db 0xCC

op95:   ; invalid
times   pad - ($ - $op95) db 0xCC

op96:   ; invalid
times   pad - ($ - $op96) db 0xCC

op97:   ; invalid
times   pad - ($ - $op97) db 0xCC

op98:   ; invalid
times   pad - ($ - $op98) db 0xCC

op99:   ; invalid
times   pad - ($ - $op99) db 0xCC

op9A:   ; invalid
times   pad - ($ - $op9A) db 0xCC

op9B:   ; invalid
times   pad - ($ - $op9B) db 0xCC

op9C:   ; invalid
times   pad - ($ - $op9C) db 0xCC

op9D:   ; invalid
times   pad - ($ - $op9D) db 0xCC

op9E:   ; invalid
times   pad - ($ - $op9E) db 0xCC

op9F:   ; invalid
times   pad - ($ - $op9F) db 0xCC

opA0:   ; invalid
times   pad - ($ - $opA0) db 0xCC

opA1:   ; invalid
times   pad - ($ - $opA1) db 0xCC

opA2:   ; invalid
times   pad - ($ - $opA2) db 0xCC

opA3:   ; invalid
times   pad - ($ - $opA3) db 0xCC

opA4:   ; invalid
times   pad - ($ - $opA4) db 0xCC

opA5:   ; invalid
times   pad - ($ - $opA5) db 0xCC

opA6:   ; invalid
times   pad - ($ - $opA6) db 0xCC

opA7:   ; invalid
times   pad - ($ - $opA7) db 0xCC

opA8:   ; invalid
times   pad - ($ - $opA8) db 0xCC

opA9:   ; invalid
times   pad - ($ - $opA9) db 0xCC

opAA:   ; invalid
times   pad - ($ - $opAA) db 0xCC

opAB:   ; invalid
times   pad - ($ - $opAB) db 0xCC

opAC:   ; invalid
times   pad - ($ - $opAC) db 0xCC

opAD:   ; invalid
times   pad - ($ - $opAD) db 0xCC

opAE:   ; invalid
times   pad - ($ - $opAE) db 0xCC

opAF:   ; invalid
times   pad - ($ - $opAF) db 0xCC

opB0:   ; invalid
times   pad - ($ - $opB0) db 0xCC

opB1:   ; invalid
times   pad - ($ - $opB1) db 0xCC

opB2:   ; invalid
times   pad - ($ - $opB2) db 0xCC

opB3:   ; invalid
times   pad - ($ - $opB3) db 0xCC

opB4:   ; invalid
times   pad - ($ - $opB4) db 0xCC

opB5:   ; invalid
times   pad - ($ - $opB5) db 0xCC

opB6:   ; invalid
times   pad - ($ - $opB6) db 0xCC

opB7:   ; invalid
times   pad - ($ - $opB7) db 0xCC

opB8:   ; invalid
times   pad - ($ - $opB8) db 0xCC

opB9:   ; invalid
times   pad - ($ - $opB9) db 0xCC

opBA:   ; invalid
times   pad - ($ - $opBA) db 0xCC

opBB:   ; invalid
times   pad - ($ - $opBB) db 0xCC

opBC:   ; invalid
times   pad - ($ - $opBC) db 0xCC

opBD:   ; invalid
times   pad - ($ - $opBD) db 0xCC

opBE:   ; invalid
times   pad - ($ - $opBE) db 0xCC

opBF:   ; invalid
times   pad - ($ - $opBF) db 0xCC

opC0:   ; invalid
times   pad - ($ - $opC0) db 0xCC

opC1:   ; invalid
times   pad - ($ - $opC1) db 0xCC

opC2:   ; invalid
times   pad - ($ - $opC2) db 0xCC

opC3:   ; invalid
times   pad - ($ - $opC3) db 0xCC

opC4:   ; invalid
times   pad - ($ - $opC4) db 0xCC

opC5:   ; invalid
times   pad - ($ - $opC5) db 0xCC

opC6:   ; invalid
times   pad - ($ - $opC6) db 0xCC

opC7:   ; invalid
times   pad - ($ - $opC7) db 0xCC

opC8:   ; invalid
times   pad - ($ - $opC8) db 0xCC

opC9:   ; invalid
times   pad - ($ - $opC9) db 0xCC

opCA:   ; invalid
times   pad - ($ - $opCA) db 0xCC

opCB:   ; invalid
times   pad - ($ - $opCB) db 0xCC

opCC:   sha1rnds4 xmm0, xmm2, 0x22
times   pad - ($ - $opCC) db 0xCC

opCD:   ; invalid
times   pad - ($ - $opCD) db 0xCC

opCE:   ; invalid
times   pad - ($ - $opCE) db 0xCC

opCF:   ; invalid
times   pad - ($ - $opCF) db 0xCC

opD0:   ; invalid
times   pad - ($ - $opD0) db 0xCC

opD1:   ; invalid
times   pad - ($ - $opD1) db 0xCC

opD2:   ; invalid
times   pad - ($ - $opD2) db 0xCC

opD3:   ; invalid
times   pad - ($ - $opD3) db 0xCC

opD4:   ; invalid
times   pad - ($ - $opD4) db 0xCC

opD5:   ; invalid
times   pad - ($ - $opD5) db 0xCC

opD6:   ; invalid
times   pad - ($ - $opD6) db 0xCC

opD7:   ; invalid
times   pad - ($ - $opD7) db 0xCC

opD8:   ; invalid
times   pad - ($ - $opD8) db 0xCC

opD9:   ; invalid
times   pad - ($ - $opD9) db 0xCC

opDA:   ; invalid
times   pad - ($ - $opDA) db 0xCC

opDB:   ; invalid
times   pad - ($ - $opDB) db 0xCC

opDC:   ; invalid
times   pad - ($ - $opDC) db 0xCC

opDD:   ; invalid
times   pad - ($ - $opDD) db 0xCC

opDE:   ; invalid
times   pad - ($ - $opDE) db 0xCC

opDF:   times   pad - ($ - $opDF) db 0xCC

opE0:   ; invalid
times   pad - ($ - $opE0) db 0xCC

opE1:   ; invalid
times   pad - ($ - $opE1) db 0xCC

opE2:   ; invalid
times   pad - ($ - $opE2) db 0xCC

opE3:   ; invalid
times   pad - ($ - $opE3) db 0xCC

opE4:   ; invalid
times   pad - ($ - $opE4) db 0xCC

opE5:   ; invalid
times   pad - ($ - $opE5) db 0xCC

opE6:   ; invalid
times   pad - ($ - $opE6) db 0xCC

opE7:   ; invalid
times   pad - ($ - $opE7) db 0xCC

opE8:   ; invalid
times   pad - ($ - $opE8) db 0xCC

opE9:   ; invalid
times   pad - ($ - $opE9) db 0xCC

opEA:   ; invalid
times   pad - ($ - $opEA) db 0xCC

opEB:   ; invalid
times   pad - ($ - $opEB) db 0xCC

opEC:   ; invalid
times   pad - ($ - $opEC) db 0xCC

opED:   ; invalid
times   pad - ($ - $opED) db 0xCC

opEE:   ; invalid
times   pad - ($ - $opEE) db 0xCC

opEF:   times   pad - ($ - $opEF) db 0xCC

opF0:   ; invalid
times   pad - ($ - $opF0) db 0xCC

opF1:   ; invalid
times   pad - ($ - $opF1) db 0xCC

opF2:   ; invalid
times   pad - ($ - $opF2) db 0xCC

opF3:   ; invalid
times   pad - ($ - $opF3) db 0xCC

opF4:   ; invalid
times   pad - ($ - $opF4) db 0xCC

opF5:   ; invalid
times   pad - ($ - $opF5) db 0xCC

opF6:   ; invalid
times   pad - ($ - $opF6) db 0xCC

opF7:   ; invalid
times   pad - ($ - $opF7) db 0xCC

opF8:   ; invalid
times   pad - ($ - $opF8) db 0xCC

opF9:   ; invalid
times   pad - ($ - $opF9) db 0xCC

opFA:   ; invalid
times   pad - ($ - $opFA) db 0xCC

opFB:   ; invalid
times   pad - ($ - $opFB) db 0xCC

opFC:   ; invalid
times   pad - ($ - $opFC) db 0xCC

opFD:   ; invalid
times   pad - ($ - $opFD) db 0xCC

opFE:   ; invalid
times   pad - ($ - $opFE) db 0xCC

opFF:   times   pad - ($ - $opFF) db 0xCC


; Variables
; ---------------------------------
var:
    times pad - ($ - $var) db 0x90