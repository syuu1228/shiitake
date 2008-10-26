#ifndef SEGMENT_H
#define SEGMENT_H
#include <i386/thread.h>
#include <lib/types.h>

#define GLOBAL_32BIT_CODE 0x08
#define GLOBAL_32BIT_DATA 0x10
#define GLOBAL_32BIT_TSS 0x18

typedef struct {
	uint16_t limit_l;
	uint16_t base_l;
	uint8_t base_m;
	uint8_t type:4;
	uint8_t descriptor_type:1;
	uint8_t privilege_level:2;
	uint8_t present:1;
	uint8_t limit_h:4;
	uint8_t __unused1:2;
	uint8_t operation_size:1;
	uint8_t granularity:1;
	uint8_t base_h;
} __attribute__ ((__packed__)) segment_descriptor_t;

#define SEGMENT_TYPE_ACCESSED 0x1
#define SEGMENT_TYPE_READONLY 0x0
#define SEGMENT_TYPE_WRITABLE 0x2
#define SEGMENT_TYPE_EXPANDDOWN 0x4
#define SEGMENT_TYPE_DATA 0x0
#define SEGMENT_TYPE_CODE 0x8

#define SEGMENT_DESCRIPTOR_TYPE_SYSTEM 0x0
#define SEGMENT_DESCRIPTOR_TYPE_CODEDATA 0x1

#define SEGMENT_PRIVILEGE_LEVEL_KERNEL 0x0
#define SEGMENT_PRIVILEGE_LEVEL_USER 0x3

#define SEGMENT_NOT_PRESENT 0x0
#define SEGMENT_PRESENT 0x1

#define SEGMENT_OPERATION_SIZE_32BIT 0x1
#define SEGMENT_OPERATION_SIZE_16BIT 0x0

#define SEGMENT_GRANULARITY_DISABLE 0x0
#define SEGMENT_GRANULARITY_ENABLE 0x1

#define TSS_TYPE_NORMAL 0x9
#define TSS_TYPE_BUSY 0xb

#define TSS_PRIVILEGE_LEVEL_KERNEL SEGMENT_PRIVILEGE_LEVEL_KERNEL
#define TSS_PRIVILEGE_LEVEL_USER SEGMENT_PRIVILEGE_LEVEL_USER

#define TSS_NOT_PRESENT SEGMENT_NOT_PRESENT
#define TSS_PRESENT SEGMENT_PRESENT

#define TSS_GRANULARITY_DISABLE SEGMENT_GRANULARITY_DISABLE
#define TSS_GRANULARITY_ENABLE SEGMENT_GRANULARITY_ENABLE

typedef struct {
	uint16_t offset_l;
	uint16_t segment_selector;
	uint8_t parameter_count:5;
	uint8_t __unused1:3;
	uint8_t type:4;
	uint8_t __unused2:1;
	uint8_t privilege_level:2;
	uint8_t present:1;
	uint16_t offset_h;
} __attribute__ ((__packed__)) gate_descriptor_t;

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

typedef union {
	segment_descriptor_t segment;
	gate_descriptor_t gate;
} descriptor_t;

typedef struct {
	uint16_t limit;
	descriptor_t *base;
} __attribute__ ((__packed__)) descriptor_table_register_t;

inline static void
set_descriptor_table_register(descriptor_table_register_t *reg,
			      descriptor_t *descriptor_table,
			      int length)
{
	reg->base = descriptor_table;
	reg->limit = length * sizeof(descriptor_t);
}

void gdt_init(void);

void gdt_dump(void);

void 
gdt_set_segment(uint16_t selector, uint32_t base, uint32_t limit,
		uint8_t type, uint8_t descriptor_type, uint8_t privilege_level,
		uint8_t present, uint8_t operation_size, uint8_t granularity);
void 
gdt_set_tss(uint16_t selector, tss_t *base, uint8_t type,
	    uint8_t privilege_level, uint8_t present, uint8_t granularity);

segment_descriptor_t *
gdt_get_segment(uint16_t selector);

void 
gdt_set_gate(uint16_t selector, uint32_t offset, uint16_t segment_selector,
	     uint8_t stack_copy_count, uint8_t type, uint8_t privilge_level,
	     uint8_t present);

gate_descriptor_t *
gdt_get_gate(uint16_t selector);

#endif
