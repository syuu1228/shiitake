#include <types.h>
#include <cpu.h>
#include <process.h>
#include <segment.h>

#define PROCESS_TABLE_SIZE 1024

static struct process process_table[PROCESS_TABLE_SIZE] = {{0}};

static inline void
tr_load(uint16_t selector)
{
	asm volatile("ltr %0" : : "r" (selector));
}

void process_init(void)
{
	/* set process 0 descriptor */
	gdt_set_tss(0x100, &process_table[0], TSS_TYPE_NORMAL,
		    TSS_PRIVILEGE_LEVEL_KERNEL, TSS_PRESENT,
		    TSS_GRANULARITY_ENABLE);

	gdt_dump();

	tr_load(0x100);
}

