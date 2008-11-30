#include <kern/console.h>
#include <mips/testmachine.h>

void putchar(int c)
{
	*((volatile unsigned char *) PUTCHAR_ADDRESS) = c;
}

int getchar(void)
{
	int c;
	while (!(c = *((volatile unsigned char *) PUTCHAR_ADDRESS)))
		;

	return c;
}
