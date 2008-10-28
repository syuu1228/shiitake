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
	set_segment_descriptor(gdt_get_segment_descriptor(0x00),
			       0x0, 0x0, 0, 0, 0, 0, 0, 0);

	/* 32bit code segment */
	set_segment_descriptor(gdt_get_segment_descriptor(GLOBAL_32BIT_CODE),
			       0x0, 0xfffff,
			       SEGMENT_TYPE_WRITABLE | SEGMENT_TYPE_CODE,
			       SEGMENT_DESCRIPTOR_TYPE_CODEDATA,
			       SEGMENT_PRIVILEGE_LEVEL_KERNEL,
			       SEGMENT_PRESENT,
			       SEGMENT_OPERATION_SIZE_32BIT,
			       SEGMENT_GRANULARITY_ENABLE);

	/* 32bit data segment */
	set_segment_descriptor(gdt_get_segment_descriptor(GLOBAL_32BIT_DATA),
			       0x0, 0xfffff,
			       SEGMENT_TYPE_WRITABLE | SEGMENT_TYPE_DATA,
			       SEGMENT_DESCRIPTOR_TYPE_CODEDATA,
			       SEGMENT_PRIVILEGE_LEVEL_KERNEL,
			       SEGMENT_PRESENT,
			       SEGMENT_OPERATION_SIZE_32BIT,
			       SEGMENT_GRANULARITY_ENABLE);

	/* tss descriptor */
	set_tss_descriptor(gdt_get_segment_descriptor(GLOBAL_32BIT_TSS),
			   &global_tss, TSS_TYPE_NORMAL,
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

segment_descriptor_t *
gdt_get_segment_descriptor(uint16_t selector)
{
	return &gdt[selector >> 3].segment;
}

gate_descriptor_t *
gdt_get_gate_descriptor(uint16_t selector)
{
	return &gdt[selector >> 3].gate;
}

