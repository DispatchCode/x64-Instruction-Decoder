; ------------------------------------------
; VOL. 2D, Appendix A, pg. 7-8 (Intel Manual)
; ------------------------------------------

[BITS 32]

; Macros
pad     equ   16

; -------------------------------
; 1-byte opcodes tests
; -------------------------------

;
; 00h - 0Fh
;
op00:   add     al, bl
times   pad - ($ - $op00) db 0xCC

op01:   add     [var], ebx
times   pad - ($ - $op01) db 0xCC

op02:   add     al, byte [var]
times   pad - ($ - $op02) db 0xCC

op03:   add     edx, [var]
times   pad - ($ - $op03) db 0xCC

op04:   add     al, 123
times   pad - ($ - $op04) db 0xCC

op05:   add     eax, 0x11223344
times   pad - ($ - $op05) db 0xCC

op06:   push    es
times   pad - ($ - $op06) db 0xCC

op07:   pop     es
times   pad - ($ - $op07) db 0xCC

op08:   or      al, bl
times   pad - ($ - $op08) db 0xCC

op09:   or      [var], ebx
times   pad - ($ - $op09) db 0xCC

op0A:   or      al, byte [var]
times   pad - ($ - $op0A) db 0xCC

op0B:   or      edx, [var]
times   pad - ($ - $op0B) db 0xCC

op0C:   or      al, 123
times   pad - ($ - $op0C) db 0xCC

op0D:   or      eax, 0x11223344
times   pad - ($ - $op0D) db 0xCC

op0E:   push    cs
times   pad - ($ - $op0E) db 0xCC

op0F:   db      0x0F ; ESCape, 2-byte OP
times   pad - ($ - $op0F) db 0xCC

op10:   adc     dh, cl
times   pad - ($ - $op10) db 0xCC

op11:   adc     [var], ecx
times   pad - ($ - $op11) db 0xCC

op12:   adc     ah, byte [var]
times   pad - ($ - $op12) db 0xCC

op13:   adc     eax, [var]
times   pad - ($ - $op13) db 0xCC

op14:   adc     al, 123
times   pad - ($ - $op14) db 0xCC

op15:   adc     eax, 0x11223344
times   pad - ($ - $op15) db 0xCC

op16:   push    ss
times   pad - ($ - $op16) db 0xCC

op17:   pop     ss
times   pad - ($ - $op17) db 0xCC

op18:   sbb     al, bl
times   pad - ($ - $op18) db 0xCC

op19:   sbb     [var], ebx
times   pad - ($ - $op19) db 0xCC

op1A:   sbb     al, byte [var]
times   pad - ($ - $op1A) db 0xCC

op1B:   sbb     edx, [var]
times   pad - ($ - $op1B) db 0xCC

op1C:   sbb     al, 123
times   pad - ($ - $op1C) db 0xCC

op1D:   sbb     eax, 0x11223344
times   pad - ($ - $op1D) db 0xCC

op1E:   push    ds
times   pad - ($ - $op1E) db 0xCC

op1F:   pop     ds
times   pad - ($ - $op1F) db 0xCC

op20:   and     al, bl
times   pad - ($ - $op20) db 0xCC

op21:   and     [var], ebx
times   pad - ($ - $op21) db 0xCC

op22:   and     al, byte [var]
times   pad - ($ - $op22) db 0xCC

op23:   and     edx, [var]
times   pad - ($ - $op23) db 0xCC

op24:   and     al, 123
times   pad - ($ - $op24) db 0xCC

op25:   and     eax, 0x11223344
times   pad - ($ - $op25) db 0xCC

op26:   db      0x26 ; ES prefix
times   pad - ($ - $op26) db 0xCC

op27:   daa
times   pad - ($ - $op27) db 0xCC

op28:   sub     al, bl
times   pad - ($ - $op28) db 0xCC

op29:   sub     [var], ebx
times   pad - ($ - $op29) db 0xCC

op2A:   sub     al, byte [var]
times   pad - ($ - $op2A) db 0xCC

op2B:   sub     edx, [var]
times   pad - ($ - $op2B) db 0xCC

op2C:   sub     al, 123
times   pad - ($ - $op2C) db 0xCC

op2D:   sub     eax, 0x11223344
times   pad - ($ - $op2D) db 0xCC

op2E:   db      0x2E ; CS Prefix
times   pad - ($ - $op2E) db 0xCC

op2F:   das
times   pad - ($ - $op2F) db 0xCC

