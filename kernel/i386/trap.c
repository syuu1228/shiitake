#include <lib/console.h>
#include <lib/types.h>
#include <i386/frame.h>
#include <i386/syscall.h>

//#define DPRINTF (printf("[%s:%s:%d] ", __FILE__, __FUNCTION__, __LINE__), printf)
#define DPRINTF(...) do{}while(0)

void
trap(int vector, trapframe_t *frame);

void
trap(int vector, trapframe_t *frame)
{
	if(vector == 128) {
		syscall_handle(frame);
	}else{
		printf(
			"vector:%d\n"
			"frame:%x\n"
			"eflags:%x eip:%x\n"
			"eax:%x ecx:%x edx:%x ebx:%x\n"
			"esp:%x ebp:%x esi:%x edi:%x\n",
			vector,
			frame,
			frame->eflags, frame->eip,
			frame->eax, frame->ecx, frame->edx, frame->ebx,
			frame->esp, frame->ebp, frame->esi, frame->edi);
		while(1)
			;
	}
}
