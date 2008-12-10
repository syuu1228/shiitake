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

#define VECTOR(no) interrupt_vector_ ## no

extern unsigned
	VECTOR(0), VECTOR(1), VECTOR(2), VECTOR(3), VECTOR(4),
	VECTOR(5), VECTOR(6), VECTOR(7), VECTOR(8), VECTOR(9),
	VECTOR(10), VECTOR(11), VECTOR(12), VECTOR(13), VECTOR(14), 
	VECTOR(15), VECTOR(16), VECTOR(17), VECTOR(18), VECTOR(19),
	VECTOR(20), VECTOR(21), VECTOR(22), VECTOR(23), VECTOR(24),
	VECTOR(25), VECTOR(26), VECTOR(27), VECTOR(28), VECTOR(29),
	VECTOR(30), VECTOR(31), VECTOR(32), VECTOR(33), VECTOR(34),
	VECTOR(35), VECTOR(36), VECTOR(37), VECTOR(38), VECTOR(39),
	VECTOR(40), VECTOR(41), VECTOR(42), VECTOR(43), VECTOR(44),
	VECTOR(45), VECTOR(46), VECTOR(47), VECTOR(48);

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

#define SET_IDT(no)							\
	set_gate_descriptor(&idt[no].gate, VECTOR(no),			\
			    GLOBAL_32BIT_CODE, 0x0,			\
			    GATE_TYPE_32BIT_TRAP, 0x0,			\
			    0x1)

void 
interrupt_init(void)
{
	descriptor_table_register_t idtr;
	
	SET_IDT(0);
	SET_IDT(1);
	SET_IDT(2);
	SET_IDT(3);
	SET_IDT(4);
	SET_IDT(5);
	SET_IDT(6);
	SET_IDT(7);
	SET_IDT(8);
	SET_IDT(9);
	SET_IDT(10);
	SET_IDT(11);
	SET_IDT(12);
	SET_IDT(13);
	SET_IDT(14);
	SET_IDT(15);
	SET_IDT(16);
	SET_IDT(17);
	SET_IDT(18);
	SET_IDT(19);
	SET_IDT(20);
	SET_IDT(21);
	SET_IDT(22);
	SET_IDT(23);
	SET_IDT(24);
	SET_IDT(25);
	SET_IDT(26);
	SET_IDT(27);
	SET_IDT(28);
	SET_IDT(29);
	SET_IDT(30);
	SET_IDT(31);
	SET_IDT(32);
	SET_IDT(33);
	SET_IDT(34);
	SET_IDT(35);
	SET_IDT(36);
	SET_IDT(37);
	SET_IDT(38);
	SET_IDT(39);
	SET_IDT(40);
	SET_IDT(41);
	SET_IDT(42);
	SET_IDT(43);
	SET_IDT(44);
	SET_IDT(45);
	SET_IDT(46);
	SET_IDT(47);
	SET_IDT(48);

	set_descriptor_table_register(&idtr, idt, IDT_SIZE);
	idt_load(&idtr);
	i8259a_init();
	interrupt_enable();
}

