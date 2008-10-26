#include <i386/segment.h>

#define GDT_SIZE 4096
static descriptor_t gdt[GDT_SIZE] = {{{0}}};
static tss_t global_tss;

extern void
printf (const char *format, ...);

static inline void
gdt_load(descriptor_table_register_t *gdtr)
{
	asm volatile("lgdt %0" :: "m"(gdtr->limit));
}

static inline void
tr_load(uint16_t selector)
{
	asm volatile("ltr %0" : : "r" (selector));
}


void gdt_init(void)
{
	descriptor_table_register_t gdtr;

	/* null segment */
	gdt_set_segment(0x00, 0x0, 0x0, 0, 0, 0, 0, 0, 0);

	/* 32bit code segment */
	gdt_set_segment(GLOBAL_32BIT_CODE, 0x0, 0xfffff,
			SEGMENT_TYPE_WRITABLE | SEGMENT_TYPE_CODE,
			SEGMENT_DESCRIPTOR_TYPE_CODEDATA,
			SEGMENT_PRIVILEGE_LEVEL_KERNEL,
			SEGMENT_PRESENT,
			SEGMENT_OPERATION_SIZE_32BIT,
			SEGMENT_GRANULARITY_ENABLE);

	/* 32bit data segment */
	gdt_set_segment(GLOBAL_32BIT_DATA, 0x0, 0xfffff,
			SEGMENT_TYPE_WRITABLE | SEGMENT_TYPE_DATA,
			SEGMENT_DESCRIPTOR_TYPE_CODEDATA,
			SEGMENT_PRIVILEGE_LEVEL_KERNEL,
			SEGMENT_PRESENT,
			SEGMENT_OPERATION_SIZE_32BIT,
			SEGMENT_GRANULARITY_ENABLE);

	/* tss descriptor */
	gdt_set_tss(GLOBAL_32BIT_TSS, &global_tss, TSS_TYPE_NORMAL,
		    TSS_PRIVILEGE_LEVEL_KERNEL, TSS_PRESENT,
		    TSS_GRANULARITY_ENABLE);


	set_descriptor_table_register(&gdtr, gdt, GDT_SIZE);
	gdt_load(&gdtr);
	tr_load(GLOBAL_32BIT_TSS);
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
        segment_descriptor_t *descriptor = gdt_get_segment(selector);
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
gdt_set_tss(uint16_t selector, tss_t *base, uint8_t type,
	    uint8_t privilege_level, uint8_t present, uint8_t granularity)
{
	segment_descriptor_t *descriptor = gdt_get_segment(selector);
        descriptor->limit_l = (uint16_t)(0xffff & sizeof(tss_t));
        descriptor->limit_h = (uint8_t)(0x0f & (sizeof(tss_t) >> 16));
        descriptor->base_l = (uint16_t)(0xffff & (uint32_t)base);
        descriptor->base_m = (uint8_t)(0xff & ((uint32_t)base >> 16));
        descriptor->base_h = (uint8_t)(0xff & ((uint32_t)base >> 24));
	descriptor->type = type;
	descriptor->privilege_level = privilege_level;
	descriptor->present = present;
	descriptor->granularity = granularity;
}

segment_descriptor_t *
gdt_get_segment(uint16_t selector)
{
	return &gdt[selector >> 3].segment;
}

void 
gdt_set_gate(uint16_t selector, uint32_t offset, uint16_t segment_selector,
	     uint8_t parameter_count, uint8_t type, uint8_t privilege_level,
	     uint8_t present)
{
	gate_descriptor_t *descriptor = gdt_get_gate(selector);
	descriptor->offset_l = (uint16_t)(0xffff & offset);
	descriptor->offset_h = (uint16_t)(0xffff & (offset >> 16));
	descriptor->segment_selector = segment_selector;
	descriptor->parameter_count = parameter_count;
	descriptor->type = type;
	descriptor->privilege_level = privilege_level;
	descriptor->present = present;
}

gate_descriptor_t *
gdt_get_gate(uint16_t selector)
{
	return &gdt[selector >> 3].gate;
}