op30:   xor     al, bl
times   pad - ($ - $op30) db 0xCC

op31:   xor     [var], ebx
times   pad - ($ - $op31) db 0xCC

op32:   xor     al, byte [var]
times   pad - ($ - $op32) db 0xCC

op33:   xor     edx, [var]
times   pad - ($ - $op33) db 0xCC

op34:   xor     al, 123
times   pad - ($ - $op34) db 0xCC

op35:   xor     eax, 0x11223344
times   pad - ($ - $op35) db 0xCC

op36:   db      0x36 ; SS Prefix
times   pad - ($ - $op36) db 0xCC

op37:   aaa
times   pad - ($ - $op37) db 0xCC

op38:   cmp     al, bl
times   pad - ($ - $op38) db 0xCC

op39:   cmp     [var], ebx
times   pad - ($ - $op39) db 0xCC

op3A:   cmp     al, byte [var]
times   pad - ($ - $op3A) db 0xCC

op3B:   cmp     edx, [var]
times   pad - ($ - $op3B) db 0xCC

op3C:   cmp     al, 123
times   pad - ($ - $op3C) db 0xCC

op3D:   cmp     eax, 0x11223344
times   pad - ($ - $op3D) db 0xCC

op3E:   db      0x3E ; DS Prefix
times   pad - ($ - $op3E) db 0xCC

op3F:   aas
times   pad - ($ - $op3F) db 0xCC

op40:   inc     ax
times   pad - ($ - $op40) db 0xCC

op41:   inc     ecx
times   pad - ($ - $op41) db 0xCC

op42:   inc     dx
times   pad - ($ - $op42) db 0xCC

op43:   inc     ebx
times   pad - ($ - $op43) db 0xCC

op44:   inc     sp
times   pad - ($ - $op44) db 0xCC

op45:   inc     ebp
times   pad - ($ - $op45) db 0xCC

op46:   inc     si
times   pad - ($ - $op46) db 0xCC

op47:   inc     edi
times   pad - ($ - $op47) db 0xCC

op48:   dec     ax
times   pad - ($ - $op48) db 0xCC

op49:   dec     ecx
times   pad - ($ - $op49) db 0xCC

op4A:   dec     dx
times   pad - ($ - $op4A) db 0xCC

op4B:   dec     ebx
times   pad - ($ - $op4B) db 0xCC

op4C:   dec     sp
times   pad - ($ - $op4C) db 0xCC

op4D:   dec     ebp
times   pad - ($ - $op4D) db 0xCC

op4E:   dec     si
times   pad - ($ - $op4E) db 0xCC

op4F:   dec     edi
times   pad - ($ - $op4F) db 0xCC

op50:   push    ax
times   pad - ($ - $op50) db 0xCC

op51:   push    ecx
times   pad - ($ - $op51) db 0xCC

op52:   push    dx
times   pad - ($ - $op52) db 0xCC

op53:   push    ebx
times   pad - ($ - $op53) db 0xCC

op54:   push    sp
times   pad - ($ - $op54) db 0xCC

op55:   push    ebp
times   pad - ($ - $op55) db 0xCC

op56:   push    si
times   pad - ($ - $op56) db 0xCC

op57:   push    edi
times   pad - ($ - $op57) db 0xCC

op58:   pop     ax
times   pad - ($ - $op58) db 0xCC

op59:   pop     ecx
times   pad - ($ - $op59) db 0xCC

op5A:   pop     dx
times   pad - ($ - $op5A) db 0xCC

op5B:   pop     ebx
times   pad - ($ - $op5B) db 0xCC

op5C:   pop     sp
times   pad - ($ - $op5C) db 0xCC

op5D:   pop     ebp
times   pad - ($ - $op5D) db 0xCC

op5E:   pop     si
times   pad - ($ - $op5E) db 0xCC

op5F:   pop     edi
times   pad - ($ - $op5F) db 0xCC

op60:   pusha
times   pad - ($ - $op60) db 0xCC

op61:   popa
times   pad - ($ - $op61) db 0xCC

op62:   bound   eax, [var]
times   pad - ($ - $op62) db 0xCC

op63:   arpl    cx, dx
times   pad - ($ - $op63) db 0xCC

op64:   db      0x64 ; FS segment
times   pad - ($ - $op64) db 0xCC

op65:   db      0x65 ; GS segment
times   pad - ($ - $op65) db 0xCC

