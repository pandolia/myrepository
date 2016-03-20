#include <stdio.h>
#include <string.h>
#include <linux/elf.h>
#include "missedmacro.h"

/* Elf File Layout */
struct Elf_File {
/* 0000h->+------+--------------------------------+<-0x400000 */
/*        | 040h | Elf file header                | */ Elf64_Ehdr    header;
/* 0040h->+------+--------------------------------+ */
/*        | 038h | Program header  0 (PT_PHDR)    | */ Elf64_Phdr    phdr_PHDR;
/* 0078h->+------+--------------------------------+ */
/*        | 038h | Program header  1 (PT_INTERP)  | */ Elf64_Phdr    phdr_INTERP;
/* 00b0h->+------+--------------------------------+ */
/*        | 038h | Program header  2 (PT_LOAD RE) | */ Elf64_Phdr    phdr_LOAD_RE;
/* 00e8h->+------+--------------------------------+ */
/*        | 038h | Program header  3 (PT_LOAD RW) | */ Elf64_Phdr    phdr_LOAD_RW;
/* 0120h->+------+--------------------------------+ */
/*        | 038h | Program header  4 (PT_DYNAMIC) | */ Elf64_Phdr    phdr_DYNAMIC;
/* 0158h->+------+--------------------------------+ */
/*        | 0a8h | Padding                        | */ unsigned char padding[0x0a8];
/* 0200h->+------+--------------------------------+<-0x400200 */
/*        | 080h | Section body  1 (.interp)      | */ unsigned char sect_interp[0x080];
/* 0280h->+------+--------------------------------+<-0x400280 */
/*        | 020h | Section body  2 (.hash)    | */ unsigned char sect_hash[0x020];
/* 02a0h->+------+--------------------------------+<-0x4002a0 */
/*        | 030h | Section body  3 (.dynsym)      | */ Elf64_Sym     sect_dynsym[2];
/* 02d0h->+------+--------------------------------+<-0x4002d0 */
/*        | 020h | Section body  4 (.dynstr)      | */ unsigned char sect_dynstr[0x020];
/* 02f0h->+------+--------------------------------+<-0x4002f0 */
/*        | 018h | Section body  5 (.rela.plt)    | */ Elf64_Rela    sect_relaplt[1];
/* 0308h->+------+--------------------------------+<-0x400308 */
/*        | 020h | Section body  6 (.plt)         | */ Elf64_Plt     sect_plt[2];
/* 0328h->+------+--------------------------------+<-0x400328 */
/*        | 060h | Section body  7 (.text)        | */ unsigned char sect_text[0x060];
/* 0388h->+------+--------------------------------+<-0x400388 */
/*        | 018h | Section body  8 (.rodata)      | */ unsigned char sect_rodata[0x018];
/* 03a0h->+------+--------------------------------+<-0x6003a0 */
/*        | 100h | Section body  9 (.dynamic)     | */ Elf64_Dyn     sect_dynamic[16];
/* 04a0h->+------+--------------------------------+<-0x6004a0 */
/*        | 040h | Section body 10 (.got.plt)     | */ Elf64_Addr	 sect_gotplt[8];
/* 04e0h->+------+--------------------------------+ */
/*        | 100h | Section body 11 (.shstrtab)    | */ unsigned char sect_shstrtab[0x100];
/* 05e0h->+------+--------------------------------+ */
/*        | 030h | Section body 12 (.symtab)      | */ Elf64_Sym     sect_symtab[2];
/* 0610h->+------+--------------------------------+ */
/*        | 020h | Section body 13 (.strtab)      | */ unsigned char sect_strtab[0x20];
/* 0630h->+------+--------------------------------+ */
/*        | 040h | Section header  0 (null)       | */ Elf64_Shdr    shdr_null;
/* 0670h->+------+--------------------------------+ */
/*        | 040h | Section header  1 (.interp)    | */ Elf64_Shdr    shdr_interp;
/* 06b0h->+------+--------------------------------+ */
/*        | 040h | Section header  2 (.hash)      | */ Elf64_Shdr    shdr_hash;
/* 06f0h->+------+--------------------------------+ */
/*        | 040h | Section header  3 (.dynsym)    | */ Elf64_Shdr    shdr_dynsym;
/* 0730h->+------+--------------------------------+ */
/*        | 040h | Section header  4 (.dynstr)    | */ Elf64_Shdr    shdr_dynstr;
/* 0770h->+------+--------------------------------+ */
/*        | 040h | Section header  5 (.rela.plt)  | */ Elf64_Shdr    shdr_relaplt;
/* 07b0h->+------+--------------------------------+ */
/*        | 040h | Section header  6 (.plt)       | */ Elf64_Shdr    shdr_plt;
/* 07f0h->+------+--------------------------------+ */
/*        | 040h | Section header  7 (.text)      | */ Elf64_Shdr    shdr_text;
/* 0830h->+------+--------------------------------+ */
/*        | 040h | Section header  8 (.rodata)    | */ Elf64_Shdr    shdr_rodata;
/* 0870h->+------+--------------------------------+ */
/*        | 040h | Section header  9 (.dynamic)   | */ Elf64_Shdr    shdr_dynamic;
/* 08b0h->+------+--------------------------------+ */
/*        | 040h | Section header 10 (.got.plt)   | */ Elf64_Shdr    shdr_gotplt;
/* 08f0h->+------+--------------------------------+ */
/*        | 040h | Section header 11 (.shstrtab)  | */ Elf64_Shdr    shdr_shstrtab;
/* 0930h->+------+--------------------------------+ */
/*        | 040h | Section header 12 (.symtab)    | */ Elf64_Shdr    shdr_symtab;
/* 0970h->+------+--------------------------------+ */
/*        | 040h | Section header 13 (.strtab)    | */ Elf64_Shdr    shdr_strtab;
/* 09b0h->+------+--------------------------------+ */
} elf;

