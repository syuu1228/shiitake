#include <mips/config.h>
#include <mips/cpu.h>

extern void *end;

char *md_memory_head(void);
char *md_memory_tail(void);

char *
md_memory_head(void)
{
	return (char *)&end;
}

char *
md_memory_tail(void)
{
	return (char *)OFFSET_KSEG0 + MEMORY_SIZE;
}
