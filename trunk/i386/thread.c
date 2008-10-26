#include <kern/thread.h>

void 
md_thread_create(thread_t *t, void (*function)(void))
{
	t->md.esp = (uint32_t)t->stack_area + THREAD_STACK_SIZE;
	t->md.eip = (uint32_t)function;
}
