#include <kern/syscall.h>

#define SYSCALL_ENTER0(no)				\
	asm volatile("movl %0, %%eax\n"			\
		     "int $128" :: "i"(no) : "eax")

#define SYSCALL_ENTER1(no, arg1)					\
	asm volatile("movl %0, %%eax\n"					\
		     "movl %1, %%ebx\n"					\
		     "int $128" :: "i"(no), "r"(arg1) : "eax", "ebx")

static void putchar(int c)
{
	SYSCALL_ENTER1(SYSCALL_PUTCHAR, c);
}
#if 0
static int getchar(void)
{
	SYSCALL_ENTER0(SYSCALL_GETCHAR);
}
#endif
int main(void)
{
	putchar('a');
	putchar('b');
	putchar('c');
#if 0
	while(1) {
		int c = getchar();
		putchar(c);
		if(c == 'q')
			break;
	}
#endif
	return 0;
}
