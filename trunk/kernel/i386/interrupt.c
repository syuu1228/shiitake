#include <i386/interrupt.h>
#include <i386/segment.h>
#include <i386/cpu.h>
#include <lib/console.h>

#define I8259A_MASTER_REG0 0x20
#define I8259A_MASTER_REG1 0x21

#define I8259A_SLAVE_REG0 0xa0
#define I8259A_SLAVE_REG1 0xa15

#define I8259A_CASCADE_IR 0x2
#define I8259A_INT_ADDR 0x20

#define I8259A_ICW1_ADDR(x) (x & 0xe0)
#define I8259A_ICW1 0x10
#define I8259A_ICW1_LTIM 0x8
#define I8259A_ICW1_ADI 0x4
#define I8259A_ICW1_SNGL 0x2
#define I8259A_ICW1_IC4 0x1

#define I8259A_ICW2_ADDR(x) ((x) & 0xf8)

#define I8259A_ICW3_MASTER_IR(x) (1U << x)
#define I8259A_ICW3_SLAVE_IR(x) (x)

#define I8259A_ICW4_SFNM 0x10
#define I8259A_ICW4_MASTER_BUFFER 0xc
#define I8259A_ICW4_SLAVE_BUFFER 0x8
#define I8259A_ICW4_AEOI 0x2
#define I8259A_ICW4_PM 0x1

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

static void
i8259a_init(void)
{
	/* mask all interrupts */
	ioport_write8(I8259A_MASTER_REG1,
		      0xff);
	ioport_write8(I8259A_SLAVE_REG1,
		      0xff);

	/* addr = 0, edge trigger, interval = 8, cascade connected */
	ioport_write8(I8259A_MASTER_REG0,
		      I8259A_ICW1 | I8259A_ICW1_IC4);

	/* interrupt vector = 20h */
	ioport_write8(I8259A_MASTER_REG1,
		      I8259A_ICW2_ADDR(I8259A_INT_ADDR + 0x0));

	/* master ir2 connected to slave */
	ioport_write8(I8259A_MASTER_REG1,
		      I8259A_ICW3_MASTER_IR(I8259A_CASCADE_IR));

	/* normal nest, non buffer, normal eoi, 8086 mode */
	ioport_write8(I8259A_MASTER_REG1,
		      I8259A_ICW4_PM);

	/* addr = 0, edge trigger, interval = 8, cascade connected */
	ioport_write8(I8259A_SLAVE_REG0,
		      I8259A_ICW1 | I8259A_ICW1_IC4);

	/* interrupt vector = 28h */
	ioport_write8(I8259A_SLAVE_REG1,
		      I8259A_ICW2_ADDR(I8259A_INT_ADDR + 8));

	/* slave connected to master ir2 */
	ioport_write8(I8259A_SLAVE_REG1,
		      I8259A_ICW3_SLAVE_IR(I8259A_CASCADE_IR)); /* XXX 0x02? */

	/* normal nest, non buffer, normal eoi, 8086 mode */
	ioport_write8(I8259A_SLAVE_REG1,
		      I8259A_ICW4_PM);
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
	i8259a_init();
	interrupt_enable();
}

