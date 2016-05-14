#include <stdio.h>
#include <string.h>
#include <linux/elf.h>

/* Elf File Layout */
struct {
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
/*        | 020h | Section body  2 (.hash)        | */ unsigned char sect_hash[0x020];
/* 02a0h->+------+--------------------------------+<-0x4002a0 */
/*        | 030h | Section body  3 (.dynsym)      | */ Elf64_Sym     sect_dynsym[2];
/* 02d0h->+------+--------------------------------+<-0x4002d0 */
/*        | 020h | Section body  4 (.dynstr)      | */ unsigned char sect_dynstr[0x020];
/* 02f0h->+------+--------------------------------+<-0x4002f0 */
/*        | 018h | Section body  5 (.rela.plt)    | */ Elf64_Rela    sect_relaplt[1];
/* 0308h->+------+--------------------------------+<-0x400308 */
/*        | 020h | Section body  6 (.plt)         | */ unsigned char sect_plt[0x020];
/* 0328h->+------+--------------------------------+<-0x400328 */
/*        | 060h | Section body  7 (.text)        | */ unsigned char sect_text[0x060];
/* 0388h->+------+--------------------------------+<-0x400388 */
/*        | 018h | Section body  8 (.rodata)      | */ unsigned char sect_rodata[0x018];
/* 03a0h->+------+--------------------------------+<-0x6003a0 */
/*        | 100h | Section body  9 (.dynamic)     | */ Elf64_Dyn     sect_dynamic[16];
/* 04a0h->+------+--------------------------------+<-0x6004a0 */
/*        | 040h | Section body 10 (.got.plt)     | */ Elf64_Addr	 sect_gotplt[4];
/* 04e0h->+------+--------------------------------+ */
/*        | 100h | Section body 11 (.shstrtab)    | */ unsigned char sect_shstrtab[0x100];
/* 05e0h->+------+--------------------------------+ */
/*        | 030h | Section body 12 (.symtab)      | */ Elf64_Sym     sect_symtab[2];
/* 0610h->+------+--------------------------------+ */
/*        | 020h | Section body 13 (.strtab)      | */ unsigned char sect_strtab[0x20];
/* 0630h->+------+--------------------------------+ */
/*        | 040h | Section header  0 (null)       | */ Elf64_Shdr shdr_null;
/* 0670h->+------+--------------------------------+ */
/*        | 040h | Section header  1 (.interp)    | */ Elf64_Shdr shdr_interp;
/* 06b0h->+------+--------------------------------+ */
/*        | 040h | Section header  2 (.hash)      | */ Elf64_Shdr shdr_hash;
/* 06f0h->+------+--------------------------------+ */
/*        | 040h | Section header  3 (.dynsym)    | */ Elf64_Shdr shdr_dynsym;
/* 0730h->+------+--------------------------------+ */
/*        | 040h | Section header  4 (.dynstr)    | */ Elf64_Shdr shdr_dynstr;
/* 0770h->+------+--------------------------------+ */
/*        | 040h | Section header  5 (.rela.plt)  | */ Elf64_Shdr shdr_relaplt;
/* 07b0h->+------+--------------------------------+ */
/*        | 040h | Section header  6 (.plt)       | */ Elf64_Shdr shdr_plt;
/* 07f0h->+------+--------------------------------+ */
/*        | 040h | Section header  7 (.text)      | */ Elf64_Shdr shdr_text;
/* 0830h->+------+--------------------------------+ */
/*        | 040h | Section header  8 (.rodata)    | */ Elf64_Shdr shdr_rodata;
/* 0870h->+------+--------------------------------+ */
/*        | 040h | Section header  9 (.dynamic)   | */ Elf64_Shdr shdr_dynamic;
/* 08b0h->+------+--------------------------------+ */
/*        | 040h | Section header 10 (.got.plt)   | */ Elf64_Shdr shdr_gotplt;
/* 08f0h->+------+--------------------------------+ */
/*        | 040h | Section header 11 (.shstrtab)  | */ Elf64_Shdr shdr_shstrtab;
/* 0930h->+------+--------------------------------+ */
/*        | 040h | Section header 12 (.symtab)    | */ Elf64_Shdr shdr_symtab;
/* 0970h->+------+--------------------------------+ */
/*        | 040h | Section header 13 (.strtab)    | */ Elf64_Shdr shdr_strtab;
/* 09b0h->+------+--------------------------------+ */
} elf;

#define NOFLAG	0
#define GOT		0x6004a0
#define PLT		0x400308
#define ENTRY	0X400328
#define SHNUM	14
#define PHNUM	5

int index(char *h, char *needle)
{
	int i = 0, j = 0;
	while (needle[j]) {
		if (i >= 1000) {
			return -1;
		}
		if (h[i] == needle[j]) {
			i++;
			j++;
		} else {
			j = 0;
		}
	}
	return i;
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
	elf.header.e_entry = ENTRY;
	elf.header.e_phoff = (Elf64_Off)(&(elf.phdr_PHDR)) - (Elf64_Off)(&elf);
	elf.header.e_shoff = (Elf64_Off)(&(elf.shdr_null)) - (Elf64_Off)(&elf);
	elf.header.e_flags = NOFLAG;
	elf.header.e_ehsize = sizeof(Elf64_Ehdr);
	elf.header.e_phentsize = sizeof(Elf64_Phdr);
	elf.header.e_phnum = PHNUM;
	elf.header.e_shentsize = sizeof(Elf64_Shdr);
	elf.header.e_shnum = SHNUM;
	elf.header.e_shstrndx = (&(elf.shdr_shstrtab)) - (&(elf.shdr_null));
}

void make_section_header_null()
{
	/* Section Header 0 (null) */
	elf.shdr_null.sh_type = SHT_NULL;
	elf.shdr_null.sh_addralign = 0x0;
	elf.shdr_null.sh_offset = 0x0;
	elf.shdr_null.sh_entsize = 0x0;
	elf.shdr_null.sh_name = 0x0;
	elf.shdr_null.sh_flags = 0x0;
	elf.shdr_null.sh_size = 0x0;
	elf.shdr_null.sh_addr = 0x0;
	elf.shdr_null.sh_link = 0x0;
	elf.shdr_null.sh_info = 0x0;
}

