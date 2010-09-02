#include <mips/interrupt.h>
#include <mips/cpu.h>
#include <mips/thread.h>

#include <mips/testmachine.h>

void
interrupt_init(void)
{
//	const int sr = SR_CU0 | SR_IEo | SR_IEp | SR_IEc;
	const int sr = SR_CU0 | INT_LEV4 | SR_IEo | SR_IEp | SR_IEc;
	asm volatile("mtc0 %0, $12" : : "r"(sr));

	*((volatile int *)(RTC_ADDRESS + DEV_RTC_HZ)) = 1000;
}

void 
interrupt_handle(int level)
{
	printf("level:%x\n", level);
	while(1)
		;
}