#define IDX_PUTS_RELAPLT    0
#define IDX_PUTS_DYNSYM     1
#define IDX_PUTS_PLT        1
#define IDX_PUTS_GOTPLT     (IDX_PUTS_PLT + 2)
#define IDX_PUTS_SYMTAB     1

Elf64_Addr* GOT;
Elf64_Plt*  PLT;

int str_index(char *h, char *needle);

void set_linking_geometry()
{
    elf.shdr_null.sh_addr = 0x0;
    elf.shdr_null.sh_offset = 0x0;
    elf.shdr_null.sh_size = 0x0;
    elf.shdr_null.sh_addralign = 0x0;
    elf.shdr_null.sh_entsize = 0x0;

    elf.shdr_interp.sh_addr = 0x400200;
    elf.shdr_interp.sh_offset = 0x0200;
    elf.shdr_interp.sh_size = sizeof(elf.sect_interp);
    elf.shdr_interp.sh_addralign = 0x1000;
    elf.shdr_interp.sh_entsize = 0x0;

    elf.shdr_hash.sh_addr = 0x400280;
    elf.shdr_hash.sh_offset = 0x280;
    elf.shdr_hash.sh_size = sizeof(elf.sect_hash);
    elf.shdr_hash.sh_addralign = 0x1000;
    elf.shdr_hash.sh_entsize = 0x0;

    elf.shdr_dynsym.sh_addr = 0x4002a0;
    elf.shdr_dynsym.sh_offset = 0x2a0;
    elf.shdr_dynsym.sh_size = sizeof(elf.sect_dynsym);
    elf.shdr_dynsym.sh_addralign = 0x1000;
    elf.shdr_dynsym.sh_entsize = sizeof(elf.sect_dynsym[0]);

    elf.shdr_dynstr.sh_addr = 0x4002d0;
    elf.shdr_dynstr.sh_offset = 0x2d0;
    elf.shdr_dynstr.sh_size = sizeof(elf.sect_dynstr);
    elf.shdr_dynstr.sh_addralign = 0x1000;
    elf.shdr_dynstr.sh_entsize = 0x0;

    elf.shdr_relaplt.sh_addr = 0x4002f0;
    elf.shdr_relaplt.sh_offset = 0x2f0;
    elf.shdr_relaplt.sh_size = sizeof(elf.sect_relaplt);
    elf.shdr_relaplt.sh_addralign = 0x1000;
    elf.shdr_relaplt.sh_entsize = sizeof(elf.sect_relaplt[0]);

    elf.shdr_plt.sh_addr = 0x400308;
    elf.shdr_plt.sh_offset = 0x308;
    elf.shdr_plt.sh_size = sizeof(elf.sect_plt);
    elf.shdr_plt.sh_addralign = 0x1000;
    elf.shdr_plt.sh_entsize = sizeof(elf.sect_plt[0]);

    elf.shdr_text.sh_addr = 0x400328;
    elf.shdr_text.sh_offset = 0x328;
    elf.shdr_text.sh_size = sizeof(elf.sect_text);
    elf.shdr_text.sh_addralign = 0x1000;
    elf.shdr_text.sh_entsize = 0x0;

    elf.shdr_rodata.sh_addr = 0x400388;
    elf.shdr_rodata.sh_offset = 0x388;
    elf.shdr_rodata.sh_size = sizeof(elf.sect_rodata);
    elf.shdr_rodata.sh_addralign = 0x1000;
    elf.shdr_rodata.sh_entsize = 0x0;

    elf.shdr_dynamic.sh_addr = 0x6003a0;
    elf.shdr_dynamic.sh_offset = 0x3a0;
    elf.shdr_dynamic.sh_size = sizeof(elf.sect_dynamic);
    elf.shdr_dynamic.sh_addralign = 0x1000;
    elf.shdr_dynamic.sh_entsize = sizeof(elf.sect_dynamic[0]);

    elf.shdr_gotplt.sh_addr = 0x6004a0;
    elf.shdr_gotplt.sh_offset = 0x4a0;
    elf.shdr_gotplt.sh_size = sizeof(elf.sect_gotplt);
    elf.shdr_gotplt.sh_addralign = 0x1000;
    elf.shdr_gotplt.sh_entsize = sizeof(elf.sect_gotplt[0]);

    elf.shdr_shstrtab.sh_addr = 0x0;
    elf.shdr_shstrtab.sh_offset = 0x4e0;
    elf.shdr_shstrtab.sh_size = sizeof(elf.sect_shstrtab);
    elf.shdr_shstrtab.sh_addralign = 0x0;
    elf.shdr_shstrtab.sh_entsize = 0x0;

    elf.shdr_symtab.sh_addr = 0x0;
    elf.shdr_symtab.sh_offset = 0x5e0;
    elf.shdr_symtab.sh_size = sizeof(elf.sect_symtab);
    elf.shdr_symtab.sh_addralign = 0x0;
    elf.shdr_symtab.sh_entsize = sizeof(elf.sect_symtab[0]);

    elf.shdr_strtab.sh_addr = 0x0;
    elf.shdr_strtab.sh_offset = 0x610;
    elf.shdr_strtab.sh_size = sizeof(elf.sect_strtab);
    elf.shdr_strtab.sh_addralign = 0x0;
    elf.shdr_strtab.sh_entsize = 0x0;

    elf.header.e_entry = elf.shdr_text.sh_addr;
    elf.header.e_phoff = (Elf64_Off)(&(elf.phdr_PHDR)) - (Elf64_Off)(&elf);
    elf.header.e_shoff = (Elf64_Off)(&(elf.shdr_null)) - (Elf64_Off)(&elf);
    elf.header.e_ehsize = sizeof(elf.header);
    elf.header.e_phentsize = sizeof(elf.phdr_PHDR);
    elf.header.e_phnum = 5;
    elf.header.e_shentsize = sizeof(elf.shdr_null);
    elf.header.e_shnum = 14;
    elf.header.e_shstrndx = (&(elf.shdr_shstrtab)) - (&(elf.shdr_null));

    GOT = (Elf64_Addr*) (elf.shdr_gotplt.sh_addr);
    PLT = (Elf64_Plt*) (elf.shdr_plt.sh_addr);
}

