; ------------------------------------------
; VOL. 2D, Appendix A, pg. 7-8 (Intel Manual)
; ------------------------------------------

[BITS 32]

; Macros
pad     equ   16

; -------------------------------
; 2-byte opcodes tests (VEX)
; -------------------------------

op00:   lldt    [var]
times   pad - ($ - $op00) db 0xCC;

op01:   lmsw    [var]
times   pad - ($ - $op01) db 0xCC

op02:   lar     eax, [var]
times   pad - ($ - $op02) db 0xCC

op03:   lsl     eax, [var]
times   pad - ($ - $op03) db 0xCC

op04:   ; unused / reserved
times   pad - ($ - $op04) db 0xCC

op05:   ; syscall  | invalid in 32bit mode
times   pad - ($ - $op05) db 0xCC

op06:   clts
times   pad - ($ - $op06) db 0xCC

op07:   ; sysret  | invalid in 32bit mode
times   pad - ($ - $op07) db 0xCC

op08:   invd
times   pad - ($ - $op08) db 0xCC

op09:   wbinvd
times   pad - ($ - $op09) db 0xCC

op0A:   ; unused / reserved
times   pad - ($ - $op0A) db 0xCC

op0B:   dw      0B0fh; 2byte illegal opcoe UD2
times   pad - ($ - $op0B) db 0xCC

op0C:   ; unused / reserved
times   pad - ($ - $op0C) db 0xCC

op0D:   dw      0D0fh ;prefetchw
times   pad - ($ - $op0D) db 0xCC

op0E:   ; unused / reserved
times   pad - ($ - $op0E) db 0xCC

op0F:   ; unused / reserved
times   pad - ($ - $op0F) db 0xCC

op10:   vmovupd  xmm1, xmm2
times   pad - ($ - $op10) db 0xCC

op11:   vmovsd   [var], xmm1
times   pad - ($ - $op11) db 0xCC

op12:   vmovsldup  xmm1, [var]
times   pad - ($ - $op12) db 0xCC

op13:   vmovlpd  qword [var], xmm1
times   pad - ($ - $op13) db 0xCC

op14:   vunpcklpd xmm1, xmm2
times   pad - ($ - $op14) db 0xCC

op15:   vunpckhpd xmm1, xmm2
times   pad - ($ - $op15) db 0xCC

op16:   vmovshdup xmm1, xmm2
times   pad - ($ - $op16) db 0xCC

op17:   vmovhps  [var], xmm1
times   pad - ($ - $op17) db 0xCC

op18:   ; reserved
times   pad - ($ - $op18) db 0xCC

op19:   ; reserved
times   pad - ($ - $op19) db 0xCC

op1A:   ; reserved
times   pad - ($ - $op1A) db 0xCC

op1B:   ; reserved
times   pad - ($ - $op1B) db 0xCC

op1C:   ; reserved
times   pad - ($ - $op1C) db 0xCC

op1D:   ; reserved
times   pad - ($ - $op1D) db 0xCC

op1E:   ; reserved
times   pad - ($ - $op1E) db 0xCC

op1F:   ; reserved
times   pad - ($ - $op1F) db 0xCC

op20:   mov     eax, cr0
times   pad - ($ - $op20) db 0xCC

op21:   mov     eax, dr0
times   pad - ($ - $op21) db 0xCC

op22:   mov     cr0, eax
times   pad - ($ - $op22) db 0xCC

op23:   mov     dr0, eax
times   pad - ($ - $op23) db 0xCC

op24:   ; reserved
times   pad - ($ - $op24) db 0xCC

op25:   ; reserved
times   pad - ($ - $op25) db 0xCC

op26:   ; reserved
times   pad - ($ - $op26) db 0xCC

op27:   ; reserved
times   pad - ($ - $op27) db 0xCC

op28:   vmovapd  xmm1, [var]
times   pad - ($ - $op28) db 0xCC

op29:   vmovapd  [var], xmm1
times   pad - ($ - $op29) db 0xCC

op2A:   vcvtsi2ss xmm1, [var]
times   pad - ($ - $op2A) db 0xCC

