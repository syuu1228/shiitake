#include "types.h"

struct segment_descriptor {
	uint16_t limit_l;
	uint16_t base_l;
	uint8_t base_m;
	uint8_t type:4;
	uint8_t s:1;
	uint8_t dpl:2;
	uint8_t p:1;
	uint8_t limit_h:4;
	uint8_t avl:1;
	uint8_t __unused:1;
	uint8_t db:1;
	uint8_t g:1;
	uint8_t base_h;
} __attribute__ ((__packed__));

struct gate_descriptor {
	uint16_t offset_l;
	uint16_t segment_selector;
	uint8_t stack_copy_count;
	uint8_t type:3;
	uint8_t d:1;
	uint8_t dpl:2;
	uint8_t p:1;
	uint16_t offset_h;
} __attribute__ ((__packed__));

#define GATE_TYPE_16BIT_TSS 0x1
#define GATE_TYPE_LDT 0x2
#define GATE_TYPE_BUSY_16BIT_TSS 0x3
#define GATE_TYPE_16BIT_CALL 0x4
#define GATE_TYPE_TASK 0x5
#define GATE_TYPE_16BIT_INTERRUPT 0x6
#define GATE_TYPE_16BIT_TRAP 0x7 
#define GATE_TYPE_32BIT_TSS 0x9
#define GATE_TYPE_BUSY_32BIT_TSS 0xB
#define GATE_TYPE_32BIT_CALL 0xC
#define GATE_TYPE_32BIT_INTERRUPT 0xE
#define GATE_TYPE_32BIT_TRAP 0xF

struct segment_descriptor_table {
	uint16_t limit;
	void *base;
} __attribute__ ((__packed__));

inline static void get_gdtr(struct segment_descriptor_table *table)
{
	asm volatile("sgdt %0" : "=m"(table->limit));
}

inline static void set_gdtr(struct segment_descriptor_table *table)
{
	asm volatile("lgdt %0" :: "m"(table->limit));
}

inline static void get_idtr(struct segment_descriptor_table *table)
{
	asm volatile("sidt %0" : "=m"(table->limit));
}

inline static void set_idtr(struct segment_descriptor_table *table)
{
	asm volatile("lidt %0" :: "m"(table->limit));
}

inline static int get_gdt_length(struct segment_descriptor_table *table)
{
	return table->limit / sizeof(struct segment_descriptor);
}

inline static struct segment_descriptor *get_gdt_entry(struct segment_descriptor_table *table, int i)
{
	return ((struct segment_descriptor *)table->base) + i;
}

inline static void init_gate_descriptor(struct gate_descriptor *gate, uint16_t segment_selector,
					void (*function)(void), uint8_t stack_copy_count, uint8_t type,
					uint8_t d, uint8_t dpl, uint8_t p)
{
	gate->offset_l = (uint16_t)(uint32_t)function;
	gate->segment_selector = segment_selector;
	gate->stack_copy_count = stack_copy_count;
	gate->type = type;
	gate->d = d;
	gate->dpl = dpl;
	gate->p = p;
	gate->offset_h = (uint16_t)((uint32_t)function >> 16);
}
