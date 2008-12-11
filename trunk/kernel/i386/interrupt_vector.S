#include <i386/asm.h>

#define VECTOR(no)			\
	.globl interrupt_vector_ ## no ;\
	interrupt_vector_ ## no:       ;\
	pushal			       ;\
	pushl %esp		       ;\
	pushl $(no)		       ;\
	call trap		       ;\
	addl $8, %esp		       ;\
	popal			       ;\
	iret

VECTOR(0)
VECTOR(1)
VECTOR(2)
VECTOR(3)
VECTOR(4)
VECTOR(5)
VECTOR(6)
VECTOR(7)
VECTOR(8)
VECTOR(9)
VECTOR(10)
VECTOR(11)
VECTOR(12)
VECTOR(13)
VECTOR(14)
VECTOR(15)
VECTOR(16)
VECTOR(17)
VECTOR(18)
VECTOR(19)
VECTOR(20)
VECTOR(21)
VECTOR(22)
VECTOR(23)
VECTOR(24)
VECTOR(25)
VECTOR(26)
VECTOR(27)
VECTOR(28)
VECTOR(29)
VECTOR(30)
VECTOR(31)
VECTOR(32)
VECTOR(33)
VECTOR(34)
VECTOR(35)
VECTOR(36)
VECTOR(37)
VECTOR(38)
VECTOR(39)
VECTOR(40)
VECTOR(41)
VECTOR(42)
VECTOR(43)
VECTOR(44)
VECTOR(45)
VECTOR(46)
VECTOR(47)
VECTOR(128)
