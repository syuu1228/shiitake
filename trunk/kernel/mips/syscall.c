#include <mips/cpu.h>
#include <mips/syscall.h>

void syscall_handle(unsigned status, unsigned cause, unsigned epc, 
		    md_thread_t *frame)
{
	printf("syscall code:%x arg0:%x arg1:%x arg2:%x arg3:%x\n",
	       frame->v0, frame->a0, frame->a1, frame->a2, frame->a3);
	if(cause & CAUSE_BD) {
		printf("delay slot unsupported in syscall\n");
		while(1)
			;
	}else
		frame->pc = epc + sizeof(int);
}
