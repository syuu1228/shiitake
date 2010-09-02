#include <kern/syscall.h>
#include <i386/syscall.h>
#include <lib/console.h>

//#define DPRINTF (printf("[%s:%s:%d] ", __FILE__, __FUNCTION__, __LINE__), printf)
#define DPRINTF(...) do{}while(0)

typedef unsigned (*syscall_func_t)(unsigned, unsigned, unsigned, unsigned);

void syscall_handle(trapframe_t *frame)
{
	DPRINTF("syscall code:%x arg0:%x arg1:%x arg2:%x arg3:%x\n",
		frame->eax, frame->arg0, frame->arg1, frame->arg2, frame->arg3);
	syscall_func_t syscall_function =
		(syscall_func_t)syscall_functions[frame->eax];
	frame->eax = 
		syscall_function(frame->arg0, frame->arg1, frame->arg2, frame->arg3);
}
