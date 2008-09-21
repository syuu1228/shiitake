#ifndef TASK_H
#define TASK_H

#include <types.h>
#include <cpu.h>

struct tss {
	uint16_t previous_task;
	uint16_t __unused1;
	uint32_t esp0;
	uint16_t ss0;
	uint16_t __unused2;
	uint32_t esp1;
	uint16_t ss1;
	uint16_t __unused3;
	uint32_t esp2;
	uint16_t ss2;
	uint16_t __unused4;
	uint32_t cr3;
	uint32_t eip;
	struct eflags eflags;
	uint32_t eax;
	uint32_t ecx;
	uint32_t edx;
	uint32_t ebx;
	uint32_t esp;
	uint32_t ebp;
	uint32_t esi;
	uint32_t edi;
	uint16_t es;
	uint16_t __unused5;
	uint16_t cs;
	uint16_t __unused6;
	uint16_t ss;
	uint16_t __unused7;
	uint16_t ds;
	uint16_t __unused8;
	uint16_t fs;
	uint16_t __unused9;
	uint16_t gs;
	uint16_t __unused10;
	uint16_t ldt_segment_selector;
	uint16_t __unused11;
	uint16_t t;
	uint16_t io_map_base_address;
} __attribute__ ((__packed__));

#endif