void set_execution_geometry_and_attribute()
{
    /* PHDR <==> program header table */
    elf.phdr_PHDR.p_type = PT_PHDR;
    elf.phdr_PHDR.p_flags = PF_R | PF_X;
    elf.phdr_PHDR.p_offset = elf.header.e_phoff;
    elf.phdr_PHDR.p_filesz = elf.header.e_phnum * elf.header.e_phentsize;

    elf.phdr_PHDR.p_vaddr = 0x400000 + elf.phdr_PHDR.p_offset;
    elf.phdr_PHDR.p_paddr = elf.phdr_PHDR.p_vaddr;
    elf.phdr_PHDR.p_memsz = elf.phdr_PHDR.p_filesz;
    elf.phdr_PHDR.p_align = 0x1000;

    /* INTERP <==> Section .interp */
    elf.phdr_INTERP.p_type = PT_INTERP;
    elf.phdr_INTERP.p_flags = PF_R;
    elf.phdr_INTERP.p_offset = elf.shdr_interp.sh_offset;
    elf.phdr_INTERP.p_filesz = elf.shdr_interp.sh_size;

    elf.phdr_INTERP.p_vaddr = 0x400000 + elf.phdr_INTERP.p_offset;
    elf.phdr_INTERP.p_paddr = elf.phdr_INTERP.p_vaddr;
    elf.phdr_INTERP.p_memsz = elf.phdr_INTERP.p_filesz;
    elf.phdr_INTERP.p_align = 0x1000;

    /* LOAD_RE <==> Elf header, program header table,
     *              Section body .interp .hash .dynsym .rela.plt .plt .text .rodata */
    elf.phdr_LOAD_RE.p_type = PT_LOAD;
    elf.phdr_LOAD_RE.p_flags = PF_R | PF_X;
    elf.phdr_LOAD_RE.p_offset = 0x0;
    elf.phdr_LOAD_RE.p_filesz = elf.shdr_dynamic.sh_offset;

    elf.phdr_LOAD_RE.p_vaddr = 0x400000 + elf.phdr_LOAD_RE.p_offset;
    elf.phdr_LOAD_RE.p_paddr = elf.phdr_LOAD_RE.p_vaddr;
    elf.phdr_LOAD_RE.p_memsz = elf.phdr_LOAD_RE.p_filesz;
    elf.phdr_LOAD_RE.p_align = 0x1000;

    /* LOAD_RW <==> Section body .dynamic .got.plt */
    elf.phdr_LOAD_RW.p_type = PT_LOAD;
    elf.phdr_LOAD_RW.p_flags = PF_R | PF_W;
    elf.phdr_LOAD_RW.p_offset = elf.shdr_dynamic.sh_offset;
    elf.phdr_LOAD_RW.p_filesz = elf.shdr_dynamic.sh_size + elf.shdr_gotplt.sh_size;

    elf.phdr_LOAD_RW.p_vaddr = 0x600000 + elf.phdr_LOAD_RW.p_offset;
    elf.phdr_LOAD_RW.p_paddr = elf.phdr_LOAD_RW.p_vaddr;
    elf.phdr_LOAD_RW.p_memsz = elf.phdr_LOAD_RW.p_filesz;
    elf.phdr_LOAD_RW.p_align = 0x1000;

    /* DYNAMIC <==> Section body .dynamic */
    elf.phdr_DYNAMIC.p_type = PT_DYNAMIC;
    elf.phdr_DYNAMIC.p_flags = PF_R | PF_W;
    elf.phdr_DYNAMIC.p_offset = elf.shdr_dynamic.sh_offset;
    elf.phdr_DYNAMIC.p_filesz = elf.shdr_dynamic.sh_size;

    elf.phdr_DYNAMIC.p_vaddr = 0x600000 + elf.phdr_DYNAMIC.p_offset;
    elf.phdr_DYNAMIC.p_paddr = elf.phdr_DYNAMIC.p_vaddr;
    elf.phdr_DYNAMIC.p_memsz = elf.phdr_DYNAMIC.p_filesz;
    elf.phdr_DYNAMIC.p_align = 0x1000;
}

