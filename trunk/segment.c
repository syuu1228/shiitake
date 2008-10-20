#include <segment.h>

#define GDT_SIZE 4096

static union descriptor gdt[GDT_SIZE] = {{{0}}};

extern void
printf (const char *format, ...);

static inline void
gdt_load(struct descriptor_table_register *reg)
{
	asm volatile("lgdt %0" :: "m"(reg->limit));
}

void gdt_init(void)
{
	struct descriptor_table_register gdtr;

	/* null segment */
	gdt_set_segment(0x00, 0x0, 0x0, 0, 0, 0, 0, 0, 0);

	/* 32bit code segment */
	gdt_set_segment(0x08, 0x0, 0xfffff,
			SEGMENT_TYPE_WRITABLE | SEGMENT_TYPE_CODE,
			SEGMENT_DESCRIPTOR_TYPE_CODEDATA,
			SEGMENT_PRIVILEGE_LEVEL_KERNEL,
			SEGMENT_PRESENT,
			SEGMENT_OPERATION_SIZE_32BIT,
			SEGMENT_GRANULARITY_ENABLE);

	/* 32bit data segment */
	gdt_set_segment(0x10, 0x0, 0xfffff,
			SEGMENT_TYPE_WRITABLE | SEGMENT_TYPE_DATA,
			SEGMENT_DESCRIPTOR_TYPE_CODEDATA,
			SEGMENT_PRIVILEGE_LEVEL_KERNEL,
			SEGMENT_PRESENT,
			SEGMENT_OPERATION_SIZE_32BIT,
			SEGMENT_GRANULARITY_ENABLE);

	set_descriptor_table_register(&gdtr, gdt, GDT_SIZE);
	gdt_load(&gdtr);
}

void
gdt_dump(void)
{
	uint16_t *t = (uint16_t *)gdt;
	int i, j;
	for(i = 0; i < 33; i++) {
		if(i < 5 || i == 32)
			printf("gdt[%d] ", i);
		for(j = 0; j < 4; j++) {
			if(i < 5 || i == 32)
				printf("%x ", *t);
			t++;
		}
		if(i < 5 || i == 32)
			printf("\n");
	}
}

void 
gdt_set_segment(uint16_t selector, uint32_t base, uint32_t limit,
		uint8_t type, uint8_t descriptor_type, uint8_t privilege_level,
		uint8_t present, uint8_t operation_size, uint8_t granularity)
{
	struct segment_descriptor *descriptor = gdt_get_segment(selector);
        descriptor->limit_l = (uint16_t)(0xffff & limit);
        descriptor->limit_h = (uint8_t)(0x0f & (limit >> 16));
        descriptor->base_l = (uint16_t)(0xffff & base);
        descriptor->base_m = (uint8_t)(0xff & (base >> 16));
        descriptor->base_h = (uint8_t)(0xff & (base >> 24));
	descriptor->type = type;
	descriptor->descriptor_type = descriptor_type;
	descriptor->privilege_level = privilege_level;
	descriptor->present = present;
	descriptor->operation_size = operation_size;
	descriptor->granularity = granularity;
}

void 
gdt_set_tss(uint16_t selector, struct process *base, uint8_t type,
	    uint8_t privilege_level, uint8_t present, uint8_t granularity)
{
	struct segment_descriptor *descriptor = gdt_get_segment(selector);
        descriptor->limit_l = (uint16_t)(0xffff & sizeof(struct process));
        descriptor->limit_h = (uint8_t)(0x0f & (sizeof(struct process) >> 16));
        descriptor->base_l = (uint16_t)(0xffff & (uint32_t)base);
        descriptor->base_m = (uint8_t)(0xff & ((uint32_t)base >> 16));
        descriptor->base_h = (uint8_t)(0xff & ((uint32_t)base >> 24));
	descriptor->type = type;
	descriptor->privilege_level = privilege_level;
	descriptor->present = present;
	descriptor->granularity = granularity;
}

struct segment_descriptor *
gdt_get_segment(uint16_t selector)
{
	return &gdt[selector >> 3].segment;
}

void 
gdt_set_gate(uint16_t selector, uint32_t offset, uint16_t segment_selector,
	     uint8_t parameter_count, uint8_t type, uint8_t privilege_level,
	     uint8_t present)
{
	struct gate_descriptor *descriptor = gdt_get_gate(selector);
	descriptor->offset_l = (uint16_t)(0xffff & offset);
	descriptor->offset_h = (uint16_t)(0xffff & (offset >> 16));
	descriptor->segment_selector = segment_selector;
	descriptor->parameter_count = parameter_count;
	descriptor->type = type;
	descriptor->privilege_level = privilege_level;
	descriptor->present = present;
}

struct gate_descriptor *
gdt_get_gate(uint16_t selector)
{
	return &gdt[selector >> 3].gate;
}

