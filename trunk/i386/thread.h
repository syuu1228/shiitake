#ifndef I386_THREAD_H_
#define I386_THREAD_H_
#include <lib/types.h>
typedef struct {
	uint32_t previous_task;
	uint32_t esp0;
	uint32_t ss0;
	uint32_t esp1;
	uint32_t ss1;
	uint32_t esp2;
	uint32_t ss2;
	uint32_t cr3;
	uint32_t eip;
	uint32_t eflags;
	uint32_t eax;
	uint32_t ecx;
	uint32_t edx;
	uint32_t ebx;
	uint32_t esp;
	uint32_t ebp;
	uint32_t esi;
	uint32_t edi;
	uint32_t es;
	uint32_t cs;
	uint32_t ss;
	uint32_t ds;
	uint32_t fs;
	uint32_t gs;
	uint32_t ldt_segment_selector;
	uint16_t t;
	uint16_t io_map_base_address;
} tss_t;

typedef tss_t md_thread_t;
#endif