op2B:   vmovntpd [var], xmm1
times   pad - ($ - $op2B) db 0xCC

op2C:   vcvttss2si eax, xmm1
times   pad - ($ - $op2C) db 0xCC

op2D:   vcvtsd2si eax, xmm1
times   pad - ($ - $op2D) db 0xCC

op2E:   vucomisd xmm2, xmm1
times   pad - ($ - $op2E) db 0xCC

op2F:   vcomisd  xmm1, xmm2
times   pad - ($ - $op2F) db 0xCC

op30:   wrmsr
times   pad - ($ - $op30) db 0xCC

op31:   rdtsc
times   pad - ($ - $op31) db 0xCC

op32:   rdmsr
times   pad - ($ - $op32) db 0xCC

op33:   rdpmc
times   pad - ($ - $op33) db 0xCC

op34:   sysenter
times   pad - ($ - $op34) db 0xCC

op35:   sysexit
times   pad - ($ - $op35) db 0xCC

op36:   ; reserved
times   pad - ($ - $op36) db 0xCC

op37:   getsec
times   pad - ($ - $op37) db 0xCC

op38:   ; 3-byte OP escape
times   pad - ($ - $op38) db 0xCC

op39:   ; reserved
times   pad - ($ - $op39) db 0xCC

op3A:   ; 3-byte OP escape
times   pad - ($ - $op3A) db 0xCC

op3B:   ; reserved
times   pad - ($ - $op3B) db 0xCC

op3C:   ; reserved
times   pad - ($ - $op3C) db 0xCC

op3D:   ; reserved
times   pad - ($ - $op3D) db 0xCC

op3E:   ; reserved
times   pad - ($ - $op3E) db 0xCC

op3F:   ; reserved
times   pad - ($ - $op3F) db 0xCC

op40:   cmovo   eax, [var]
times   pad - ($ - $op40) db 0xCC

op41:   cmovno  eax, ebx
times   pad - ($ - $op41) db 0xCC

op42:   cmovb   eax, [var]
times   pad - ($ - $op42) db 0xCC

op43:   cmovnb  eax, ecx
times   pad - ($ - $op43) db 0xCC

op44:   cmovz   eax, [var]
times   pad - ($ - $op44) db 0xCC

op45:   cmovnz  eax, edx
times   pad - ($ - $op45) db 0xCC

op46:   cmovbe  eax, [var]
times   pad - ($ - $op46) db 0xCC

op47:   cmovnbe eax, [var]
times   pad - ($ - $op47) db 0xCC

op48:   cmovs   eax, [var]
times   pad - ($ - $op48) db 0xCC

op49:   cmovns  eax, [var]
times   pad - ($ - $op49) db 0xCC

op4A:   cmovp   eax, [var]
times   pad - ($ - $op4A) db 0xCC

op4B:   cmovnp  eax, [var]
times   pad - ($ - $op4B) db 0xCC

op4C:   cmovnge eax, [var]
times   pad - ($ - $op4C) db 0xCC

op4D:   cmovge  eax, edx
times   pad - ($ - $op4D) db 0xCC

op4E:   cmovng  ecx, edx
times   pad - ($ - $op4E) db 0xCC

op4F:   cmovg   ebx, [var]
times   pad - ($ - $op4F) db 0xCC

op50:   vmovmskpd eax, xmm0
times   pad - ($ - $op50) db 0xCC

op51:   vsqrtpd  xmm0, xmm1
times   pad - ($ - $op51) db 0xCC

op52:   vrsqrtps xmm0, xmm1
times   pad - ($ - $op52) db 0xCC

op53:   vrcpps   xmm0, xmm1
times   pad - ($ - $op53) db 0xCC

op54:   vandpd   xmm1, xmm2
times   pad - ($ - $op54) db 0xCC

op55:   vandnpd  xmm1, xmm2
times   pad - ($ - $op55) db 0xCC

op56:   vorpd    xmm1, xmm2
times   pad - ($ - $op56) db 0xCC

op57:   vxorpd   xmm1, xmm0
times   pad - ($ - $op57) db 0xCC

op58:   vaddsd   xmm1, xmm0
times   pad - ($ - $op58) db 0xCC