void make_strtabs()
{
    char names[] = {
       ".interp\x00"
       ".hash\x00"
       ".dynsym\x00"
       ".dynstr\x00"
       ".rela.plt\x00"
       ".plt\x00"
       ".text\x00"
       ".rodata\x00"
       ".dynamic\x00"
       ".got.plt\x00"
       ".shstrtab\x00"
       ".symtab\x00"
       ".strtab\x00"
    };
    memcpy(elf.sect_shstrtab+1, names, sizeof(names));
    memcpy(elf.sect_dynstr+1, "puts\x00libc.so.6", 14);
    strcpy(elf.sect_strtab + 1, "puts");

    elf.shdr_dynstr.sh_name = str_index(elf.sect_shstrtab, ".dynstr");
    elf.shdr_dynstr.sh_type = SHT_STRTAB;
    elf.shdr_dynstr.sh_flags = SHF_ALLOC;
    elf.shdr_dynstr.sh_link = 0x0;
    elf.shdr_dynstr.sh_info = 0x0;

    elf.shdr_shstrtab.sh_name = str_index(elf.sect_shstrtab, ".shstrtab");
    elf.shdr_shstrtab.sh_type = SHT_STRTAB;
    elf.shdr_shstrtab.sh_flags = SHF_NOFLAG;
    elf.shdr_shstrtab.sh_link = 0x0;
    elf.shdr_shstrtab.sh_info = 0x0;

    /* Section Body 9 (.shstrtab) */
    elf.shdr_strtab.sh_name = str_index(elf.sect_shstrtab, ".strtab");
    elf.shdr_strtab.sh_type = SHT_STRTAB;
    elf.shdr_strtab.sh_flags = SHF_NOFLAG;
    elf.shdr_strtab.sh_link = 0x0;
    elf.shdr_strtab.sh_info = 0x0;
}

