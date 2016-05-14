#ifndef MISSEDMACRO_H
#define MISSEDMACRO_H

#define EF_NOFLAG               0
#define SHF_NOFLAG              0
#define R_X86_64_JUMP_SLOT      7
#define INFO_LINK               0x40
#define ELF64_R_INFO(s,t)       ((((Elf64_Xword)(s))<<32)+(unsigned char)(t))
#define ELF64_ST_INFO(b,t)      (((b)<<4)+((t)&0xf))

typedef struct {
    unsigned char code[0x10];
} Elf64_Plt;

#endif // MISSEDMACRO_H
