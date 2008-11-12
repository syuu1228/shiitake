#include <kern/thread.h>
#include <mips/config.h>
#include <mips/cpu.h>

void 
md_thread_create(thread_t *t, void (*function)(void))
{
	t->md.sp = (unsigned)(t->stack_area + THREAD_STACK_SIZE);
	t->md.a0 = (unsigned)function;
	t->md.pc = (unsigned)md_thread_trampoline;
//	t->md.sr = SR_CU0 | INT_LEV4 | SR_IEo | SR_IEp | SR_IEc;
//	t->md.sr = SR_CU0 | SR_IEo | SR_IEp | SR_IEc;
	t->md.sr = SR_CU0;
	asm volatile("sw $gp, %0" : : "m"(t->md.gp)); /* t->md.gp = $gp */
}