void make_elf_header()
{
    /* Elf File Header */
    elf.header.e_ident[EI_MAG0] = ELFMAG0;
    elf.header.e_ident[EI_MAG1] = ELFMAG1;
    elf.header.e_ident[EI_MAG2] = ELFMAG2;
    elf.header.e_ident[EI_MAG3] = ELFMAG3;
    elf.header.e_ident[EI_CLASS] = ELFCLASS64;
    elf.header.e_ident[EI_DATA] = ELFDATA2LSB;
    elf.header.e_ident[EI_VERSION] = EV_CURRENT;
    elf.header.e_ident[EI_OSABI] = ELFOSABI_NONE;
    elf.header.e_type = ET_EXEC;
    elf.header.e_machine = EM_X86_64;
    elf.header.e_version = EV_CURRENT;
    elf.header.e_flags = EF_NOFLAG;
}

void make_section_header_null()
{
    elf.shdr_null.sh_type = SHT_NULL;
    elf.shdr_null.sh_name = 0x0;
    elf.shdr_null.sh_flags = 0x0;
    elf.shdr_null.sh_link = 0x0;
    elf.shdr_null.sh_info = 0x0;
}

void make_section_interp()
{
    strcpy(elf.sect_interp, "/lib64/ld-linux-x86-64.so.2");

    elf.shdr_interp.sh_name = str_index(elf.sect_shstrtab, ".interp");
    elf.shdr_interp.sh_type = SHT_PROGBITS;
    elf.shdr_interp.sh_flags = SHF_ALLOC;
    elf.shdr_interp.sh_link = 0x0;
    elf.shdr_interp.sh_info = 0x0;
}

void make_section_hash()
{
    elf.shdr_hash.sh_name = str_index(elf.sect_shstrtab, ".hash");
    elf.shdr_hash.sh_type = SHT_HASH;
    elf.shdr_hash.sh_flags = SHF_ALLOC;
    elf.shdr_hash.sh_link = (&(elf.shdr_dynsym)) - (&(elf.shdr_null));
    elf.shdr_hash.sh_info = 0x0;

    memcpy(elf.sect_hash, "\x01\x00\x00\x00\x01\x00\x00\x00"
                          "\x01\x00\x00\x00\x00\x00\x00\x00", 0x10);
}