void make_section_interp()
{
	/* Section Header 1 (.interp) */
	elf.shdr_interp.sh_name = index(elf.sect_shstrtab, ".interp");
	elf.shdr_interp.sh_type = SHT_PROGBITS;
	elf.shdr_interp.sh_flags = SHF_ALLOC;
	elf.shdr_interp.sh_addr = 0x400200;
	elf.shdr_interp.sh_offset = 0x0200;
	elf.shdr_interp.sh_size = sizeof(elf.sect_interp);
	elf.shdr_interp.sh_link = 0x0;
	elf.shdr_interp.sh_info = 0x0;
	elf.shdr_interp.sh_addralign = 0x1000;
	elf.shdr_interp.sh_entsize = 0x0;

	/* Section Body 1 (.interp) */
	strcpy(elf.sect_interp, "/lib64/ld-linux-x86-64.so.2");
}

void make_section_hash()
{
	/* Section Header 2 (.hash) */
	elf.shdr_hash.sh_name = index(elf.sect_shstrtab, ".hash");
	elf.shdr_hash.sh_type = SHT_HASH;
	elf.shdr_hash.sh_flags = SHF_ALLOC;
	elf.shdr_hash.sh_addr = 0x400280;
	elf.shdr_hash.sh_offset = 0x280;
	elf.shdr_hash.sh_size = sizeof(elf.sect_hash);
	elf.shdr_hash.sh_link = (&(elf.shdr_dynsym)) - (&(elf.shdr_null));
	elf.shdr_hash.sh_info = 0x0;
	elf.shdr_hash.sh_addralign = 0x1000;
	elf.shdr_hash.sh_entsize = 0x0;

	/* Section Body 2 (.hash) */
	memcpy(elf.sect_hash,
	       "\x01\x00\x00\x00\x01\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00",
	       0x10);
}

void make_section_dynsym()
{
	/* Section Header 3 (.dynsym) */
	elf.shdr_dynsym.sh_name = index(elf.sect_shstrtab, ".dynsym");
	elf.shdr_dynsym.sh_type = SHT_DYNSYM;
	elf.shdr_dynsym.sh_flags = SHF_ALLOC;
	elf.shdr_dynsym.sh_addr = 0x4002a0;
	elf.shdr_dynsym.sh_offset = 0x2a0;
	elf.shdr_dynsym.sh_size = sizeof(elf.sect_dynsym);
	elf.shdr_dynsym.sh_link = (&(elf.shdr_dynstr)) - (&(elf.shdr_null));
	elf.shdr_dynsym.sh_info = 0x1;
	elf.shdr_dynsym.sh_addralign = 0x1000;
	elf.shdr_dynsym.sh_entsize = sizeof(Elf64_Sym);

	/* Section Body 5 (.dynsym) */
	elf.sect_dynsym[1].st_name = index(elf.sect_dynstr, "puts");
	elf.sect_dynsym[1].st_info = ELF64_ST_INFO(STB_GLOBAL, STT_FUNC);
	elf.sect_dynsym[1].st_other = 0x0;
	elf.sect_dynsym[1].st_shndx = 0x0;
	elf.sect_dynsym[1].st_value = 0x0;
	elf.sect_dynsym[1].st_size = 0x0;
}


void make_section_dynstr()
{
	/* Section Header 4 (.dynstr) */
	elf.shdr_dynstr.sh_name = index(elf.sect_shstrtab, ".dynstr");
	elf.shdr_dynstr.sh_type = SHT_STRTAB;
	elf.shdr_dynstr.sh_flags = SHF_ALLOC;
	elf.shdr_dynstr.sh_addr = 0x4002d0;
	elf.shdr_dynstr.sh_offset = 0x2d0;
	elf.shdr_dynstr.sh_size = sizeof(elf.sect_dynstr);
	elf.shdr_dynstr.sh_link = 0x0;
	elf.shdr_dynstr.sh_info = 0x0;
	elf.shdr_dynstr.sh_addralign = 0x1000;
	elf.shdr_dynstr.sh_entsize = 0;

	/* Section Body 4 (.dynstr) */
	memcpy(elf.sect_dynstr, "\x00puts\x00", 6);
}

