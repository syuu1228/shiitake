#include <kern/execute.h>
#include <kern/elf.h>
#include <kern/file_system.h>
#include <kern/memory.h>
#include <lib/console.h>
#include <lib/assert.h>

//#define DPRINTF (printf("[%s:%s:%d] ", __FILE__, __FUNCTION__, __LINE__), printf)
#define DPRINTF(...) do{}while(0)

void
execute(const char *path)
{
	elf32_header_t hdr = {0};
	int fd = open(path, 0, 0);
	if(fd < 0)
		panic("open failed\n");
	if(read(fd, &hdr, sizeof(hdr)) != sizeof(hdr))
		panic("read failed\n");

	DPRINTF("e_ident[EI_MAG0]: %c\n", hdr.e_ident[EI_MAG0]);
	DPRINTF("e_ident[EI_MAG1]: %c\n", hdr.e_ident[EI_MAG1]);
	DPRINTF("e_ident[EI_MAG2]: %c\n", hdr.e_ident[EI_MAG2]);
	DPRINTF("e_ident[EI_MAG3]: %c\n", hdr.e_ident[EI_MAG3]);
	DPRINTF("e_ident[EI_CLASS]: %x\n", hdr.e_ident[EI_CLASS]);
	DPRINTF("e_ident[EI_DATA]: %x\n", hdr.e_ident[EI_DATA]);
	DPRINTF("e_ident[EI_VERSION]: %x\n", hdr.e_ident[EI_VERSION]);
	DPRINTF("e_ident[EI_OSABI]: %x\n", hdr.e_ident[EI_OSABI]);
	DPRINTF("e_type:%x\n", hdr.e_type);
	DPRINTF("e_machine: %x\n", hdr.e_machine);
	DPRINTF("e_version: %x\n", hdr.e_version);
	DPRINTF("e_entry: %x\n", hdr.e_entry);
	DPRINTF("e_phoff: %x\n", hdr.e_phoff);
	DPRINTF("e_shoff: %x\n", hdr.e_shoff);
	DPRINTF("e_flags: %x\n", hdr.e_flags);
	DPRINTF("e_ehsize: %x\n", hdr.e_ehsize);
	DPRINTF("e_phentsize: %x\n", hdr.e_phentsize);
	DPRINTF("e_phnum: %x\n", hdr.e_phnum);
	DPRINTF("e_shentsize: %x\n", hdr.e_shentsize);
	DPRINTF("e_shnum: %x\n", hdr.e_shnum);
	DPRINTF("e_shstrndx: %x\n\n", hdr.e_shstrndx);
	
	assert(sizeof(elf32_program_header_t) == hdr.e_phentsize);
	assert(sizeof(elf32_section_header_t) == hdr.e_shentsize);

	if(hdr.e_phoff) {
		elf32_program_header_t ph[hdr.e_phnum];
		memset(ph, 0, sizeof(ph));
		if(lseek(fd, hdr.e_phoff, 0) < 0)
			panic("seek failed\n");
		if(read(fd, ph, sizeof(ph)) != sizeof(ph)) 
			panic("read failed\n");
		int i;
		for(i = 0; i < hdr.e_phnum; i++) {
			DPRINTF("ph[%d] p_type:%x ", i, ph[i].p_type);
			DPRINTF("p_offset:%x ", ph[i].p_offset);
			DPRINTF("p_vaddr:%x ", ph[i].p_vaddr);
			DPRINTF("p_paddr:%x ", ph[i].p_paddr);
			DPRINTF("p_filesz:%x ", ph[i].p_filesz);
			DPRINTF("p_memsz:%x ", ph[i].p_memsz);
			DPRINTF("p_flags:%x ", ph[i].p_flags);
			DPRINTF("p_align:%x\n", ph[i].p_align);
			if(ph[i].p_type == 0x1) {
				assert(ph[i].p_offset);
				assert(ph[i].p_paddr);
				assert(ph[i].p_filesz);
				assert(ph[i].p_memsz);
				unsigned char *dest =
					(unsigned char *)ph[i].p_paddr;
				memset(dest, 0, ph[i].p_memsz);
				if(lseek(fd, ph[i].p_offset, 0) < 0) 
					panic("seek failed\n");				
				if(read(fd, dest, ph[i].p_filesz) != ph[i].p_filesz)
					panic("read failed\n");
			}
		}
	}
        thread_create((void (*)(void))hdr.e_entry);
}
