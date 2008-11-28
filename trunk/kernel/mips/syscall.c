#include <mips/cpu.h>
#include <kern/syscall.h>
#include <mips/syscall.h>

#define DPRINTF (printf("[%s:%s:%d] ", __FILE__, __FUNCTION__, __LINE__), printf)
//#define DPRINTF(...) do{}while(0)

void syscall_handle(unsigned status, unsigned cause, unsigned epc, 
		    md_thread_t *frame)
{
	DPRINTF("syscall code:%x arg0:%x arg1:%x arg2:%x arg3:%x\n",
		frame->v0, frame->a0, frame->a1, frame->a2, frame->a3);

	if(cause & CAUSE_BD)
		panic("delay slot is not supported in syscall\n");
	else
		frame->pc = epc + sizeof(int);
	syscall_invoke(frame);
}