void make_section_relaplt()
{
	/* Section Header 10 (.rela.plt) */
	elf.shdr_relaplt.sh_name = index(elf.sect_shstrtab, ".rela.plt");
	elf.shdr_relaplt.sh_type = SHT_RELA;
	elf.shdr_relaplt.sh_flags = 0x40 | SHF_ALLOC; // what's the 0x40 for?
	elf.shdr_relaplt.sh_addr = 0x4002f0;
	elf.shdr_relaplt.sh_offset = 0x2f0;
	elf.shdr_relaplt.sh_size = sizeof(elf.sect_relaplt);
	elf.shdr_relaplt.sh_link = (&(elf.shdr_dynsym)) - (&(elf.shdr_null));
	elf.shdr_relaplt.sh_info = (&(elf.shdr_plt)) - (&(elf.shdr_null));
	elf.shdr_relaplt.sh_addralign = 0x1000;
	elf.shdr_relaplt.sh_entsize = sizeof(Elf64_Rela);

	/* Section Body 10 (.rela.plt) */
	elf.sect_relaplt = 

	memcpy(elf.section_body10 , 
	       "\xf8\x08\x60\x00\x00\x00\x00\x00\x07\x00\x00\x00\x01\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x09\x60\x00\x00\x00\x00\x00" 
	       "\x07\x00\x00\x00\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\x08\x09\x60\x00\x00\x00\x00\x00\x07\x00\x00\x00\x03\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00" ,
	       72);




}


	/* Section Header 11 (.init) */
	elf.section_header11.sh_type = SHT_PROGBITS;
	elf.section_header11.sh_addralign = 0x4;
	elf.section_header11.sh_offset = 0x3a8;
	elf.section_header11.sh_entsize = 0x0;
	elf.section_header11.sh_name = 0x8e;
	elf.section_header11.sh_flags = 0x6;
	elf.section_header11.sh_size = 0x1a;
	elf.section_header11.sh_addr = 0x4003a8;
	elf.section_header11.sh_link = 0x0;
	elf.section_header11.sh_info = 0x0;

	/* Section Header 12 (.plt) */
	elf.section_header12.sh_type = SHT_PROGBITS;
	elf.section_header12.sh_addralign = 0x10;
	elf.section_header12.sh_offset = 0x3d0;
	elf.section_header12.sh_entsize = 0x10;
	elf.section_header12.sh_name = 0x89;
	elf.section_header12.sh_flags = 0x6;
	elf.section_header12.sh_size = 0x40;
	elf.section_header12.sh_addr = 0x4003d0;
	elf.section_header12.sh_link = 0x0;
	elf.section_header12.sh_info = 0x0;

	/* Section Header 13 (.text) */
	elf.section_header13.sh_type = SHT_PROGBITS;
	elf.section_header13.sh_addralign = 0x10;
	elf.section_header13.sh_offset = 0x410;
	elf.section_header13.sh_entsize = 0x0;
	elf.section_header13.sh_name = 0x94;
	elf.section_header13.sh_flags = 0x6;
	elf.section_header13.sh_size = 0x192;
	elf.section_header13.sh_addr = 0x400410;
	elf.section_header13.sh_link = 0x0;
	elf.section_header13.sh_info = 0x0;

	/* Section Header 14 (.fini) */
	elf.section_header14.sh_type = SHT_PROGBITS;
	elf.section_header14.sh_addralign = 0x4;
	elf.section_header14.sh_offset = 0x5a4;
	elf.section_header14.sh_entsize = 0x0;
	elf.section_header14.sh_name = 0x9a;
	elf.section_header14.sh_flags = 0x6;
	elf.section_header14.sh_size = 0x9;
	elf.section_header14.sh_addr = 0x4005a4;
	elf.section_header14.sh_link = 0x0;
	elf.section_header14.sh_info = 0x0;

	/* Section Header 15 (.rodata) */
	elf.section_header15.sh_type = SHT_PROGBITS;
	elf.section_header15.sh_addralign = 0x4;
	elf.section_header15.sh_offset = 0x5b0;
	elf.section_header15.sh_entsize = 0x0;
	elf.section_header15.sh_name = 0xa0;
	elf.section_header15.sh_flags = 0x2;
	elf.section_header15.sh_size = 0x11;
	elf.section_header15.sh_addr = 0x4005b0;
	elf.section_header15.sh_link = 0x0;
	elf.section_header15.sh_info = 0x0;

	/* Section Header 16 (.eh_frame_hdr) */
	elf.section_header16.sh_type = SHT_PROGBITS;
	elf.section_header16.sh_addralign = 0x4;
	elf.section_header16.sh_offset = 0x5c4;
	elf.section_header16.sh_entsize = 0x0;
	elf.section_header16.sh_name = 0xa8;
	elf.section_header16.sh_flags = 0x2;
	elf.section_header16.sh_size = 0x34;
	elf.section_header16.sh_addr = 0x4005c4;
	elf.section_header16.sh_link = 0x0;
	elf.section_header16.sh_info = 0x0;

	/* Section Header 17 (.eh_frame) */
	elf.section_header17.sh_type = SHT_PROGBITS;
	elf.section_header17.sh_addralign = 0x8;
	elf.section_header17.sh_offset = 0x5f8;
	elf.section_header17.sh_entsize = 0x0;
	elf.section_header17.sh_name = 0xb6;
	elf.section_header17.sh_flags = 0x2;
	elf.section_header17.sh_size = 0xf4;
	elf.section_header17.sh_addr = 0x4005f8;
	elf.section_header17.sh_link = 0x0;
	elf.section_header17.sh_info = 0x0;

	/* Section Header 18 (.init_array) */
	elf.section_header18.sh_type = SHT_INIT_ARRAY;
	elf.section_header18.sh_addralign = 0x8;
	elf.section_header18.sh_offset = 0x6f0;
	elf.section_header18.sh_entsize = 0x0;
	elf.section_header18.sh_name = 0xc0;
	elf.section_header18.sh_flags = 0x3;
	elf.section_header18.sh_size = 0x8;
	elf.section_header18.sh_addr = 0x6006f0;
	elf.section_header18.sh_link = 0x0;
	elf.section_header18.sh_info = 0x0;

	/* Section Header 19 (.fini_array) */
	elf.section_header19.sh_type = SHT_FINI_ARRAY;
	elf.section_header19.sh_addralign = 0x8;
	elf.section_header19.sh_offset = 0x6f8;
	elf.section_header19.sh_entsize = 0x0;
	elf.section_header19.sh_name = 0xcc;
	elf.section_header19.sh_flags = 0x3;
	elf.section_header19.sh_size = 0x8;
	elf.section_header19.sh_addr = 0x6006f8;
	elf.section_header19.sh_link = 0x0;
	elf.section_header19.sh_info = 0x0;

	/* Section Header 20 (.jcr) */
	elf.section_header20.sh_type = SHT_PROGBITS;
	elf.section_header20.sh_addralign = 0x8;
	elf.section_header20.sh_offset = 0x700;
	elf.section_header20.sh_entsize = 0x0;
	elf.section_header20.sh_name = 0xd8;
	elf.section_header20.sh_flags = 0x3;
	elf.section_header20.sh_size = 0x8;
	elf.section_header20.sh_addr = 0x600700;
	elf.section_header20.sh_link = 0x0;
	elf.section_header20.sh_info = 0x0;

	/* Section Header 21 (.dynamic) */
	elf.section_header21.sh_type = SHT_DYNAMIC;
	elf.section_header21.sh_addralign = 0x8;
	elf.section_header21.sh_offset = 0x708;
	elf.section_header21.sh_entsize = 0x10;
	elf.section_header21.sh_name = 0xdd;
	elf.section_header21.sh_flags = 0x3;
	elf.section_header21.sh_size = 0x1d0;
	elf.section_header21.sh_addr = 0x600708;
	elf.section_header21.sh_link = 0x6;
	elf.section_header21.sh_info = 0x0;

	/* Section Header 22 (.got) */
	elf.section_header22.sh_type = SHT_PROGBITS;
	elf.section_header22.sh_addralign = 0x8;
	elf.section_header22.sh_offset = 0x8d8;
	elf.section_header22.sh_entsize = 0x8;
	elf.section_header22.sh_name = 0xe6;
	elf.section_header22.sh_flags = 0x3;
	elf.section_header22.sh_size = 0x8;
	elf.section_header22.sh_addr = 0x6008d8;
	elf.section_header22.sh_link = 0x0;
	elf.section_header22.sh_info = 0x0;

	/* Section Header 23 (.got.plt) */
	elf.section_header23.sh_type = SHT_PROGBITS;
	elf.section_header23.sh_addralign = 0x8;
	elf.section_header23.sh_offset = 0x8e0;
	elf.section_header23.sh_entsize = 0x8;
	elf.section_header23.sh_name = 0xeb;
	elf.section_header23.sh_flags = 0x3;
	elf.section_header23.sh_size = 0x30;
	elf.section_header23.sh_addr = 0x6008e0;
	elf.section_header23.sh_link = 0x0;
	elf.section_header23.sh_info = 0x0;

	/* Section Header 24 (.data) */
	elf.section_header24.sh_type = SHT_PROGBITS;
	elf.section_header24.sh_addralign = 0x8;
	elf.section_header24.sh_offset = 0x910;
	elf.section_header24.sh_entsize = 0x0;
	elf.section_header24.sh_name = 0xf4;
	elf.section_header24.sh_flags = 0x3;
	elf.section_header24.sh_size = 0x10;
	elf.section_header24.sh_addr = 0x600910;
	elf.section_header24.sh_link = 0x0;
	elf.section_header24.sh_info = 0x0;

	/* Section Header 25 (.bss) */
	elf.section_header25.sh_type = SHT_NOBITS;
	elf.section_header25.sh_addralign = 0x1;
	elf.section_header25.sh_offset = 0x920;
	elf.section_header25.sh_entsize = 0x0;
	elf.section_header25.sh_name = 0xfa;
	elf.section_header25.sh_flags = 0x3;
	elf.section_header25.sh_size = 0x8;
	elf.section_header25.sh_addr = 0x600920;
	elf.section_header25.sh_link = 0x0;
	elf.section_header25.sh_info = 0x0;

	/* Section Header 26 (.comment) */
	elf.section_header26.sh_type = SHT_PROGBITS;
	elf.section_header26.sh_addralign = 0x1;
	elf.section_header26.sh_offset = 0x920;
	elf.section_header26.sh_entsize = 0x1;
	elf.section_header26.sh_name = 0xff;
	elf.section_header26.sh_flags = 0x30;
	elf.section_header26.sh_size = 0x39;
	elf.section_header26.sh_addr = 0x0;
	elf.section_header26.sh_link = 0x0;
	elf.section_header26.sh_info = 0x0;

	/* Section Header 27 (.shstrtab) */
	elf.section_header27.sh_type = SHT_STRTAB;
	elf.section_header27.sh_addralign = 0x1;
	elf.section_header27.sh_offset = 0x959;
	elf.section_header27.sh_entsize = 0x0;
	elf.section_header27.sh_name = 0x11;
	elf.section_header27.sh_flags = 0x0;
	elf.section_header27.sh_size = 0x108;
	elf.section_header27.sh_addr = 0x0;
	elf.section_header27.sh_link = 0x0;
	elf.section_header27.sh_info = 0x0;

	/* Section Header 28 (.symtab) */
	elf.section_header28.sh_type = SHT_SYMTAB;
	elf.section_header28.sh_addralign = 0x8;
	elf.section_header28.sh_offset = 0xa68;
	elf.section_header28.sh_entsize = 0x18;
	elf.section_header28.sh_name = 0x1;
	elf.section_header28.sh_flags = 0x0;
	elf.section_header28.sh_size = 0x618;
	elf.section_header28.sh_addr = 0x0;
	elf.section_header28.sh_link = 0x1d;
	elf.section_header28.sh_info = 0x2d;

	/* Section Header 29 (.strtab) */
	elf.section_header29.sh_type = SHT_STRTAB;
	elf.section_header29.sh_addralign = 0x1;
	elf.section_header29.sh_offset = 0x1080;
	elf.section_header29.sh_entsize = 0x0;
	elf.section_header29.sh_name = 0x9;
	elf.section_header29.sh_flags = 0x0;
	elf.section_header29.sh_size = 0x237;
	elf.section_header29.sh_addr = 0x0;
	elf.section_header29.sh_link = 0x0;
	elf.section_header29.sh_info = 0x0;

	

	

	

	

	/* Section Body 11 (.init) */
	memcpy(elf.section_body11 , 
	       "\x48\x83\xec\x08\x48\x8b\x05\x25\x05\x20\x00\x48\x85\xc0\x74\x05" 
	       "\xe8\x43\x00\x00\x00\x48\x83\xc4\x08\xc3" ,
	       26);

	/* Section Body 12 (.plt) */
	memcpy(elf.section_body12 , 
	       "\xff\x35\x12\x05\x20\x00\xff\x25\x14\x05\x20\x00\x0f\x1f\x40\x00" 
	       "\xff\x25\x12\x05\x20\x00\x68\x00\x00\x00\x00\xe9\xe0\xff\xff\xff" 
	       "\xff\x25\x0a\x05\x20\x00\x68\x01\x00\x00\x00\xe9\xd0\xff\xff\xff" 
	       "\xff\x25\x02\x05\x20\x00\x68\x02\x00\x00\x00\xe9\xc0\xff\xff\xff" ,
	       64);

	/* Section Body 13 (.text) */
	memcpy(elf.section_body13 , 
	       "\x31\xed\x49\x89\xd1\x5e\x48\x89\xe2\x48\x83\xe4\xf0\x50\x54\x49" 
	       "\xc7\xc0\xa0\x05\x40\x00\x48\xc7\xc1\x30\x05\x40\x00\x48\xc7\xc7" 
	       "\x06\x05\x40\x00\xe8\xb7\xff\xff\xff\xf4\x66\x0f\x1f\x44\x00\x00" 
	       "\xb8\x27\x09\x60\x00\x55\x48\x2d\x20\x09\x60\x00\x48\x83\xf8\x0e" 
	       "\x48\x89\xe5\x76\x1b\xb8\x00\x00\x00\x00\x48\x85\xc0\x74\x11\x5d" 
	       "\xbf\x20\x09\x60\x00\xff\xe0\x66\x0f\x1f\x84\x00\x00\x00\x00\x00" 
	       "\x5d\xc3\x66\x66\x66\x66\x66\x2e\x0f\x1f\x84\x00\x00\x00\x00\x00" 
	       "\xbe\x20\x09\x60\x00\x55\x48\x81\xee\x20\x09\x60\x00\x48\xc1\xfe" 
	       "\x03\x48\x89\xe5\x48\x89\xf0\x48\xc1\xe8\x3f\x48\x01\xc6\x48\xd1" 
	       "\xfe\x74\x15\xb8\x00\x00\x00\x00\x48\x85\xc0\x74\x0b\x5d\xbf\x20" 
	       "\x09\x60\x00\xff\xe0\x0f\x1f\x00\x5d\xc3\x66\x0f\x1f\x44\x00\x00" 
	       "\x80\x3d\x59\x04\x20\x00\x00\x75\x11\x55\x48\x89\xe5\xe8\x6e\xff" 
	       "\xff\xff\x5d\xc6\x05\x46\x04\x20\x00\x01\xf3\xc3\x0f\x1f\x40\x00" 
	       "\xbf\x00\x07\x60\x00\x48\x83\x3f\x00\x75\x05\xeb\x93\x0f\x1f\x00" 
	       "\xb8\x00\x00\x00\x00\x48\x85\xc0\x74\xf1\x55\x48\x89\xe5\xff\xd0" 
	       "\x5d\xe9\x7a\xff\xff\xff\x55\x48\x89\xe5\x48\x83\xec\x10\x89\x7d" 
	       "\xfc\x48\x89\x75\xf0\xbf\xb4\x05\x40\x00\xe8\xc1\xfe\xff\xff\xb8" 
	       "\x00\x00\x00\x00\xc9\xc3\x66\x2e\x0f\x1f\x84\x00\x00\x00\x00\x00" 
	       "\x41\x57\x41\x89\xff\x41\x56\x49\x89\xf6\x41\x55\x49\x89\xd5\x41" 
	       "\x54\x4c\x8d\x25\xa8\x01\x20\x00\x55\x48\x8d\x2d\xa8\x01\x20\x00" 
	       "\x53\x4c\x29\xe5\x31\xdb\x48\xc1\xfd\x03\x48\x83\xec\x08\xe8\x45" 
	       "\xfe\xff\xff\x48\x85\xed\x74\x1e\x0f\x1f\x84\x00\x00\x00\x00\x00" 
	       "\x4c\x89\xea\x4c\x89\xf6\x44\x89\xff\x41\xff\x14\xdc\x48\x83\xc3" 
	       "\x01\x48\x39\xeb\x75\xea\x48\x83\xc4\x08\x5b\x5d\x41\x5c\x41\x5d" 
	       "\x41\x5e\x41\x5f\xc3\x66\x66\x2e\x0f\x1f\x84\x00\x00\x00\x00\x00" 
	       "\xf3\xc3" ,
	       402);

	/* Section Body 14 (.fini) */
	memcpy(elf.section_body14 , 
	       "\x48\x83\xec\x08\x48\x83\xc4\x08\xc3" ,
	       9);

	/* Section Body 15 (.rodata) */
	memcpy(elf.section_body15 , 
	       "\x01\x00\x02\x00\x48\x65\x6c\x6c\x6f\x20\x77\x6f\x72\x6c\x64\x21" 
	       "\x00" ,
	       17);

	/* Section Body 16 (.eh_frame_hdr) */
	memcpy(elf.section_body16 , 
	       "\x01\x1b\x03\x3b\x30\x00\x00\x00\x05\x00\x00\x00\x0c\xfe\xff\xff" 
	       "\x7c\x00\x00\x00\x4c\xfe\xff\xff\x4c\x00\x00\x00\x42\xff\xff\xff" 
	       "\xa4\x00\x00\x00\x6c\xff\xff\xff\xc4\x00\x00\x00\xdc\xff\xff\xff" 
	       "\x0c\x01\x00\x00" ,
	       52);

	/* Section Body 17 (.eh_frame) */
	memcpy(elf.section_body17 , 
	       "\x14\x00\x00\x00\x00\x00\x00\x00\x01\x7a\x52\x00\x01\x78\x10\x01" 
	       "\x1b\x0c\x07\x08\x90\x01\x07\x10\x14\x00\x00\x00\x1c\x00\x00\x00" 
	       "\xf8\xfd\xff\xff\x2a\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\x14\x00\x00\x00\x00\x00\x00\x00\x01\x7a\x52\x00\x01\x78\x10\x01" 
	       "\x1b\x0c\x07\x08\x90\x01\x00\x00\x24\x00\x00\x00\x1c\x00\x00\x00" 
	       "\x88\xfd\xff\xff\x40\x00\x00\x00\x00\x0e\x10\x46\x0e\x18\x4a\x0f" 
	       "\x0b\x77\x08\x80\x00\x3f\x1a\x3b\x2a\x33\x24\x22\x00\x00\x00\x00" 
	       "\x1c\x00\x00\x00\x44\x00\x00\x00\x96\xfe\xff\xff\x20\x00\x00\x00" 
	       "\x00\x41\x0e\x10\x86\x02\x43\x0d\x06\x5b\x0c\x07\x08\x00\x00\x00" 
	       "\x44\x00\x00\x00\x64\x00\x00\x00\xa0\xfe\xff\xff\x65\x00\x00\x00" 
	       "\x00\x42\x0e\x10\x8f\x02\x45\x0e\x18\x8e\x03\x45\x0e\x20\x8d\x04" 
	       "\x45\x0e\x28\x8c\x05\x48\x0e\x30\x86\x06\x48\x0e\x38\x83\x07\x4d" 
	       "\x0e\x40\x6c\x0e\x38\x41\x0e\x30\x41\x0e\x28\x42\x0e\x20\x42\x0e" 
	       "\x18\x42\x0e\x10\x42\x0e\x08\x00\x14\x00\x00\x00\xac\x00\x00\x00" 
	       "\xc8\xfe\xff\xff\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00" ,
	       244);

	/* Section Body 18 (.init_array) */
	memcpy(elf.section_body18 , 
	       "\xe0\x04\x40\x00\x00\x00\x00\x00" ,
	       8);

	/* Section Body 19 (.fini_array) */
	memcpy(elf.section_body19 , 
	       "\xc0\x04\x40\x00\x00\x00\x00\x00" ,
	       8);

	/* Section Body 20 (.jcr) */
	memcpy(elf.section_body20 , 
	       "\x00\x00\x00\x00\x00\x00\x00\x00" ,
	       8);

	/* Section Body 21 (.dynamic) */
	memcpy(elf.section_body21 , 
	       "\x01\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00" 
	       "\x0c\x00\x00\x00\x00\x00\x00\x00\xa8\x03\x40\x00\x00\x00\x00\x00" 
	       "\x0d\x00\x00\x00\x00\x00\x00\x00\xa4\x05\x40\x00\x00\x00\x00\x00" 
	       "\x19\x00\x00\x00\x00\x00\x00\x00\xf0\x06\x60\x00\x00\x00\x00\x00" 
	       "\x1b\x00\x00\x00\x00\x00\x00\x00\x08\x00\x00\x00\x00\x00\x00\x00" 
	       "\x1a\x00\x00\x00\x00\x00\x00\x00\xf8\x06\x60\x00\x00\x00\x00\x00" 
	       "\x1c\x00\x00\x00\x00\x00\x00\x00\x08\x00\x00\x00\x00\x00\x00\x00" 
	       "\xf5\xfe\xff\x6f\x00\x00\x00\x00\x60\x02\x40\x00\x00\x00\x00\x00" 
	       "\x05\x00\x00\x00\x00\x00\x00\x00\xe0\x02\x40\x00\x00\x00\x00\x00" 
	       "\x06\x00\x00\x00\x00\x00\x00\x00\x80\x02\x40\x00\x00\x00\x00\x00" 
	       "\x0a\x00\x00\x00\x00\x00\x00\x00\x3d\x00\x00\x00\x00\x00\x00\x00" 
	       "\x0b\x00\x00\x00\x00\x00\x00\x00\x18\x00\x00\x00\x00\x00\x00\x00" 
	       "\x15\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\x03\x00\x00\x00\x00\x00\x00\x00\xe0\x08\x60\x00\x00\x00\x00\x00" 
	       "\x02\x00\x00\x00\x00\x00\x00\x00\x48\x00\x00\x00\x00\x00\x00\x00" 
	       "\x14\x00\x00\x00\x00\x00\x00\x00\x07\x00\x00\x00\x00\x00\x00\x00" 
	       "\x17\x00\x00\x00\x00\x00\x00\x00\x60\x03\x40\x00\x00\x00\x00\x00" 
	       "\x07\x00\x00\x00\x00\x00\x00\x00\x48\x03\x40\x00\x00\x00\x00\x00" 
	       "\x08\x00\x00\x00\x00\x00\x00\x00\x18\x00\x00\x00\x00\x00\x00\x00" 
	       "\x09\x00\x00\x00\x00\x00\x00\x00\x18\x00\x00\x00\x00\x00\x00\x00" 
	       "\xfe\xff\xff\x6f\x00\x00\x00\x00\x28\x03\x40\x00\x00\x00\x00\x00" 
	       "\xff\xff\xff\x6f\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00" 
	       "\xf0\xff\xff\x6f\x00\x00\x00\x00\x1e\x03\x40\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" ,
	       464);

	/* Section Body 22 (.got) */
	memcpy(elf.section_body22 , 
	       "\x00\x00\x00\x00\x00\x00\x00\x00" ,
	       8);

	/* Section Body 23 (.got.plt) */
	memcpy(elf.section_body23 , 
	       "\x08\x07\x60\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\xe6\x03\x40\x00\x00\x00\x00\x00" 
	       "\xf6\x03\x40\x00\x00\x00\x00\x00\x06\x04\x40\x00\x00\x00\x00\x00" ,
	       48);

	/* Section Body 24 (.data) */
	memcpy(elf.section_body24 , 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" ,
	       16);

	/* Section Body 25 (.bss) */
	memcpy(elf.section_body25 , 
	       "\x47\x43\x43\x3a\x20\x28\x44\x65" ,
	       8);

	/* Section Body 26 (.comment) */
	memcpy(elf.section_body26 , 
	       "\x47\x43\x43\x3a\x20\x28\x44\x65\x62\x69\x61\x6e\x20\x34\x2e\x39" 
	       "\x2e\x32\x2d\x31\x30\x29\x20\x34\x2e\x39\x2e\x32\x00\x47\x43\x43" 
	       "\x3a\x20\x28\x44\x65\x62\x69\x61\x6e\x20\x34\x2e\x38\x2e\x34\x2d" 
	       "\x31\x29\x20\x34\x2e\x38\x2e\x34\x00" ,
	       57);

	/* Section Body 27 (.shstrtab) */
	memcpy(elf.section_body27 , 
	       "\x00\x2e\x73\x79\x6d\x74\x61\x62\x00\x2e\x73\x74\x72\x74\x61\x62" 
	       "\x00\x2e\x73\x68\x73\x74\x72\x74\x61\x62\x00\x2e\x69\x6e\x74\x65" 
	       "\x72\x70\x00\x2e\x6e\x6f\x74\x65\x2e\x41\x42\x49\x2d\x74\x61\x67" 
	       "\x00\x2e\x6e\x6f\x74\x65\x2e\x67\x6e\x75\x2e\x62\x75\x69\x6c\x64" 
	       "\x2d\x69\x64\x00\x2e\x67\x6e\x75\x2e\x68\x61\x73\x68\x00\x2e\x64" 
	       "\x79\x6e\x73\x79\x6d\x00\x2e\x64\x79\x6e\x73\x74\x72\x00\x2e\x67" 
	       "\x6e\x75\x2e\x76\x65\x72\x73\x69\x6f\x6e\x00\x2e\x67\x6e\x75\x2e" 
	       "\x76\x65\x72\x73\x69\x6f\x6e\x5f\x72\x00\x2e\x72\x65\x6c\x61\x2e" 
	       "\x64\x79\x6e\x00\x2e\x72\x65\x6c\x61\x2e\x70\x6c\x74\x00\x2e\x69" 
	       "\x6e\x69\x74\x00\x2e\x74\x65\x78\x74\x00\x2e\x66\x69\x6e\x69\x00" 
	       "\x2e\x72\x6f\x64\x61\x74\x61\x00\x2e\x65\x68\x5f\x66\x72\x61\x6d" 
	       "\x65\x5f\x68\x64\x72\x00\x2e\x65\x68\x5f\x66\x72\x61\x6d\x65\x00" 
	       "\x2e\x69\x6e\x69\x74\x5f\x61\x72\x72\x61\x79\x00\x2e\x66\x69\x6e" 
	       "\x69\x5f\x61\x72\x72\x61\x79\x00\x2e\x6a\x63\x72\x00\x2e\x64\x79" 
	       "\x6e\x61\x6d\x69\x63\x00\x2e\x67\x6f\x74\x00\x2e\x67\x6f\x74\x2e" 
	       "\x70\x6c\x74\x00\x2e\x64\x61\x74\x61\x00\x2e\x62\x73\x73\x00\x2e" 
	       "\x63\x6f\x6d\x6d\x65\x6e\x74\x00" ,
	       264);

	/* Section Body 28 (.symtab) */
	memcpy(elf.section_body28 , 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x03\x00\x01\x00" 
	       "\x00\x02\x40\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x03\x00\x02\x00\x1c\x02\x40\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x03\x00\x03\x00" 
	       "\x3c\x02\x40\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x03\x00\x04\x00\x60\x02\x40\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x03\x00\x05\x00" 
	       "\x80\x02\x40\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x03\x00\x06\x00\xe0\x02\x40\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x03\x00\x07\x00" 
	       "\x1e\x03\x40\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x03\x00\x08\x00\x28\x03\x40\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x03\x00\x09\x00" 
	       "\x48\x03\x40\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x03\x00\x0a\x00\x60\x03\x40\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x03\x00\x0b\x00" 
	       "\xa8\x03\x40\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x03\x00\x0c\x00\xd0\x03\x40\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x03\x00\x0d\x00" 
	       "\x10\x04\x40\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x03\x00\x0e\x00\xa4\x05\x40\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x03\x00\x0f\x00" 
	       "\xb0\x05\x40\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x03\x00\x10\x00\xc4\x05\x40\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x03\x00\x11\x00" 
	       "\xf8\x05\x40\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x03\x00\x12\x00\xf0\x06\x60\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x03\x00\x13\x00" 
	       "\xf8\x06\x60\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x03\x00\x14\x00\x00\x07\x60\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x03\x00\x15\x00" 
	       "\x08\x07\x60\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x03\x00\x16\x00\xd8\x08\x60\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x03\x00\x17\x00" 
	       "\xe0\x08\x60\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x03\x00\x18\x00\x10\x09\x60\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x03\x00\x19\x00" 
	       "\x20\x09\x60\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x03\x00\x1a\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x04\x00\xf1\xff" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\x0c\x00\x00\x00\x01\x00\x14\x00\x00\x07\x60\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\x19\x00\x00\x00\x02\x00\x0d\x00" 
	       "\x40\x04\x40\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\x2e\x00\x00\x00\x02\x00\x0d\x00\x80\x04\x40\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\x41\x00\x00\x00\x02\x00\x0d\x00" 
	       "\xc0\x04\x40\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\x57\x00\x00\x00\x01\x00\x19\x00\x20\x09\x60\x00\x00\x00\x00\x00" 
	       "\x01\x00\x00\x00\x00\x00\x00\x00\x66\x00\x00\x00\x01\x00\x13\x00" 
	       "\xf8\x06\x60\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\x8d\x00\x00\x00\x02\x00\x0d\x00\xe0\x04\x40\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\x99\x00\x00\x00\x01\x00\x12\x00" 
	       "\xf0\x06\x60\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\xb8\x00\x00\x00\x04\x00\xf1\xff\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x04\x00\xf1\xff" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\xc0\x00\x00\x00\x01\x00\x11\x00\xe8\x06\x40\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\xce\x00\x00\x00\x01\x00\x14\x00" 
	       "\x00\x07\x60\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x04\x00\xf1\xff\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\xda\x00\x00\x00\x00\x00\x12\x00" 
	       "\xf8\x06\x60\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\xeb\x00\x00\x00\x01\x00\x15\x00\x08\x07\x60\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\xf4\x00\x00\x00\x00\x00\x12\x00" 
	       "\xf0\x06\x60\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\x07\x01\x00\x00\x01\x00\x17\x00\xe0\x08\x60\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\x1d\x01\x00\x00\x12\x00\x0d\x00" 
	       "\xa0\x05\x40\x00\x00\x00\x00\x00\x02\x00\x00\x00\x00\x00\x00\x00" 
	       "\x2d\x01\x00\x00\x20\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\x49\x01\x00\x00\x20\x00\x18\x00" 
	       "\x10\x09\x60\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\x54\x01\x00\x00\x12\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\x66\x01\x00\x00\x10\x00\x18\x00" 
	       "\x20\x09\x60\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\x6d\x01\x00\x00\x12\x00\x0e\x00\xa4\x05\x40\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\x73\x01\x00\x00\x12\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\x92\x01\x00\x00\x10\x00\x18\x00\x10\x09\x60\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\x9f\x01\x00\x00\x20\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\xae\x01\x00\x00\x11\x02\x18\x00\x18\x09\x60\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\xbb\x01\x00\x00\x11\x00\x0f\x00" 
	       "\xb0\x05\x40\x00\x00\x00\x00\x00\x04\x00\x00\x00\x00\x00\x00\x00" 
	       "\xca\x01\x00\x00\x12\x00\x0d\x00\x30\x05\x40\x00\x00\x00\x00\x00" 
	       "\x65\x00\x00\x00\x00\x00\x00\x00\xda\x01\x00\x00\x10\x00\x19\x00" 
	       "\x28\x09\x60\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\xdf\x01\x00\x00\x12\x00\x0d\x00\x10\x04\x40\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\xe6\x01\x00\x00\x10\x00\x19\x00" 
	       "\x20\x09\x60\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\xf2\x01\x00\x00\x12\x00\x0d\x00\x06\x05\x40\x00\x00\x00\x00\x00" 
	       "\x20\x00\x00\x00\x00\x00\x00\x00\xf7\x01\x00\x00\x20\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\x0b\x02\x00\x00\x11\x02\x18\x00\x20\x09\x60\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\x17\x02\x00\x00\x20\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" 
	       "\x31\x02\x00\x00\x12\x00\x0b\x00\xa8\x03\x40\x00\x00\x00\x00\x00" 
	       "\x00\x00\x00\x00\x00\x00\x00\x00" ,
	       1560);

	/* Section Body 29 (.strtab) */
	memcpy(elf.section_body29 , 
	       "\x00\x63\x72\x74\x73\x74\x75\x66\x66\x2e\x63\x00\x5f\x5f\x4a\x43" 
	       "\x52\x5f\x4c\x49\x53\x54\x5f\x5f\x00\x64\x65\x72\x65\x67\x69\x73" 
	       "\x74\x65\x72\x5f\x74\x6d\x5f\x63\x6c\x6f\x6e\x65\x73\x00\x72\x65" 
	       "\x67\x69\x73\x74\x65\x72\x5f\x74\x6d\x5f\x63\x6c\x6f\x6e\x65\x73" 
	       "\x00\x5f\x5f\x64\x6f\x5f\x67\x6c\x6f\x62\x61\x6c\x5f\x64\x74\x6f" 
	       "\x72\x73\x5f\x61\x75\x78\x00\x63\x6f\x6d\x70\x6c\x65\x74\x65\x64" 
	       "\x2e\x36\x36\x36\x31\x00\x5f\x5f\x64\x6f\x5f\x67\x6c\x6f\x62\x61" 
	       "\x6c\x5f\x64\x74\x6f\x72\x73\x5f\x61\x75\x78\x5f\x66\x69\x6e\x69" 
	       "\x5f\x61\x72\x72\x61\x79\x5f\x65\x6e\x74\x72\x79\x00\x66\x72\x61" 
	       "\x6d\x65\x5f\x64\x75\x6d\x6d\x79\x00\x5f\x5f\x66\x72\x61\x6d\x65" 
	       "\x5f\x64\x75\x6d\x6d\x79\x5f\x69\x6e\x69\x74\x5f\x61\x72\x72\x61" 
	       "\x79\x5f\x65\x6e\x74\x72\x79\x00\x68\x65\x6c\x6c\x6f\x2e\x63\x00" 
	       "\x5f\x5f\x46\x52\x41\x4d\x45\x5f\x45\x4e\x44\x5f\x5f\x00\x5f\x5f" 
	       "\x4a\x43\x52\x5f\x45\x4e\x44\x5f\x5f\x00\x5f\x5f\x69\x6e\x69\x74" 
	       "\x5f\x61\x72\x72\x61\x79\x5f\x65\x6e\x64\x00\x5f\x44\x59\x4e\x41" 
	       "\x4d\x49\x43\x00\x5f\x5f\x69\x6e\x69\x74\x5f\x61\x72\x72\x61\x79" 
	       "\x5f\x73\x74\x61\x72\x74\x00\x5f\x47\x4c\x4f\x42\x41\x4c\x5f\x4f" 
	       "\x46\x46\x53\x45\x54\x5f\x54\x41\x42\x4c\x45\x5f\x00\x5f\x5f\x6c" 
	       "\x69\x62\x63\x5f\x63\x73\x75\x5f\x66\x69\x6e\x69\x00\x5f\x49\x54" 
	       "\x4d\x5f\x64\x65\x72\x65\x67\x69\x73\x74\x65\x72\x54\x4d\x43\x6c" 
	       "\x6f\x6e\x65\x54\x61\x62\x6c\x65\x00\x64\x61\x74\x61\x5f\x73\x74" 
	       "\x61\x72\x74\x00\x70\x75\x74\x73\x40\x40\x47\x4c\x49\x42\x43\x5f" 
	       "\x32\x2e\x32\x2e\x35\x00\x5f\x65\x64\x61\x74\x61\x00\x5f\x66\x69" 
	       "\x6e\x69\x00\x5f\x5f\x6c\x69\x62\x63\x5f\x73\x74\x61\x72\x74\x5f" 
	       "\x6d\x61\x69\x6e\x40\x40\x47\x4c\x49\x42\x43\x5f\x32\x2e\x32\x2e" 
	       "\x35\x00\x5f\x5f\x64\x61\x74\x61\x5f\x73\x74\x61\x72\x74\x00\x5f" 
	       "\x5f\x67\x6d\x6f\x6e\x5f\x73\x74\x61\x72\x74\x5f\x5f\x00\x5f\x5f" 
	       "\x64\x73\x6f\x5f\x68\x61\x6e\x64\x6c\x65\x00\x5f\x49\x4f\x5f\x73" 
	       "\x74\x64\x69\x6e\x5f\x75\x73\x65\x64\x00\x5f\x5f\x6c\x69\x62\x63" 
	       "\x5f\x63\x73\x75\x5f\x69\x6e\x69\x74\x00\x5f\x65\x6e\x64\x00\x5f" 
	       "\x73\x74\x61\x72\x74\x00\x5f\x5f\x62\x73\x73\x5f\x73\x74\x61\x72" 
	       "\x74\x00\x6d\x61\x69\x6e\x00\x5f\x4a\x76\x5f\x52\x65\x67\x69\x73" 
	       "\x74\x65\x72\x43\x6c\x61\x73\x73\x65\x73\x00\x5f\x5f\x54\x4d\x43" 
	       "\x5f\x45\x4e\x44\x5f\x5f\x00\x5f\x49\x54\x4d\x5f\x72\x65\x67\x69" 
	       "\x73\x74\x65\x72\x54\x4d\x43\x6c\x6f\x6e\x65\x54\x61\x62\x6c\x65" 
	       "\x00\x5f\x69\x6e\x69\x74\x00" ,
	       567);

	
}

