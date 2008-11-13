#include <i386/interrupt.h>
#include <i386/segment.h>
#include <lib/console.h>

#define IDT_SIZE 256
static descriptor_t idt[IDT_SIZE] = {{{0}}};

static inline void
idt_load(descriptor_table_register_t *idtr)
{
	asm volatile("lidt %0" :: "m"(idtr->limit));
}

static inline void
interrupt_enable(void)
{
	asm volatile("sti");
}

static void
interrupt_handler(void)
{
	printf("interrupt handled\n");
	while(1)
		;
}

void 
interrupt_init(void)
{
	descriptor_table_register_t idtr;
	int i;
	for(i = 0; i < IDT_SIZE; i++)
		set_gate_descriptor(&idt[i].gate,
				    (uint32_t)interrupt_handler,
				    GLOBAL_32BIT_CODE, 0x0,
				    GATE_TYPE_32BIT_TRAP, 0x0,
				    0x1);
	set_descriptor_table_register(&idtr, idt, IDT_SIZE);
	idt_load(&idtr);
	interrupt_enable();
}

