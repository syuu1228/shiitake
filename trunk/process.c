#include <types.h>
#include <cpu.h>
#include <process.h>
#include <segment.h>

#define PROCESS_TABLE_SIZE 1024

extern void
printf (const char *format, ...);

static struct process process_table[PROCESS_TABLE_SIZE] = {{0}};

static inline void
tr_load(uint16_t selector)
{
	asm volatile("ltr %0" : : "r" (selector));
}

static inline void
switch_to(const uint16_t selector)
{
	asm volatile("ljmp %0, $0" : : "i" (selector));
}

static void
set_entry(int pid, uint16_t cs, uint16_t ds, uint16_t ss,
	  uint32_t eip, uint32_t eflags, uint32_t esp,
	  uint32_t esp0, uint16_t ss0)
{
	struct process *p = &process_table[pid];
	p->cs = cs;
	p->ds = p->es = ds;
	p->ss = ss;
	p->eip = eip;
	p->eflags = eflags;
	p->esp = esp;
	p->esp0 = esp0;
	p->ss0 = ss0;
}

static void
process1(void)
{
	int i = 0;
	while(1) {
		printf("[%d] process 1 running!\n", i++);
		switch_to(0x100);
	}
}

uint8_t process1_stack[8192];

void 
process_init(void)
{
	/* process 0 descriptor */
	gdt_set_tss(0x100, &process_table[0], TSS_TYPE_NORMAL,
		    TSS_PRIVILEGE_LEVEL_KERNEL, TSS_PRESENT,
		    TSS_GRANULARITY_ENABLE);

	/* process 1 descriptor */
	gdt_set_tss(0x108, &process_table[1], TSS_TYPE_NORMAL,
		    TSS_PRIVILEGE_LEVEL_KERNEL, TSS_PRESENT,
		    TSS_GRANULARITY_ENABLE);

	/* process 1 entry */
	set_entry(1, GLOBAL_32BIT_CODE, GLOBAL_32BIT_DATA,
		  GLOBAL_32BIT_DATA, (uint32_t)process1,
		  0, (uint32_t)process1_stack, 0, 0);
			  

	gdt_dump();

	tr_load(0x100);

	int i = 0;
	while(1) {
		printf("[%d] process 0 running!\n", i++);
		switch_to(0x108);
	}
}