void x()
{
	/* Program Header 0 */
	elf.program_header0.p_memsz = 448;
	elf.program_header0.p_flags = 5;
	elf.program_header0.p_offset = 64;
	elf.program_header0.p_type = PT_PHDR;
	elf.program_header0.p_align = 8;
	elf.program_header0.p_paddr = 4194368;
	elf.program_header0.p_filesz = 448;
	elf.program_header0.p_vaddr = 4194368;

	/* Program Header 1 */
	elf.program_header1.p_memsz = 28;
	elf.program_header1.p_flags = 4;
	elf.program_header1.p_offset = 512;
	elf.program_header1.p_type = PT_INTERP;
	elf.program_header1.p_align = 1;
	elf.program_header1.p_paddr = 4194816;
	elf.program_header1.p_filesz = 28;
	elf.program_header1.p_vaddr = 4194816;

	/* Program Header 2 */
	elf.program_header2.p_memsz = 1772;
	elf.program_header2.p_flags = 5;
	elf.program_header2.p_offset = 0;
	elf.program_header2.p_type = PT_LOAD;
	elf.program_header2.p_align = 2097152;
	elf.program_header2.p_paddr = 4194304;
	elf.program_header2.p_filesz = 1772;
	elf.program_header2.p_vaddr = 4194304;

	/* Program Header 3 */
	elf.program_header3.p_memsz = 568;
	elf.program_header3.p_flags = 6;
	elf.program_header3.p_offset = 1776;
	elf.program_header3.p_type = PT_LOAD;
	elf.program_header3.p_align = 2097152;
	elf.program_header3.p_paddr = 6293232;
	elf.program_header3.p_filesz = 560;
	elf.program_header3.p_vaddr = 6293232;

	/* Program Header 4 */
	elf.program_header4.p_memsz = 464;
	elf.program_header4.p_flags = 6;
	elf.program_header4.p_offset = 1800;
	elf.program_header4.p_type = PT_DYNAMIC;
	elf.program_header4.p_align = 8;
	elf.program_header4.p_paddr = 6293256;
	elf.program_header4.p_filesz = 464;
	elf.program_header4.p_vaddr = 6293256;

	/* Program Header 5 */
	elf.program_header5.p_memsz = 68;
	elf.program_header5.p_flags = 4;
	elf.program_header5.p_offset = 540;
	elf.program_header5.p_type = PT_NOTE;
	elf.program_header5.p_align = 4;
	elf.program_header5.p_paddr = 4194844;
	elf.program_header5.p_filesz = 68;
	elf.program_header5.p_vaddr = 4194844;

	/* Program Header 6 */
	elf.program_header6.p_memsz = 52;
	elf.program_header6.p_flags = 4;
	elf.program_header6.p_offset = 1476;
	elf.program_header6.p_type = PT_GNU_EH_FRAME;
	elf.program_header6.p_align = 4;
	elf.program_header6.p_paddr = 4195780;
	elf.program_header6.p_filesz = 52;
	elf.program_header6.p_vaddr = 4195780;

	/* Program Header 7 */
	elf.program_header7.p_memsz = 0;
	elf.program_header7.p_flags = 6;
	elf.program_header7.p_offset = 0;
	elf.program_header7.p_type = PT_GNU_STACK;
	elf.program_header7.p_align = 16;
	elf.program_header7.p_paddr = 0;
	elf.program_header7.p_filesz = 0;
	elf.program_header7.p_vaddr = 0;

}
int main(int argc, char *argv[])
{
	/* Write Out Elf */
	FILE *fp = fopen("elf.out", "w");
	if (!fp) {
		fprintf(stderr, "Can not open elf.out to write\n");
		return 1;
	}
	fwrite((void*)&elf, 1, sizeof(elf), fp);
	fclose(fp);

	return 0;
}