#include <kern/thread.h>
#include <mips/config.h>
#include <mips/cpu.h>

void 
md_thread_create(thread_t *t, void (*function)(void))
{
	t->md.sp = (unsigned)(t->stack_area + THREAD_STACK_SIZE);
	t->md.pc = (unsigned)function;
	t->md.sr = SR_CU0 | INT_LEV4 | SR_IEo | SR_IEp | SR_IEc;
}

