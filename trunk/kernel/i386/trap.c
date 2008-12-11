#include <lib/console.h>
#include <lib/types.h>
#include <i386/frame.h>

#define DPRINTF (printf("[%s:%s:%d] ", __FILE__, __FUNCTION__, __LINE__), printf)

void
trap(int vector, trapframe_t *frame);

void
trap(int vector, trapframe_t *frame)
{
	DPRINTF("\n"
		"vector:%d\n"
		"frame:%x\n"
		"eip:%x\n"
		"eax:%x ecx:%x edx:%x ebx:%x\n"
		"esp:%x ebp:%x esi:%x edi:%x\n",
		vector,
		frame,
		frame->eip,
		frame->eax, frame->ecx, frame->edx, frame->ebx,
		frame->esp, frame->ebp, frame->esi, frame->edi);
	if(vector == 48) {
		printf("syscall received\n");
	}else
		while(1)
			;
}
