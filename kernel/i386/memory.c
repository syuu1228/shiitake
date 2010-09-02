#include <i386/multiboot.h>
#include <i386/config.h>

extern void *_end;

char *md_memory_head(void);
char *md_memory_tail(void);

char *
md_memory_head(void)
{
	return (char *)&_end;
}

char *
md_memory_tail(void)
{
/*	return (char *)(mbi->mem_upper * 1024);*/
	return (char *)(MEMORY_SIZE);
}
