#ifndef I386_FRAME_H_
#define I386_FRAME_H_
#include <lib/types.h>

typedef struct {
	uint32_t edi;
	uint32_t esi;
	uint32_t ebp;
	uint32_t esp;
	uint32_t ebx;
	uint32_t edx;
	uint32_t ecx;
	uint32_t eax;
	uint32_t eip;
	uint32_t eflags;
	uint32_t unused;
	uint32_t rta;
	uint32_t arg0;
	uint32_t arg1;
	uint32_t arg2;
	uint32_t arg3;
} trapframe_t;

#endif
