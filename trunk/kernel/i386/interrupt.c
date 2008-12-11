#include <i386/interrupt.h>
#include <i386/segment.h>
#include <i386/cpu.h>
#include <lib/console.h>

#define I8259A_MASTER_REG0 0x20
#define I8259A_MASTER_REG1 0x21

#define I8259A_SLAVE_REG0 0xa0
#define I8259A_SLAVE_REG1 0xa15

#define I8259A_CASCADE_IR 0x2
#define I8259A_INT_ADDR 32

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
#define DEFINE_VECTOR(no) extern void VECTOR(no)(void)

DEFINE_VECTOR(0);
DEFINE_VECTOR(1);
DEFINE_VECTOR(2);
DEFINE_VECTOR(3);
DEFINE_VECTOR(4);
DEFINE_VECTOR(5);
DEFINE_VECTOR(6);
DEFINE_VECTOR(7);
DEFINE_VECTOR(8);
DEFINE_VECTOR(9);
DEFINE_VECTOR(10);
DEFINE_VECTOR(11);
DEFINE_VECTOR(12);
DEFINE_VECTOR(13);
DEFINE_VECTOR(14);
DEFINE_VECTOR(15);
DEFINE_VECTOR(16);
DEFINE_VECTOR(17);
DEFINE_VECTOR(18);
DEFINE_VECTOR(19);
DEFINE_VECTOR(20);
DEFINE_VECTOR(21);
DEFINE_VECTOR(22);
DEFINE_VECTOR(23);
DEFINE_VECTOR(24);
DEFINE_VECTOR(25);
DEFINE_VECTOR(26);
DEFINE_VECTOR(27);
DEFINE_VECTOR(28);
DEFINE_VECTOR(29);
DEFINE_VECTOR(30);
DEFINE_VECTOR(31);
DEFINE_VECTOR(32);
DEFINE_VECTOR(33);
DEFINE_VECTOR(34);
DEFINE_VECTOR(35);
DEFINE_VECTOR(36);
DEFINE_VECTOR(37);
DEFINE_VECTOR(38);
DEFINE_VECTOR(39);
DEFINE_VECTOR(40);
DEFINE_VECTOR(41);
DEFINE_VECTOR(42);
DEFINE_VECTOR(43);
DEFINE_VECTOR(44);
DEFINE_VECTOR(45);
DEFINE_VECTOR(46);
DEFINE_VECTOR(47);
DEFINE_VECTOR(48);

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

	/* mask all interrupts */
	ioport_write8(I8259A_MASTER_REG1,
		      0xff);
	ioport_write8(I8259A_SLAVE_REG1,
		      0xff);
}

#define SET_IDT(no)							\
	set_gate_descriptor(&idt[no].gate, (unsigned)VECTOR(no),	\
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