op66:   db      0x66 ; Operand Size prefix
times   pad - ($ - $op66) db 0xCC

op67:   db      0x67 ; Address Size prefix
times   pad - ($ - $op67) db 0xCC

op68:   push    var
times   pad - ($ - $op68) db 0xCC

op69:   imul    eax, [var], 0x112233
times   pad - ($ - $op69) db 0xCC

op6A:   push    1
times   pad - ($ - $op6A) db 0xCC

op6B:   imul    ax, 0x11
times   pad - ($ - $op6B) db 0xCC

op6C:   insb
times   pad - ($ - $op6C) db 0xCC

op6D:   insd
times   pad - ($ - $op6D) db 0xCC

op6E:   outsb
times   pad - ($ - $op6E) db 0xCC

op6F:   outsd
times   pad - ($ - $op6F) db 0xCC

op70:   jo      op6F
times   pad - ($ - $op70) db 0xCC

op71:   jno     op70
times   pad - ($ - $op71) db 0xCC

op72:   jb      op71
times   pad - ($ - $op72) db 0xCC

op73:   jnb     op72
times   pad - ($ - $op73) db 0xCC

op74:   je      op73
times   pad - ($ - $op74) db 0xCC

op75:   jne     op74
times   pad - ($ - $op75) db 0xCC

op76:   jbe     op75
times   pad - ($ - $op76) db 0xCC

op77:   jnbe    op76
times   pad - ($ - $op77) db 0xCC

op78:   js      op77
times   pad - ($ - $op78) db 0xCC

op79:   jns     op78
times   pad - ($ - $op79) db 0xCC

op7A:   jp      op79
times   pad - ($ - $op7A) db 0xCC

op7B:   jnp     op7A
times   pad - ($ - $op7B) db 0xCC

op7C:   jl      op7B
times   pad - ($ - $op7C) db 0xCC

op7D:   jnl     op7C
times   pad - ($ - $op7D) db 0xCC

op7E:   jle     op7D
times   pad - ($ - $op7E) db 0xCC

op7F:   jnle    op7E
times   pad - ($ - $op7F) db 0xCC

op80:   add     byte [var], 1
times   pad - ($ - $op80) db 0xCC

op81:   add     dword [var], 0x11223344
times   pad - ($ - $op81) db 0xCC

op82:   ; TODO  alias (?) of 0x80
times   pad - ($ - $op82) db 0xCC

op83:   add     dword [var], 0x11
times   pad - ($ - $op83) db 0xCC

op84:   test    bl, cl
times   pad - ($ - $op84) db 0xCC

op85:   test    eax, edx
times   pad - ($ - $op85) db 0xCC

op86:   xchg    al, cl
times   pad - ($ - $op86) db 0xCC

op87:   xchg    [var], ecx
times   pad - ($ - $op87) db 0xCC

op88:   mov     bl, cl
times   pad - ($ - $op88) db 0xCC

op89:   mov     ebx, edx
times   pad - ($ - $op89) db 0xCC

op8A:   mov     ah, [var]
times   pad - ($ - $op8A) db 0xCC

op8B:   mov     ebx, [var]
times   pad - ($ - $op8B) db 0xCC

op8C:   mov     [var], es
times   pad - ($ - $op8C) db 0xCC

op8D:   lea     ebx, [eax]
times   pad - ($ - $op8D) db 0xCC

op8E:   mov     es, word [var]
times   pad - ($ - $op8E) db 0xCC

op8F:   pop     dword [var]
times   pad - ($ - $op8F) db 0xCC

op90:   nop
times   pad - ($ - $op90) db 0xCC

op91:   xchg    cx, ax
times   pad - ($ - $op91) db 0xCC

op92:   xchg    edx, eax
times   pad - ($ - $op92) db 0xCC

op93:   xchg    ebx, eax
times   pad - ($ - $op93) db 0xCC

op94:   xchg    esp, eax
times   pad - ($ - $op94) db 0xCC

op95:   xchg    ebp, eax
times   pad - ($ - $op95) db 0xCC

op96:   xchg    esi, eax
times   pad - ($ - $op96) db 0xCC

op97:   xchg    edi, eax
times   pad - ($ - $op97) db 0xCC

op98:   cwde
times   pad - ($ - $op98) db 0xCC

op99:   cdq
times   pad - ($ - $op99) db 0xCC

op9A:   call    0x1122:0x1122
times   pad - ($ - $op9A) db 0xCC

