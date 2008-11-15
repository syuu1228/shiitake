#include <lib/console.h>
#include <kern/memory.h>
#include <kern/thread.h>
#include <kern/file_system.h>

void thread1(void);

void thread3(void);
#ifdef MIPS
int thread2[] =
{
	0x24020001, /*        li      v0,1 */
	0x24040010, /*        li      a0,16 */
	0x24050020, /*        li      a1,32 */
	0x24060030, /*        li      a2,48 */
	0x24070040, /*        li      a3,64 */
	0x0000000c, /*        syscall */
	0x24020002, /*        li      v0,2 */
	0x24040100, /*        li      a0,256 */
	0x24050200, /*        li      a1,512 */
	0x24060300, /*        li      a2,768 */
	0x24070400, /*        li      a3,1024 */
	0x0000000c, /*        syscall */
	0x03e00008, /*        jr      ra */
	00000000    /*        nop */
};
#endif

#include <kern/elf.h>
int 
main(void)
{
	printf("starting shiitake..\n");
	size_t memory_size = memory_init();
	printf("%u byte of memory initializd.\n", memory_size);
	thread_init();
	printf("thread initialized.\n");
	file_system_init();
	printf("file system initialized.\n");
#if 0
	thread_t *t2 = thread_create((void (*)(void))thread2);
	t2->md.sr |= 16; /* user mode */
#endif
	thread3();
	elf32_header_t hdr = {0};
	int fd = open("/TESTAPP", 0, 0);
	if(fd < 0)
		panic("open failed\n");
	if(read(fd, &hdr, sizeof(hdr)) != sizeof(hdr))
		panic("read failed\n");
	
	printf("e_ident[EI_MAG0]: %c\n", hdr.e_ident[EI_MAG0]);
	printf("e_ident[EI_MAG1]: %c\n", hdr.e_ident[EI_MAG1]);
	printf("e_ident[EI_MAG2]: %c\n", hdr.e_ident[EI_MAG2]);
	printf("e_ident[EI_MAG3]: %c\n", hdr.e_ident[EI_MAG3]);
	printf("e_ident[EI_CLASS]: %x\n", hdr.e_ident[EI_CLASS]);
	printf("e_ident[EI_DATA]: %x\n", hdr.e_ident[EI_DATA]);
	printf("e_ident[EI_VERSION]: %x\n", hdr.e_ident[EI_VERSION]);
	printf("e_ident[EI_OSABI]: %x\n", hdr.e_ident[EI_OSABI]);
	printf("e_type:%x\n", hdr.e_type);
	printf("e_machine: %x\n", hdr.e_machine);
	printf("e_version: %x\n", hdr.e_version);
	printf("e_entry: %x\n", hdr.e_entry);
	printf("e_phoff: %x\n", hdr.e_phoff);
	printf("e_shoff: %x\n", hdr.e_shoff);
	printf("e_flags: %x\n", hdr.e_flags);
	printf("e_ehsize: %x\n", hdr.e_ehsize);
	printf("e_phentsize: %x\n", hdr.e_phentsize);
	printf("e_phnum: %x\n", hdr.e_phnum);
	printf("e_shentsize: %x\n", hdr.e_shentsize);
	printf("e_shnum: %x\n", hdr.e_shnum);
	printf("e_shstrndx: %x\n\n", hdr.e_shstrndx);
	
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
			printf("ph[%d] p_type:%x ", i, ph[i].p_type);
			printf("p_offset:%x ", ph[i].p_offset);
			printf("p_vaddr:%x ", ph[i].p_vaddr);
			printf("p_paddr:%x ", ph[i].p_paddr);
			printf("p_filesz:%x ", ph[i].p_filesz);
			printf("p_memsz:%x ", ph[i].p_memsz);
			printf("p_flags:%x ", ph[i].p_flags);
			printf("p_align:%x\n", ph[i].p_align);
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
//	tapp->md.sr |= 16;
//	thread_yield();
//	thread_create(thread3);
	thread1();
	return 0;
}

void
thread1(void)
{
	int i;
	for(i = 0; i < 10; i++) {
		printf("thread1\n");
		thread_yield();
	}
}

void
thread3(void)
{
	printf("thread3\n");
	int fd = opendir("/");
	dirent *ent;
	while((ent = readdir(fd))) {
		printf("ino:%u off:%u reclen:%d type:%d name:%s\n",
		       ent->d_ino, ent->d_off, ent->d_reclen, ent->d_type, ent->d_name);
	}
	closedir(fd);
}