op59:   vmulss   xmm1, xmm0
times   pad - ($ - $op59) db 0xCC

op5A:   vcvtpd2ps xmm1, xmm0
times   pad - ($ - $op5A) db 0xCC

op5B:   vcvtdq2ps xmm1, xmm0
times   pad - ($ - $op5B) db 0xCC

op5C:   vsubpd   xmm1, [var]
times   pad - ($ - $op5C) db 0xCC

op5D:   vminsd   xmm2, [var]
times   pad - ($ - $op5D) db 0xCC

op5E:   vdivpd   xmm0, [var]
times   pad - ($ - $op5E) db 0xCC

op5F:   vmaxpd   xmm0, xmm1
times   pad - ($ - $op5F) db 0xCC

op60:   vpunpcklbw xmm0,xmm1, [var]
times   pad - ($ - $op60) db 0xCC

op61:   vpunpcklwd xmm0,xmm2, [var]
times   pad - ($ - $op61) db 0xCC

op62:   vpunpckldq xmm1, xmm3, [var]
times   pad - ($ - $op62) db 0xCC

op63:   vpacksswb xmm1, xmm0, [var]
times   pad - ($ - $op63) db 0xCC

op64:   vpcmpgtb xmm1, xmm0, xmm3
times   pad - ($ - $op64) db 0xCC

op65:   vpcmpgtw xmm1, xmm0, xmm2
times   pad - ($ - $op65) db 0xCC

op66:   vpcmpgtd xmm1, xmm3, [var]
times   pad - ($ - $op66) db 0xCC

op67:   vpackuswb xmm0, xmm3, xmm4
times   pad - ($ - $op67) db 0xCC

op68:   vpunpckhbw xmm0, xmm3,xmm4
times   pad - ($ - $op68) db 0xCC

op69:   vpunpckhwd xmm0, xmm3, xmm1
times   pad - ($ - $op69) db 0xCC

op6A:   vpunpckhdq xmm0, xmm3, xmm2
times   pad - ($ - $op6A) db 0xCC

op6B:   vpackssdw xmm0, xmm3, xmm5
times   pad - ($ - $op6B) db 0xCC

op6C:   vpunpcklqdq xmm1, xmm2, xmm3
times   pad - ($ - $op6C) db 0xCC

op6D:   punpckhqdq xmm0, [var]
times   pad - ($ - $op6D) db 0xCC

op6E:   vmovd    xmm0,[var]
times   pad - ($ - $op6E) db 0xCC

op6F:   vmovdqa  xmm1, [var]
times   pad - ($ - $op6F) db 0xCC

op70:   vpshufd  xmm0, [var], 0x11
times   pad - ($ - $op70) db 0xCC

op71:   psrlw   xmm0, 0x11
times   pad - ($ - $op71) db 0xCC

op72:   psrld   xmm0, 0x11
times   pad - ($ - $op72) db 0xCC

op73:   psrlq   xmm2, 0x11
times   pad - ($ - $op73) db 0xCC

op74:   vpcmpeqb xmm2, xmm4
times   pad - ($ - $op74) db 0xCC

op75:   vpcmpeqw xmm1, xmm3
times   pad - ($ - $op75) db 0xCC

op76:   vpcmpeqd xmm1, xmm3
times   pad - ($ - $op76) db 0xCC

op77:   vzeroall
times   pad - ($ - $op77) db 0xCC

op78:   vmread  [var], eax
times   pad - ($ - $op78) db 0xCC

op79:   vmwrite eax, [var]
times   pad - ($ - $op79) db 0xCC

op7A:   ; reserved
times   pad - ($ - $op7A) db 0xCC

op7B:   ; reserved
times   pad - ($ - $op7B) db 0xCC

op7C:   vhaddps  xmm0, xmm4, [var]
times   pad - ($ - $op7C) db 0xCC

op7D:   vhsubps  xmm1, xmm3, [var]
times   pad - ($ - $op7D) db 0xCC

op7E:   vmovq    xmm1, xmm3
times   pad - ($ - $op7E) db 0xCC