op9B:   fwait
times   pad - ($ - $op9B) db 0xCC

op9C:   pushf
times   pad - ($ - $op9C) db 0xCC

op9D:   popf
times   pad - ($ - $op9D) db 0xCC

op9E:   sahf
times   pad - ($ - $op9E) db 0xCC

op9F:   lahf
times   pad - ($ - $op9F) db 0xCC

opA0:   mov     al, byte [var]
times   pad - ($ - $opA0) db 0xCC

opA1:   mov     ax, [var]
times   pad - ($ - $opA1) db 0xCC

opA2:   mov     byte [var], al
times   pad - ($ - $opA2) db 0xCC

opA3:   mov     dword [var], eax
times   pad - ($ - $opA3) db 0xCC

opA4:   movsb
times   pad - ($ - $opA4) db 0xCC

opA5:   movsd
times   pad - ($ - $opA5) db 0xCC

opA6:   cmpsb
times   pad - ($ - $opA6) db 0xCC

opA7:   cmpsd
times   pad - ($ - $opA7) db 0xCC

opA8:   test    al, 0x11
times   pad - ($ - $opA8) db 0xCC

opA9:   test    eax, 0x11223344
times   pad - ($ - $opA9) db 0xCC

opAA:   stosb
times   pad - ($ - $opAA) db 0xCC

opAB:   stosd
times   pad - ($ - $opAB) db 0xCC

opAC:   lodsb
times   pad - ($ - $opAC) db 0xCC

opAD:   lodsd
times   pad - ($ - $opAD) db 0xCC

opAE:   scasb
times   pad - ($ - $opAE) db 0xCC

opAF:   scasd
times   pad - ($ - $opAF) db 0xCC

opB0:   mov     al, 0x11
times   pad - ($ - $opB0) db 0xCC

opB1:   mov     cl, 0x11
times   pad - ($ - $opB1) db 0xCC

opB2:   mov     dl, 0x11
times   pad - ($ - $opB2) db 0xCC

opB3:   mov     bl, 0x11
times   pad - ($ - $opB3) db 0xCC

opB4:   mov     ah, 0x11
times   pad - ($ - $opB4) db 0xCC

opB5:   mov     ch, 0x11
times   pad - ($ - $opB5) db 0xCC

opB6:   mov     dh, 0x11
times   pad - ($ - $opB6) db 0xCC

opB7:   mov     bh, 0x11
times   pad - ($ - $opB7) db 0xCC

opB8:   mov     eax, 0x1122
times   pad - ($ - $opB8) db 0xCC

opB9:   mov     ecx, 0x1122
times   pad - ($ - $opB9) db 0xCC

opBA:   mov     edx, 0x1122
times   pad - ($ - $opBA) db 0xCC

opBB:   mov     ebx, 0x1122
times   pad - ($ - $opBB) db 0xCC

opBC:   mov     esp, 0x1122
times   pad - ($ - $opBC) db 0xCC

opBD:   mov     ebp, 0x1122
times   pad - ($ - $opBD) db 0xCC

opBE:   mov     esi, 0x1122
times   pad - ($ - $opBE) db 0xCC

opBF:   mov     edi, 0x1122
times   pad - ($ - $opBF) db 0xCC

opC0:   ror     al, 0x11
times   pad - ($ - $opC0) db 0xCC

opC1:   ror     eax, 0x11
times   pad - ($ - $opC1) db 0xCC

opC2:   ret     0x11
times   pad - ($ - $opC2) db 0xCC

opC3:   ret
times   pad - ($ - $opC3) db 0xCC

opC4:   les     eax, [var]
times   pad - ($ - $opC4) db 0xCC

opC5:   lds     eax, [var]
times   pad - ($ - $opC5) db 0xCC

opC6:   mov     byte [var], 0x11
times   pad - ($ - $opC6) db 0xCC

opC7:   mov     dword [var], 0x11223344
times   pad - ($ - $opC7) db 0xCC

opC8:   enter   0x1122, 0x11
times   pad - ($ - $opC8) db 0xCC

opC9:   leave
times   pad - ($ - $opC9) db 0xCC

opCA:   retf    0x11
times   pad - ($ - $opCA) db 0xCC

opCB:   retf
times   pad - ($ - $opCB) db 0xCC

opCC:   int3
times   pad - ($ - $opCC) db 0xCC

opCD:   int     0x21
times   pad - ($ - $opCD) db 0xCC

