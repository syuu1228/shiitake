#include <kern/syscall.h>

extern void putchar(int c);
extern int getchar(void);

int main(void)
{
	putchar('a');
	putchar('b');
	putchar('c');
/*
	while(1) {
		int c = getchar();
		putchar(c);
		if(c == 'q')
			break;
	}
*/
	return 0;
}