void make_section_dynsym()
{
    elf.shdr_dynsym.sh_name = str_index(elf.sect_shstrtab, ".dynsym");
    elf.shdr_dynsym.sh_type = SHT_DYNSYM;
    elf.shdr_dynsym.sh_flags = SHF_ALLOC;
    elf.shdr_dynsym.sh_link = (&(elf.shdr_dynstr)) - (&(elf.shdr_null));
    elf.shdr_dynsym.sh_info = IDX_PUTS_DYNSYM;  // index of the first GLOBAL SYMBOL

    elf.sect_dynsym[IDX_PUTS_DYNSYM].st_name = str_index(elf.sect_dynstr, "puts");
    elf.sect_dynsym[IDX_PUTS_DYNSYM].st_info = ELF64_ST_INFO(STB_GLOBAL, STT_FUNC);
    elf.sect_dynsym[IDX_PUTS_DYNSYM].st_other = 0x0;
    elf.sect_dynsym[IDX_PUTS_DYNSYM].st_shndx = 0x0;
    elf.sect_dynsym[IDX_PUTS_DYNSYM].st_value = 0x0;
    elf.sect_dynsym[IDX_PUTS_DYNSYM].st_size = 0x0;
}

void make_section_relaplt()
{
    elf.shdr_relaplt.sh_name = str_index(elf.sect_shstrtab, ".rela.plt");
    elf.shdr_relaplt.sh_type = SHT_RELA;
    elf.shdr_relaplt.sh_flags = INFO_LINK | SHF_ALLOC;
    elf.shdr_relaplt.sh_link = (&(elf.shdr_dynsym)) - (&(elf.shdr_null));
    elf.shdr_relaplt.sh_info = (&(elf.shdr_plt)) - (&(elf.shdr_null));

    elf.sect_relaplt[IDX_PUTS_RELAPLT].r_offset = (Elf64_Addr)(&GOT[IDX_PUTS_GOTPLT]);
    elf.sect_relaplt[IDX_PUTS_RELAPLT].r_info = ELF64_R_INFO(IDX_PUTS_DYNSYM, R_X86_64_JUMP_SLOT);
    elf.sect_relaplt[IDX_PUTS_RELAPLT].r_addend = 0x0;
}

void make_section_plt()
{
    elf.shdr_plt.sh_name = str_index(elf.sect_shstrtab, ".plt");
    elf.shdr_plt.sh_type = SHT_PROGBITS;
    elf.shdr_plt.sh_flags = SHF_EXECINSTR | SHF_ALLOC;
    elf.shdr_plt.sh_link = 0x0;
    elf.shdr_plt.sh_info = 0x0;

    /* <PLT0> */
    char *plt0code = "\xff\x35\x00\x00\x00\x00"   /* push qword [rip+0x00000000] (GOT[1]) */
                     "\xff\x25\x00\x00\x00\x00"   /* jmp qword [rip+0x00000000] (GOT[2]) */
                     "\x90\x90\x90\x90";          /* nop,nop,nop,nop */
    char *plt0 = (char*)(&(elf.sect_plt[0]));
    memcpy(plt0, plt0code, sizeof(elf.sect_plt[0]));
    Elf64_Addr RIP = (Elf64_Addr)(&PLT[0]) + 6, DEST = (Elf64_Addr)(&GOT[1]);
    *((Elf64_Word*)(plt0+2)) = (Elf64_Word)(DEST - RIP);
    RIP += 6; DEST = (Elf64_Addr)(&GOT[2]);
    *((Elf64_Word*)(plt0+8)) = (Elf64_Word)(DEST - RIP);

    /* <PLT1(puts)> */
    int i = IDX_PUTS_PLT, j = IDX_PUTS_GOTPLT, k = IDX_PUTS_RELAPLT;
    char *plticode = "\xff\x25\x00\x00\x00\x00"   /* jmp qword [rip+0x00000000] (GOT[j]) */
                     "\x68\x00\x00\x00\x00"       /* push 0x00000000 (k) */
                     "\xe9\x00\x00\x00\x00";      /* jmp rip+0x00000000 (&PLT[0]) */
    char *plti = (char*)&(elf.sect_plt[i]);
    memcpy(plti, plticode, sizeof(elf.sect_plt[i]));
    RIP = (Elf64_Addr)(&PLT[i]) + 6; DEST = (Elf64_Addr)(&GOT[j]);
    *((Elf64_Word*)(plti+2)) = (Elf64_Word)(DEST - RIP);
    *((Elf64_Word*)(plti+7)) = (Elf64_Word)(k);
    RIP += 10; DEST = (Elf64_Addr)(&PLT[0]);
    *((Elf64_Word*)(plti+12)) = (Elf64_Word)(DEST - RIP);
}

