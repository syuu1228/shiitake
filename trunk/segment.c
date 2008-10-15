#include <segment.h>
#include <types.h>

#define GDT_SIZE 4096

struct segment_descriptor {
	uint16_t limit_l;
	uint16_t base_l;
	uint8_t base_m;
	uint8_t type:4;
	uint8_t descriptor_type:1;
	uint8_t privilege_level:2;
	uint8_t present:1;
	uint8_t limit_h:4;
	uint8_t __unused1:1;
	uint8_t __unused2:1;
	uint8_t operation_size:1;
	uint8_t granularity:1;
	uint8_t base_h;
} __attribute__ ((__packed__));

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

struct gate_descriptor {
	uint16_t offset_l;
	uint16_t segment_selector;
	uint8_t stack_copy_count:5;
	uint8_t __unused1:3;
	uint8_t type:4;
	uint8_t __unused2:1;
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

union descriptor {
	struct segment_descriptor *segment;
	struct gate_descriptor *gate;
};

struct descriptor_table_register {
	uint16_t limit;
	union descriptor *base;
} __attribute__ ((__packed__));

static void
gdt_load(struct descriptor_table_register *reg);

static void
set_descriptor_table_register(struct descriptor_table_register *reg,
			      union descriptor *descriptor_table,
			      int length);

static void 
gdt_set_segment(uint16_t selector, uint32_t limit, uint32_t base,
		uint8_t type, uint8_t descriptor_type, uint8_t privilege_level,
		uint8_t present, uint8_t operation_size, uint8_t granularity);

static struct segment_descriptor *
gdt_get_segment(uint16_t selector);

/*
static struct gate_descriptor *
gdt_get_gate(uint16_t selector);
*/

static union descriptor gdt[GDT_SIZE];

static void
gdt_load(struct descriptor_table_register *reg)
{
	asm volatile("lgdt %0" :: "m"(reg->limit));
}

static void
set_descriptor_table_register(struct descriptor_table_register *reg,
			      union descriptor *descriptor_table,
			      int length)
{
	reg->base = descriptor_table;
	reg->limit = length * sizeof(union descriptor);
}

void gdt_init(void)
{
	struct descriptor_table_register gdtr;

	/* null segment */
	gdt_set_segment(0x00, 0x0, 0x0, 0, 0, 0, 0, 0, 0);
	/* 32bit code segment */
	gdt_set_segment(0x08, 0xfffff, 0x0,
			SEGMENT_TYPE_WRITABLE | SEGMENT_TYPE_CODE,
			SEGMENT_DESCRIPTOR_TYPE_CODEDATA,
			SEGMENT_PRIVILEGE_LEVEL_KERNEL,
			SEGMENT_PRESENT,
			SEGMENT_OPERATION_SIZE_32BIT,
			SEGMENT_GRANULARITY_ENABLE);

	/* 32bit data segment */
	gdt_set_segment(0x10, 0xfffff, 0x0,
			SEGMENT_TYPE_WRITABLE | SEGMENT_TYPE_DATA,
			SEGMENT_DESCRIPTOR_TYPE_CODEDATA,
			SEGMENT_PRIVILEGE_LEVEL_KERNEL,
			SEGMENT_PRESENT,
			SEGMENT_OPERATION_SIZE_32BIT,
			SEGMENT_GRANULARITY_ENABLE);

	set_descriptor_table_register(&gdtr, gdt, GDT_SIZE);
	gdt_load(&gdtr);
}

static void 
gdt_set_segment(uint16_t selector, uint32_t limit, uint32_t base,
		uint8_t type, uint8_t descriptor_type, uint8_t privilege_level,
		uint8_t present, uint8_t operation_size, uint8_t granularity)
{
	struct segment_descriptor *descriptor = gdt_get_segment(selector);
        descriptor->limit_l = (uint16_t)limit;
        descriptor->limit_h = (uint8_t)(0xf & (limit >> 16));
        descriptor->base_l = 0xffffff & base;
        descriptor->base_m = (uint8_t)(0xff & (base >> 16));
        descriptor->base_h = (uint8_t)(0xff & (base >> 24));
	descriptor->type = type;
	descriptor->descriptor_type = descriptor_type;
	descriptor->privilege_level = privilege_level;
	descriptor->present = present;
	descriptor->operation_size = operation_size;
	descriptor->granularity = granularity;
}

static struct segment_descriptor *
gdt_get_segment(uint16_t selector)
{
	return gdt[selector >> 3].segment;
}
/*
static struct gate_descriptor *
gdt_get_gate(uint16_t selector)
{
	return gdt[selector >> 3].gate;
}
*/
