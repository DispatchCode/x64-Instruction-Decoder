[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

# x64ID ~ x64 Instruction Decoder

A x86/x64 machine code decoder. It is useful to get instructions' length and identify each of its fields.

Here some scenarios where x64ID can be used:

- write your disassembler from scratch
- as a base for a VM protection [<sup>[1]</sup>](#user-content-res1).
- reverse engineering scenarios
- swapping instructions with others (eg. substitution like `MOV EAX, 0` with `XOR EAX, EAX`)
- get mnemonic rapresentation (*currently not implemented*)
- others (as ideas will come to mind...)

___

- [x64ID ~ x64 Instruction Decoder](#x64id--machine-code-analyzer)
  * [Supported architectures and features](#supported-architectures-and-features)
    + [Features on development](#features-on-development)
  * [API](#api)
    + [Instruction struct](#instruction-struct)
      - [`REX` union](#rex-union)
      - [`ModRm` union](#modrm-union)
      - [`SIB` union](#sib-union)
      - [`vex_info` struct](#vex_info-struct)
  * [Examples](#examples)
      - [A practical example: sum of two vectors using SIMD instruction](#a-practical-example-sum-of-two-vectors-using-simd-instruction)
      - [Another example: architecture x64, VEX prefix with YMM register](#another-example-architecture-x64-vex-prefix-with-ymm-register)
  * [Enabling / Disabling features](#enabling--disabling-features)
  * [Function Length detection](#find-function-length) 🌟*New❗*🌟
  * [Tests](#tests)
  * [Useful resources](#useful-resources)
  * [Notes](#notes)

## Supported architectures and features

**Architectures**:

✅ x86 <br>
✅ x64 <br>

**Opcodes**:

✅ 1-byte OPs <br>
✅ 2-byte OPs <br>
✅ 3-byte OPs, 0x38 and 0x3A <br>

**Fields**:

✅ prefixes <br>
✅ VEX prefix (0xC4, 0xC5) <br>
✅ ModRm <br>
✅ REX prefix <br>
✅ SIB <br>
✅ Imm <br>
✅ Disp <br>
❌ XOP prefix <br>

**Instruction Set**:

✅ x86 & x64 <br>
✅ SIMD extension <br>
✅ AVX extension <br>
❌ AVX-512 (EVEX prefix) <br>
❌ 3DNow! <br/>

### Features on development

🎯 XOP support <br>
🎯 AVX-512 (EVEX prefix) <br>
🎯 Machine code to assembly mnemonics <br>
🎯 Others (as ideas will come to mind...)

## API

x64ID exposes only one function and some structs to complete its goal:

```C
int x64id_decode(struct instruction *instr, enum supported_architecture arch, char *data_src, int offset);
```

| Parameter      | Type     | Explanation | Required |
|----------------|:--------:|-------------|:--------:|
| `instr`        | `struct instruction` | A reference to the struct that will contain the analysis result. See [below](#instruction-struct) for more informations. | YES |
| `arch`         | `enum supported_architecture` | The achitecture type. Use `1` for `x86` and `2` for `x64` | YES |
| `data_source`  | `char*`  | A data buffer with the data to be analyzed | YES |
| `offset`       | `int`    | An offset to be added to the starting address of `data_buffer` | NO |

**Return**:

`x64id_decode` returns the length of the decoded instruction. Its value can also be accessed from `instr.length`.

> :information_source: **Notes**
> Internally, x64ID does not use dynamic allocation to avoid overhead.

___

### Instruction struct

Here below how you can use the struct. More infos and the other structs can be found in the [header file](https://github.com/DispatchCode/Machine-Code-Analyzer/blob/master/src/x64id.h#L355).

| Field Name        | Type              | Description |
|-------------------|:-----------------:|-------------|
| `prefixes`        | `uint8_t[4]`      | Store the prefixes of the instrucion, like Segment Override, Address Size and 2 and 3-byte escape opcodes (0x0f, 0x38, 0x3A)  |
| `rex`             | `union`           | Union of five fields: `value`, `rex_b`, `rex_r`, `rex_x`, `rex_w` (see [below](#rex-union)). |
| `op`              | `uint8_t`         | The opcode of the instruction |
| `modrm`           | `union`           | Union of four fields: `value`, `rm`, `reg` and `mod` (see [below](#modrm-union)). |
| `disp`            | `uint64_t`        | Displacement field |
| `imm`             | `uint64_t`        | Immediate value (a number) |
| `label`           | `uint32_t`        | Address of Jcc/JMP, if present |
| `_vex`            | `struct vex_info` | Available only if [`_ENABLED_VEX_INFO`](#enabling--disabling-features) is defined. Described [below](#vex_info-struct). |
| `instr`           | `uint8_t[15]`     | Available only if [`_ENABLE_RAW_BYTES`](#enabling--disabling-features) is defined. |
| `sib`             | `union`           | Union of four fields: `value`, `base`, `index` and `scaled` (see [below](#sib-union)). |
| `vex`             | `uint8_t[3]`      | 0xC4 or 0xC5 followed by 1 or 2 bytes |
| `length`          | `int`             | The instruction length (in bytes) |
| `disp_len`        | `int`             | The displacement size (in bytes) |
| `imm_len`         | `int`             | The imm size |
| `vex_cnt`         | `int8_t`          | Count how many VEX prefixes are available |
| `prefix_cnt`      | `int8_t`          | Count how many prefixes are available |
| `set_prefix`      | `uint16_t`        | A field against which is possible to check if a determined prefix (belonging to `prefixes` enum) is present. |
| `set_field`       | `uint16_t`        | A field against which is possible to check if a determined feature (belonging to `instruction_feature` enum) is available (e.g. FPU, SIB, DISP,...) |
| `jcc_type`        | `uint8_t`         | The type of jump: Jcc or JMP with 1 or 2-bytes (refer to jmp_type enum) 

___

#### `REX` union

| Field Name        | Type       | Description |
|-------------------|:----------:|-------------|
| `rex.value`       | `uint8_t`  | The `rex` prefix if present (x64 only) |
| `rex.bits.rex_b`  | `uint8_t`  | `rex_b` field |
| `rex.bits.rex_x`  | `uint8_t`  | `rex_x` field |
| `rex.bits.rex_r`  | `uint8_t`  | `rex_r` field |
| `rex.bits.rex_w`  | `uint8_t`  | `rex_w` field |

For more information on REX prefix, refer to section *2.2.1 REX Prefixes* of the Intel Developer Manual Vol.2 [<sup>[2]</sup>](#user-content-res2).

___

#### `ModRm` union

| Field Name        | Type       | Description |
|-------------------|:----------:|-------------|
| `modrm.value`     | `uint8_t`  | The ModRm value |
| `modrm.bits.rm`   | `uint8_t`  | The `rm` part of ModRm  |
| `modrm.bits.reg`  | `uint8_t`  | The `reg` part of ModRm |
| `modrm.bits.mod`  | `uint8_t`  | The `mod` part of ModRm. When mod=11b source and destination are registers, otherwise one of the operands involves memory access (displacement field) |

More information on ModRm field can be found at the section *2.1.3 ModR/M and SIB Bytes* of the Intel Developer Manual Vol.2 [<sup>[2]</sup>](#user-content-res2).

___

#### `SIB` union

| Field Name        | Type       | Description |
|-------------------|:----------:|-------------|
| `sib.value`       | `uint8_t`  | If present, is the Scaled Index Base |
| `sib.bits.base`   | `uint8_t`  | `base` field |
| `sib.bits.index`  | `uint8_t`  | `index` field |
| `sib.bits.scaled` | `uint8_t`  | `scaled` field |

For more information refer to section *2.1.5 Addressing-Mode Encoding of ModR/M and SIB Bytes* of the Intel Developer Manual Vol.2 [<sup>[2]</sup>](#user-content-res2).

___

#### `vex_info` struct

| Field Name           | Type              | Description |
|----------------------|:-----------------:|-------------|
| `type`               | `uint8_t`         | `0xC4` used when 3-byte prefix is present or `0xC5` used when 2-byte prefix is present |
| `vexc5b`             | `struct`          |  |
| `_vex.val5`          | `uint8_t`         | The byte after `0xC5` with its filds described below |
| `_vex.vexc5b.vex_pp` | `uint8_t`         | Equivalent to a SIMD prefix: `00`: none, `01`: 0x66, `02`: 0xF3, `03`: 0xF2 |
| `_vex.vexc5b.vex_l`  | `uint8_t`         | 0 for 128-bit vector or 1 for 256-bit vector |
| `_vex.vexc5b.vex_v`  | `uint8_t`         | An additional operand for the instruction |
| `_vex.vexc5b.vex_r`  | `uint8_t`         |  |
| `_vex.val4`          | `uint16_t`        |  |
| `_vex.vexc4b.vex_pp` | `uint8_t`         |  |
| `_vex.vexc4b.vex_l`  | `uint8_t`         |  |
| `_vex.vexc4b.vex_v`  | `uint8_t`         |  |
| `_vex.vexc4b.vex_r`  | `uint8_t`         |  |
| `_vex.vexc4b.vex_m`  | `uint8_t`         | Values: 00001: implied 0F leading opcode byte, 00010: implied 0F 38 leading opcode bytes, 00011: implied 0F 3A leading opcode bytes. Other values will #UD. |
| `_vex.vexc4b.vex_b`  | `uint8_t`         |  |
| `_vex.vexc4b.vex_x`  | `uint8_t`         |  |
| `_vex.vexc4b.vex_r`  | `uint8_t`         |  |

For all the details about VEX prefix look at section **2.3.5 The VEX Prefix** of the Intel Developer Manual Vol.2 [<sup>[2]</sup>](#user-content-res2).
___

## Examples

#### A practical example: sum of two vectors using SIMD instruction

Lets have a pratical example, the sum of two vectors (using inline assembly):

```C
  // ... omitted code ...
  int vect1[LEN] = {1,2,3,4,5,6,7,8,9,10,11,12};
  int vect2[LEN] = {1,2,3,4,5,6,7,8,9,10,11,12};
  int res_vect1[LEN];

  __asm
  {
    lea      eax, vect1
    lea      ebx, vect2
    xor      ecx, ecx

    _while:
    cmp      ecx, LEN * 4
    jge      _end

      movups   xmm0, [eax + ecx]
      movups   xmm1, [ebx + ecx]
      addps    xmm0, xmm1
      movups   [res_vect1 + ecx], xmm0
      add      ecx, 4
      jmp      _while

    _end:  
  }
  // ... omitted code ...
```

Compiling through MS Compiler (with `/Ot` flag), the result will be what follows:

```Assembly
CPU Disasm
Address   Hex dump                    Command                                  Comments
008910BC  |.  C785 68FFFFFF 00000000  MOV DWORD PTR SS:[LOCAL.38],0
008910C6  |.  8D45 CC                 LEA EAX,[LOCAL.13]
008910C9  |.  8D5D 9C                 LEA EBX,[LOCAL.25]
008910CC  |.  33C9                    XOR ECX,ECX
008910CE  |>  83F9 30                 /CMP ECX,30
008910D1  |.  7D 18                   |JGE SHORT 008910EB
008910D3  |.  0F100408                |MOVUPS XMM0,DQWORD PTR DS:[ECX+EAX]
008910D7  |.  0F100C0B                |MOVUPS XMM1,DQWORD PTR DS:[ECX+EBX]
008910DB  |.  0F58C1                  |ADDPS XMM0,XMM1
008910DE  |.  0F11840D 6CFFFFFF       |MOVUPS DQWORD PTR SS:[ECX+EBP-94],XMM0
008910E6  |.  83C1 04                 |ADD ECX,4
008910E9  |.^ EB E3                   \JMP SHORT 008910CE

```

We can write a sample code that uses x64ID to read and print the instructions.

```C
int offset = 0x4bc;
int parse_bytes = 0x2a;
int byte_reads = 0;

while(byte_reads <= parse_bytes) {
    struct instruction instr;
    x64id_decode(&instr, arch, (char*)data_buffer, offset);
    
    for(int i=0; i<instr.length; i++)
        printf("%02X ", instr.instr[i]);
        
    printf("\n");
    offset += instr.length;
    byte_reads += instr.length;
}
```

This is what gets printed in output by giving to it the "sum of two vectors" code above (each line is an instruction):

```
C7 85 68 FF FF FF 00 00 00 00
8D 45 CC
8D 5D 9C
33 C9
83 F9 30
7D 18
0F 10 04 08
0F 10 0C 0B
0F 58 C1
0F 11 84 0D 6C FF FF FF
83 C1 04
```

Of course you can gather more information about each instruction.
Here below a sample detailed report created by x64ID processing of two of the instructions of the set above, inst. 1 and inst. 10:

```
/**
 * Ref only - Instruction Line 1:
 * MOV DWORD PTR SS:[LOCAL.38],0
 */

RAW bytes (hex): C7 85 68 FF FF FF 00 00 00 00
Instr. length: 10
Print instruction fields:
        Located Prefixes 0:

        OP: 0xC7
        mod_reg_rm: 0x85
        disp (4): 0xFFFFFF68
        Iimm: 0x0


/**
 * Ref only - Instruction Line 10:
 * MOVUPS DQWORD PTR SS:[ECX+EBP-94],XMM0
 */

RAW bytes (hex): 0F 11 84 0D 6C FF FF FF
Instr. length: 8
Print instruction fields:
        Located Prefixes 1:
                0xF
        OP: 0x11
        mod_reg_rm: 0x84
        SIB byte: 0xD
        disp (4): 0xFFFFFF6C
```

___

#### Another example: architecture x64, VEX prefix with YMM register

`vmovsldup  ymm1, [rbp*4 + var]`

As compiled output we'll get:

`C5 FE 12 0C AD 00 10 00 00`

Output after x64ID parsing:

```
RAW bytes (hex): C5 FE 12 0C AD 00 10 00 00
Instr. length: 9
Print instruction fields:
        Located Prefixes 0:

        VEX prefix value:
                0xC5 0xFE
        Field 0xFE:
                r: 1
                v: F
                L: 1
                pp: 2

        OP: 0x12
        mod_reg_rm: 0xC
        SIB byte: 0xAD
        disp (4): 0x1000
```

## Enabling / Disabling features

Some features can be toggled by adding / removing comments on these lines:

```C
#define  _ENABLE_RAW_BYTES
#define  _ENABLE_VEX_INFO
```

| Define              | Description |
|:-------------------:|:------------|
| `_ENABLE_RAW_BYTES` | Enabling this, allows storing each instruction into the `instr` struct passed to `x64id_decode` (`instr.instr`); |
| `_ENABLE_VEX_INFO`  | Enabling this, allows storing VEX infos into `instr`; see previous example for more |

## Find length of a function
An extension has been added to compute the length of a specified function:
```C
pFunctionInfo getFunctionLength(char *buffer, enum supported_architecture arch);
```
`pFunctionInfo` is an anonymous struct defined as follows:

| Field Name        | Type       | Description |
|-------------------|:----------:|-------------|
| `pVisited`     | `vector *`  | A pointer to a `vector` data structure |
| `length`   | `int`  | The length of the function in bytes  |

The `vector` data structure is a dynamic array with three members:

| Field Name        | Type       | Description |
|-------------------|:----------:|-------------|
| `vect`     | `uint32_t *`  | contains the detected addresses  |
| `size`   | `int`  | allocated memory of the array |
| `tos`   | `int`  | index of the last inserted element |

An example can be found in `main.c`, function `in_memory()`.

> :information_source: **Notes**
> Jump Table are not handled; be careful when you use switch case and compiling with MSVC (GCC/MinGw seems use other techniques).
> Handling jmp table require heuristics (eg. as IDA do and other tools) and more info on the target.
## Tests

After googling for a better solution, I came back with one of the first things I was thinking: assembly.

Tests have been written using NASM and must be compiled using the "bin" flag:

```sh
nasm -f bin <filename.asm>
```

The tested instructions are the following:

* x86: `1-byte OP`, `2-byte OP`, `3-byte OP` and `2-byte OP with VEX prefix`
* x64: `1-byte OP`, `2-byte OP`, `3-byte OP`; some of which have `VEX prefix`

Tests have been written by hand using the Intel Developer Manual book [<sup>[2]</sup>](#user-content-res2).
I can't guarantee a 100% coverage, however all the opcodes have been tested.

## Useful resources

- [X86-64 Instruction Encoding](https://wiki.osdev.org/X86-64_Instruction_Encoding)
- [x86_64 Instruction Table](https://c9x.me/x86/)
- [Compiler Explorer](https://godbolt.org/)

## Notes

<sup id="res1">[1]</sup> By VM protection is meant a code obscator that converts x86/x64 machine code into "virtual opcodes" that are understandable by a VM. Two commercial examples can be [VMProtect](https://vmpsoft.com/) and [CodeVirtualizer](https://www.oreans.com/codevirtualizer.php)

<sup id="res2">[2]</sup> [Intel Developer Manual (2nd book)](https://software.intel.com/content/dam/develop/public/us/en/documents/334569-sdm-vol-2d.pdf)

___

_Crafted with ❤ by DispatchCode. Documentation created along with [Alexander Cerutti](https://github.com/alexandercerutti)_