opCE:   into
times   pad - ($ - $opCE) db 0xCC

opCF:   iretd
times   pad - ($ - $opCF) db 0xCC

opD0:   ror     byte [var], 1
times   pad - ($ - $opD0) db 0xCC

opD1:   ror     dword [var], 1
times   pad - ($ - $opD1) db 0xCC

opD2:   ror     byte [var], cl
times   pad - ($ - $opD2) db 0xCC

opD3:   ror     dword [var], cl
times   pad - ($ - $opD3) db 0xCC

opD4:   aam     0x11
times   pad - ($ - $opD4) db 0xCC

opD5:   aad     0x11
times   pad - ($ - $opD5) db 0xCC

opD6:   db      0xD6 ; reserved opcode
times   pad - ($ - $opD6) db 0xCC

opD7:   xlatb
times   pad - ($ - $opD7) db 0xCC

; Coprocessor (0xD8 - 0xDF)
opD8:   fadd    dword [var]
times   pad - ($ - $opD8) db 0xCC

opD9:   fld     dword [var]
times   pad - ($ - $opD9) db 0xCC

opDA:   fiadd   dword [var]
times   pad - ($ - $opDA) db 0xCC

opDB:   fild    dword [var]
times   pad - ($ - $opDB) db 0xCC

opDC:   fadd    qword [var]
times   pad - ($ - $opDC) db 0xCC

opDD:   fld     qword [var]
times   pad - ($ - $opDD) db 0xCC

opDE:   fiadd   word [var]
times   pad - ($ - $opDE) db 0xCC

opDF:   fild    word [var]
times   pad - ($ - $opDF) db 0xCC

opE0:   loopne  0x22
times   pad - ($ - $opE0) db 0xCC

opE1:   loope   0x22
times   pad - ($ - $opE1) db 0xCC

opE2:   loop    0x22
times   pad - ($ - $opE2) db 0xCC

opE3:   jecxz   0x22
times   pad - ($ - $opE3) db 0xCC

opE4:   in      al, 0x11
times   pad - ($ - $opE4) db 0xCC

opE5:   in      eax, 0x11
times   pad - ($ - $opE5) db 0xCC

opE6:   out     0x11, al
times   pad - ($ - $opE6) db 0xCC

opE7:   out     0x11, eax
times   pad - ($ - $opE7) db 0xCC

opE8:   call    0x11
times   pad - ($ - $opE8) db 0xCC

opE9:   jmp     0x11
times   pad - ($ - $opE9) db 0xCC

opEA:   jmp     0x11:var
times   pad - ($ - $opEA) db 0xCC

opEB:   jmp     var
times   pad - ($ - $opEB) db 0xCC

opEC:   in      al, dx
times   pad - ($ - $opEC) db 0xCC

opED:   in      eax, dx
times   pad - ($ - $opED) db 0xCC

opEE:   out     dx, al
times   pad - ($ - $opEE) db 0xCC

opEF:   out     dx, eax
times   pad - ($ - $opEF) db 0xCC

opF0:   db      0xF0 ; lock prefix; direct use of lock throw a compiler warning
times   pad - ($ - $opF0) db 0xCC

opF1:   int1
times   pad - ($ - $opF1) db 0xCC

opF2:   db      0xF2 ; repne prefix
times   pad - ($ - $opF2) db 0xCC

opF3:   db      0xF3 ; rep prefix
times   pad - ($ - $opF3) db 0xCC

opF4:   hlt
times   pad - ($ - $opF4) db 0xCC

opF5:   cmc
times   pad - ($ - $opF5) db 0xCC

opF6:   not     byte [var]
times   pad - ($ - $opF6) db 0xCC

opF7:   not     dword [var]
times   pad - ($ - $opF7) db 0xCC

opF8:   clc
times   pad - ($ - $opF8) db 0xCC

opF9:   stc
times   pad - ($ - $opF9) db 0xCC

opFA:   cli
times   pad - ($ - $opFA) db 0xCC

opFB:   sti
times   pad - ($ - $opFB) db 0xCC

opFC:   cld
times   pad - ($ - $opFC) db 0xCC

opFD:   std
times   pad - ($ - $opFD) db 0xCC

opFE:   inc     al
times   pad - ($ - $opFE) db 0xCC

opFF:   dec     dword [var]
times   pad - ($ - $opFF) db 0xCC


; Variables
; ---------------------------------
var:
    times pad - ($ - $var) db 0x90