void make_section_text()
{
    elf.shdr_text.sh_name = str_index(elf.sect_shstrtab, ".text");
    elf.shdr_text.sh_type = SHT_PROGBITS;
    elf.shdr_text.sh_flags = SHF_EXECINSTR | SHF_ALLOC;
    elf.shdr_text.sh_link = 0x0;
    elf.shdr_text.sh_info = 0x0;

    char *code = "\x48\xbf\x00\x00"
                 "\x00\x00\x00\x00\x00\x00"  /* movabs rdi,0x00000000-00000000 "Hello..." */
                 "\xe8\x00\x00\x00\x00"      /* call <puts@plt> (PLT[1]) */
                 "\x29\xc0"                	 /* sub eax,eax */
                 "\xb0\x3c"                	 /* mov al,0x3c ; sys_exit */
                 "\x48\x29\xff"            	 /* sub rdi,rdi */
                 "\x0f\x05";               	 /* syscall */
    memcpy(elf.sect_text, code, 0x18);
    *(Elf64_Addr*)(elf.sect_text+0x2) = elf.shdr_rodata.sh_addr;
    Elf64_Addr RIP = elf.shdr_text.sh_addr + 0xf, DEST = (Elf64_Addr)(&PLT[IDX_PUTS_PLT]);
    *((Elf64_Word*)(elf.sect_text+0xb)) = (Elf64_Word)(DEST - RIP);
}

void make_section_rodata()
{
    elf.shdr_rodata.sh_name = str_index(elf.sect_shstrtab, ".rodata");
    elf.shdr_rodata.sh_type = SHT_PROGBITS;
    elf.shdr_rodata.sh_flags = SHF_ALLOC;
    elf.shdr_rodata.sh_link = 0x0;
    elf.shdr_rodata.sh_info = 0x0;

    strcpy(elf.sect_rodata, "Hello world!");
}

void make_section_dynamic()
{
    elf.shdr_dynamic.sh_name = str_index(elf.sect_shstrtab, ".dynamic");
    elf.shdr_dynamic.sh_type = SHT_DYNAMIC;
    elf.shdr_dynamic.sh_flags = SHF_ALLOC | SHF_WRITE;
    elf.shdr_dynamic.sh_link = (&(elf.shdr_dynstr)) - (&(elf.shdr_null));
    elf.shdr_dynamic.sh_info = 0x0;

    elf.sect_dynamic[0].d_tag = DT_NEEDED;
    elf.sect_dynamic[0].d_un.d_val = str_index(elf.sect_dynstr, "libc.so.6");

    elf.sect_dynamic[1].d_tag = DT_HASH;
    elf.sect_dynamic[1].d_un.d_ptr = elf.shdr_hash.sh_addr;

    elf.sect_dynamic[2].d_tag = DT_STRTAB;
    elf.sect_dynamic[2].d_un.d_ptr = elf.shdr_dynstr.sh_addr;

    elf.sect_dynamic[3].d_tag = DT_SYMTAB;
    elf.sect_dynamic[3].d_un.d_ptr = elf.shdr_dynsym.sh_addr;

    elf.sect_dynamic[4].d_tag = DT_STRSZ;
    elf.sect_dynamic[4].d_un.d_val = elf.shdr_dynstr.sh_size;

    elf.sect_dynamic[5].d_tag = DT_SYMENT;
    elf.sect_dynamic[5].d_un.d_val = elf.shdr_dynsym.sh_entsize;

    elf.sect_dynamic[6].d_tag = DT_PLTGOT;
    elf.sect_dynamic[6].d_un.d_ptr = elf.shdr_gotplt.sh_addr;

    elf.sect_dynamic[7].d_tag = DT_PLTRELSZ;
    elf.sect_dynamic[7].d_un.d_val = elf.shdr_relaplt.sh_size;

    elf.sect_dynamic[8].d_tag = DT_PLTREL;
    elf.sect_dynamic[8].d_un.d_val = DT_RELA;

    elf.sect_dynamic[9].d_tag = DT_JMPREL;
    elf.sect_dynamic[9].d_un.d_ptr = elf.shdr_relaplt.sh_addr;

    elf.sect_dynamic[10].d_tag = DT_RELA;
    elf.sect_dynamic[10].d_un.d_val = elf.shdr_relaplt.sh_addr;

    elf.sect_dynamic[11].d_tag = DT_RELASZ;
    elf.sect_dynamic[11].d_un.d_val = elf.shdr_relaplt.sh_size;

    elf.sect_dynamic[12].d_tag = DT_RELAENT;
    elf.sect_dynamic[12].d_un.d_ptr = elf.shdr_relaplt.sh_entsize;

    elf.sect_dynamic[13].d_tag = DT_NULL;
    elf.sect_dynamic[13].d_un.d_val = 0x0;
}

