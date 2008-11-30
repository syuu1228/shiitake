#include <kern/syscall.h>

#define SYSCALL_ENTER(no)			\
	asm volatile("li $v0, %0\n"		\
		     "syscall" :: "i"(no))

void putchar(int c)
{
	SYSCALL_ENTER(SYSCALL_PUTCHAR);
}

int getchar(void)
{
	SYSCALL_ENTER(SYSCALL_GETCHAR);
}

int main(void)
{
	putchar('a');
	putchar('b');
	putchar('c');
	while(1) {
		int c = getchar();
		putchar(c);
		if(c == 'q')
			break;
	}
	return 0;
}