op7F:   vmovdqu  [var], xmm1
times   pad - ($ - $op7F) db 0xCC

op80:   jo      0x11223344
times   pad - ($ - $op80) db 0xCC

op81:   jno     0x55667788
times   pad - ($ - $op81) db 0xCC

op82:   jb      0x55667788
times   pad - ($ - $op82) db 0xCC

op83:   jnb     0x55667788
times   pad - ($ - $op83) db 0xCC

op84:   jz      0x55776688
times   pad - ($ - $op84) db 0xCC

op85:   jnz     0x55776688
times   pad - ($ - $op85) db 0xCC

op86:   jbe     0x55776688
times   pad - ($ - $op86) db 0xCC

op87:   jnbe    0x55776688
times   pad - ($ - $op87) db 0xCC

op88:   js      0x55776688
times   pad - ($ - $op88) db 0xCC

op89:   jns     0x55776688
times   pad - ($ - $op89) db 0xCC

op8A:   jp      0x55776688
times   pad - ($ - $op8A) db 0xCC

op8B:   jnp     0x55776688
times   pad - ($ - $op8B) db 0xCC

op8C:   jl      0x55772288
times   pad - ($ - $op8C) db 0xCC

op8D:   jnl     0x55772288
times   pad - ($ - $op8D) db 0xCC

op8E:   jle     0x55772233
times   pad - ($ - $op8E) db 0xCC

op8F:   jnle    0x55772233
times   pad - ($ - $op8F) db 0xCC

op90:   seto    al
times   pad - ($ - $op90) db 0xCC

op91:   setno   al
times   pad - ($ - $op91) db 0xCC

op92:   setb    al
times   pad - ($ - $op92) db 0xCC

op93:   setnb   al
times   pad - ($ - $op93) db 0xCC

op94:   setz    al
times   pad - ($ - $op94) db 0xCC

op95:   setnz   al
times   pad - ($ - $op95) db 0xCC

op96:   setbe   al
times   pad - ($ - $op96) db 0xCC

op97:   setnbe  al
times   pad - ($ - $op97) db 0xCC

op98:   sets   [var]
times   pad - ($ - $op98) db 0xCC

op99:   setns   al
times   pad - ($ - $op99) db 0xCC

op9A:   setp    al
times   pad - ($ - $op9A) db 0xCC

op9B:   setnp   al
times   pad - ($ - $op9B) db 0xCC

op9C:   setl    al
times   pad - ($ - $op9C) db 0xCC

op9D:   setnl   al
times   pad - ($ - $op9D) db 0xCC

op9E:   setle   al
times   pad - ($ - $op9E) db 0xCC

op9F:   setnle  al
times   pad - ($ - $op9F) db 0xCC

opA0:   push    fs
times   pad - ($ - $opA0) db 0xCC

opA1:   pop     fs
times   pad - ($ - $opA1) db 0xCC

opA2:   cpuid
times   pad - ($ - $opA2) db 0xCC

opA3:   bt      dword [var], eax
times   pad - ($ - $opA3) db 0xCC

opA4:   shld    [var], eax, 0x77
times   pad - ($ - $opA4) db 0xCC

opA5:   shld    [var], eax, cl
times   pad - ($ - $opA5) db 0xCC

opA6:   ; reserved
times   pad - ($ - $opA6) db 0xCC

opA7:   ; reserved
times   pad - ($ - $opA7) db 0xCC

opA8:   push    gs
times   pad - ($ - $opA8) db 0xCC

opA9:   pop     gs
times   pad - ($ - $opA9) db 0xCC

opAA:   rsm
times   pad - ($ - $opAA) db 0xCC

opAB:   bts     dword [var], ebx
times   pad - ($ - $opAB) db 0xCC

opAC:   shrd    [var], ebx, 0x11
times   pad - ($ - $opAC) db 0xCC

opAD:   shrd    [var], ebx, cl
times   pad - ($ - $opAD) db 0xCC

opAE:   ; not supported in 32bit mode
xsave   [var]
times   pad - ($ - $opAE) db 0xCC

opAF:   imul    eax, [esi + eax*2]
times   pad - ($ - $opAF) db 0xCC