void make_section_gotplt()
{
    elf.shdr_gotplt.sh_name = str_index(elf.sect_shstrtab, ".got.plt");
    elf.shdr_gotplt.sh_type = SHT_PROGBITS;
    elf.shdr_gotplt.sh_flags = SHF_ALLOC | SHF_WRITE;
    elf.shdr_gotplt.sh_link = 0x0;
    elf.shdr_gotplt.sh_info = 0x0;

    elf.sect_gotplt[0] = elf.shdr_dynamic.sh_addr;
    elf.sect_gotplt[1] = 0x0;
    elf.sect_gotplt[2] = 0x0;
    elf.sect_gotplt[3] = (Elf64_Addr)(&PLT[IDX_PUTS_PLT]) + 6;
}

void make_section_symtab()
{
    elf.shdr_symtab.sh_name = str_index(elf.sect_shstrtab, ".symtab");
    elf.shdr_symtab.sh_type = SHT_SYMTAB;
    elf.shdr_symtab.sh_flags = SHF_NOFLAG;
    elf.shdr_symtab.sh_link = (&(elf.shdr_strtab)) - (&(elf.shdr_null));
    elf.shdr_symtab.sh_info = IDX_PUTS_SYMTAB;  // index of the first GLOBAL SYMBOL

    elf.sect_symtab[IDX_PUTS_SYMTAB].st_name = str_index(elf.sect_strtab, "puts");
    elf.sect_symtab[IDX_PUTS_SYMTAB].st_info = ELF64_ST_INFO(STB_GLOBAL, STT_FUNC);
    elf.sect_symtab[IDX_PUTS_SYMTAB].st_other = 0x0;
    elf.sect_symtab[IDX_PUTS_SYMTAB].st_shndx = 0x0;
    elf.sect_symtab[IDX_PUTS_SYMTAB].st_value = 0x0;
    elf.sect_symtab[IDX_PUTS_SYMTAB].st_size = 0x0;
}

// ineffient, only works here
int str_index(char *h, char *needle)
{
    int i = 0, j = 0;
    while (needle[j]) {
        if (i >= 200) {
            fprintf(stderr, "Error in str_index:\nh=%s\nneedle=%s\n", h+1, needle);
            return -1;
        }
        if (h[i] == needle[j]) {
            i++;
            j++;
        } else {
            i = i - j + 1;
            j = 0;
        }
    }
    return i - j;
}

int main(int argc, char *argv[])
{
    /* Write Out Elf */
    FILE *fp = fopen("elf.out", "w");
    if (!fp) {
        fprintf(stderr, "Can not open elf.out to write\n");
        return 1;
    }

    set_linking_geometry();
    set_execution_geometry_and_attribute();
    make_strtabs();
    make_elf_header();
    make_section_header_null();
    make_section_interp();
    make_section_hash();
    make_section_dynsym();
    make_section_relaplt();
    make_section_plt();
    make_section_text();
    make_section_rodata();
    make_section_dynamic();
    make_section_gotplt();
    make_section_symtab();

    fwrite((void*)&elf, 1, sizeof(elf), fp);
    fclose(fp);

    return 0;
}
