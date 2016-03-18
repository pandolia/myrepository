"""Usage: python {thisfile} <elffile>"""

from elftools.elf import elffile

def ListFmt(l, fmt):
    return '\n'.join(fmt.format(i=i, el=el) for i, el in enumerate(l))

def DictFmt(d, fmt):
    return '\n'.join(fmt.format(k=k, v=v) for k, v in d.iteritems())

def str2hex(s):
    return ''.join("\\x%02x" % ord(c) for c in s)

def print_elf_layout(elf):
    print "\t/* Elf File Layout */"
    e_class = elf.header.e_ident.EI_CLASS[-2:]
    blocks = [(0, elf.header.e_ehsize, elf.header.e_ehsize,
               "Elf file header", "Elf%s_Ehdr header" % e_class)]
    
    sh_cur, sh_size = elf.header.e_shoff, elf.header.e_shentsize
    for i, section in enumerate(elf.iter_sections()):
        s_name = section.name or 'NULL'
        blocks.append((sh_cur, sh_cur+sh_size, sh_size,
                       "Section header %2d (%s)" % (i, s_name),
                       "Elf%s_Shdr section_header%d" % (e_class, i)))
        sh_cur += sh_size
        if section.header.sh_size > 0:
            blocks.append((section.header.sh_offset,
                           section.header.sh_offset+section.header.sh_size,
                           section.header.sh_size,
                           "Section body %2d (%s)" %(i, s_name),
                           "unsigned char section_body%d[%d]" % (i, section.header.sh_size)))    
    
    ph_cur, ph_size = elf.header.e_phoff, elf.header.e_phentsize
    for i, segment in enumerate(elf.iter_segments()):
        blocks.append((ph_cur, ph_cur+ph_size, ph_size,
                       "Program header %2d" % i,
                       "Elf%s_Phdr program_header%d" % (e_class, i)))
        ph_cur += ph_size
        
    blocks.sort()
    
    newblocks, cur_offs, ipad = [], 0, 0
    for block in blocks:
        begin = block[0]
        if begin > cur_offs:
            newblocks.append((cur_offs, begin, begin-cur_offs,
                              "Padding",
                              "unsigned char padding%d[%d]" % (ipad, begin-cur_offs)))
            ipad += 1
        newblocks.append(block)
        cur_offs = block[1]
    
    print "\tstruct {"    
    cur_offs = 0
    delimiter = "\t\t/* %3d->+" + "-"*37 + "+ */"
    print delimiter % cur_offs
    for block in newblocks:
        print "\t\t/* %5s| [%02d] %-30s | */ %s;" % ("", block[2], block[3], block[4])
        cur_offs = block[1]
        print delimiter % cur_offs
    print "\t} elf = {0};"

def print_header(elf):    
    e_ident = elf.header.pop('e_ident')
    e_mag = e_ident.pop('EI_MAG')
    print "\n\t/* Elf File Header */"
    print ListFmt(e_mag, "\telf.header.e_ident[EI_MAG{i}] = ELFMAG{i};")
    print DictFmt(e_ident, "\telf.header.e_ident[{k}] = {v};")
    print DictFmt(elf.header, "\telf.header.{k} = {v};")
    e_ident.EI_MAG = e_mag
    elf.header.e_ident = e_ident

def print_program_headers(elf):    
    for i, segment in enumerate(elf.iter_segments()):
        print "\n\t/* Program Header %d */" % i
        print DictFmt(segment.header, "\telf.program_header%d.{k} = {v};" % i)

def print_section_headers(elf):    
    for i, section in enumerate(elf.iter_sections()):
        s_name = section.name or "NULL"
        print "\n\t/* Section Header %d (%s) */" % (i, s_name)
        print DictFmt(section.header, "\telf.section_header%d.{k} = {v};" % i)

def print_section_bodies(elf):    
    for i, section in enumerate(elf.iter_sections()):
        if section.header.sh_size == 0:
            continue
        print "\n\t/* Section Body %d (%s) */" % (i, section.name)        
        print "\tmemcpy(elf.section_body%d ," % i ,
        data = section.data()
        for i in range(0, len(data), 16):
            print "\n\t%7s\"%s\"" % ("", str2hex(data[i:i+16])),
        print ",\n\t%7s%d);" % ("", len(data)) 

def Elf2C(elf):
    print "#include <stdio.h>"
    print "#include <string.h>"
    print "#include <linux/elf.h>"
    print "\n#define ELFOSABI_SYSV ELFOSABI_NONE"
    print "#define EI_ABIVERSION 9\n"
    print "int main(int argc, char *argv[])"
    print "{"
    
    print_elf_layout(elf)
    print_header(elf)
    print_program_headers(elf)
    print_section_headers(elf)
    print_section_bodies(elf)   
    
    print "\n\t/* Write Out Elf */"
    print "\tFILE *fp = fopen(\"elf.out\", \"w\");"
    print "\tif (!fp) {"
    print "\t\tfprintf(stderr, \"Can not open elf.out to write\\n\");"
    print "\t\treturn 1;"
    print "\t}"
    print "\tfwrite((void*)&elf, 1, sizeof(elf), fp);"
    print "\tfclose(fp);"
    print ""
    print "\treturn 0;"
    print "}"

if __name__ == "__main__":
    import sys
    if len(sys.argv) != 2:
        print __doc__.format(thisfile=sys.argv[0])
    elf = elffile.ELFFile(file(sys.argv[1]))
    Elf2C(elf)