opB0:   cmpxchg byte [var], al
times   pad - ($ - $opB0) db 0xCC

opB1:   cmpxchg [var], eax
times   pad - ($ - $opB1) db 0xCC

opB2:   lss     eax, [var]
times   pad - ($ - $opB2) db 0xCC

opB3:   btr     dword [var], eax
times   pad - ($ - $opB3) db 0xCC

opB4:   lfs     eax, [var]
times   pad - ($ - $opB4) db 0xCC

opB5:   lgs     eax, [var]
times   pad - ($ - $opB5) db 0xCC

opB6:   movzx   eax, bl
times   pad - ($ - $opB6) db 0xCC

opB7:   movzx   eax, word [var]
times   pad - ($ - $opB7) db 0xCC

opB8:   popcnt  eax, [var]
times   pad - ($ - $opB8) db 0xCC

opB9:   dw      0b90fh ; invalid opcode (UD1)
times   pad - ($ - $opB9) db 0xCC

opBA:   btc     dword [var], 0x33
times   pad - ($ - $opBA) db 0xCC

opBB:   btc     [var], eax
times   pad - ($ - $opBB) db 0xCC

opBC:   bsf     eax, [var]
times   pad - ($ - $opBC) db 0xCC

opBD:   bsr     eax, [var]
times   pad - ($ - $opBD) db 0xCC

opBE:   movsx   eax, bl
times   pad - ($ - $opBE) db 0xCC

opBF:   movsx   eax, word [var]
times   pad - ($ - $opBF) db 0xCC

opC0:   xadd    byte [var], dl
times   pad - ($ - $opC0) db 0xCC

opC1:   xadd    dword [var], edx
times   pad - ($ - $opC1) db 0xCC

opC2:   vcmppd   xmm1, [var], 0x88
times   pad - ($ - $opC2) db 0xCC

opC3:   movnti  dword [var], eax
times   pad - ($ - $opC3) db 0xCC

opC4:   vpinsrw  xmm0,xmm2, ax, 0x66
times   pad - ($ - $opC4) db 0xCC

opC5:   vpextrw  eax, xmm0, 0x22
times   pad - ($ - $opC5) db 0xCC

opC6:   vshufps  xmm2, xmm0, [var], 0x44
times   pad - ($ - $opC6) db 0xCC

opC7:   vmclear [var]
times   pad - ($ - $opC7) db 0xCC

opC8:   bswap   eax
times   pad - ($ - $opC8) db 0xCC

opC9:   bswap   ecx
times   pad - ($ - $opC9) db 0xCC

opCA:   bswap   edx
times   pad - ($ - $opCA) db 0xCC

opCB:   bswap   ebx
times   pad - ($ - $opCB) db 0xCC

opCC:   bswap   esp
times   pad - ($ - $opCC) db 0xCC

opCD:   bswap   ebp
times   pad - ($ - $opCD) db 0xCC

opCE:   bswap   esi
times   pad - ($ - $opCE) db 0xCC

opCF:   bswap   edi
times   pad - ($ - $opCF) db 0xCC

opD0:   vaddsubps xmm0, xmm2
times   pad - ($ - $opD0) db 0xCC

opD1:   vpsrlw   xmm4, xmm2
times   pad - ($ - $opD1) db 0xCC

opD2:   vpsrld   xmm4, xmm2, [var]
times   pad - ($ - $opD2) db 0xCC

opD3:   vpsrlq   xmm4, xmm2
times   pad - ($ - $opD3) db 0xCC

opD4:   vpaddq   xmm2, xmm3
times   pad - ($ - $opD4) db 0xCC

opD5:   vpmullw  xmm2, xmm3
times   pad - ($ - $opD5) db 0xCC

opD6:   vmovq    qword [var], xmm1
times   pad - ($ - $opD6) db 0xCC

opD7:   vpmovmskb eax, xmm1
times   pad - ($ - $opD7) db 0xCC

opD8:   vpsubusb xmm2, xmm1
times   pad - ($ - $opD8) db 0xCC

opD9:   vpsubusw xmm0, xmm1
times   pad - ($ - $opD9) db 0xCC

opDA:   vpminub  xmm0, xmm1, xmm4
times   pad - ($ - $opDA) db 0xCC

opDB:   vpand    xmm3, xmm1
times   pad - ($ - $opDB) db 0xCC

opDC:   vpaddusb xmm3, xmm1
times   pad - ($ - $opDC) db 0xCC

opDD:   vpaddusw xmm0, xmm1
times   pad - ($ - $opDD) db 0xCC

opDE:   vpmaxub  xmm0, xmm1
times   pad - ($ - $opDE) db 0xCC

opDF:   vpandn   xmm0, xmm1
times   pad - ($ - $opDF) db 0xCC

opE0:   vpavgb   xmm1, xmm2
times   pad - ($ - $opE0) db 0xCC

opE1:   vpsraw   xmm0, xmm2
times   pad - ($ - $opE1) db 0xCC

opE2:   vpsrad   xmm0, xmm2
times   pad - ($ - $opE2) db 0xCC

opE3:   vpavgw   xmm0, xmm2
times   pad - ($ - $opE3) db 0xCC

opE4:   vpmulhuw xmm0, xmm2
times   pad - ($ - $opE4) db 0xCC

opE5:   vpmulhw  xmm3, xmm4
times   pad - ($ - $opE5) db 0xCC

opE6:   vcvttpd2dq xmm3, xmm4
times   pad - ($ - $opE6) db 0xCC

opE7:   vmovntdq [var], xmm4
times   pad - ($ - $opE7) db 0xCC

opE8:   vpsubsb  xmm2, xmm4
times   pad - ($ - $opE8) db 0xCC

opE9:   vpsubsw  xmm2, xmm4
times   pad - ($ - $opE9) db 0xCC

opEA:   vpminsw  xmm2, xmm4
times   pad - ($ - $opEA) db 0xCC

opEB:   vpor     xmm2, xmm4
times   pad - ($ - $opEB) db 0xCC

opEC:   vpaddsb  xmm2, xmm4
times   pad - ($ - $opEC) db 0xCC

opED:   vpaddsw  xmm2, xmm4
times   pad - ($ - $opED) db 0xCC

opEE:   vpmaxsw  xmm1, xmm0
times   pad - ($ - $opEE) db 0xCC

opEF:   vpxor    xmm1, xmm2
times   pad - ($ - $opEF) db 0xCC

opF0:   vlddqu   xmm1, [var]
times   pad - ($ - $opF0) db 0xCC

opF1:   vpsllw   xmm1, xmm2
times   pad - ($ - $opF1) db 0xCC

opF2:   vpslld   xmm3, xmm4
times   pad - ($ - $opF2) db 0xCC

opF3:   vpsllq   xmm3, xmm4
times   pad - ($ - $opF3) db 0xCC

opF4:   vpmuludq xmm0, xmm1
times   pad - ($ - $opF4) db 0xCC

opF5:   vpmaddwd xmm0, xmm1
times   pad - ($ - $opF5) db 0xCC

opF6:   vpsadbw  xmm1, xmm2
times   pad - ($ - $opF6) db 0xCC

opF7:   vmaskmovdqu xmm1, xmm2
times   pad - ($ - $opF7) db 0xCC

opF8:   vpsubb   xmm1, xmm2
times   pad - ($ - $opF8) db 0xCC

opF9:   vpsubw   xmm1, xmm2
times   pad - ($ - $opF9) db 0xCC

opFA:   vpsubd   xmm1, xmm2
times   pad - ($ - $opFA) db 0xCC

opFB:   vpsubq   xmm1, xmm2
times   pad - ($ - $opFB) db 0xCC

opFC:   vpaddb   xmm1, xmm2
times   pad - ($ - $opFC) db 0xCC

opFD:   vpaddw   xmm1, xmm2
times   pad - ($ - $opFD) db 0xCC

opFE:   vpaddd   xmm1, xmm2,  [var]
times   pad - ($ - $opFE) db 0xCC

opFF:   ; reserved
times   pad - ($ - $opFF) db 0xCC


; Variables
; ---------------------------------
var:
    times pad - ($ - $var) db 0x90