#include <lib/console.h>
#include <kern/memory.h>
#include <kern/thread.h>

int 
main(void)
{
	printf("starting shiitake..\n");
	size_t memory_size = memory_init();
	printf("%u byte of memory initializd.\n", memory_size);
	thread_init();
	printf("thread initialized.\n");
	thread1();
	return 0;
}

void
thread1(void)
{
	while(1) {
		printf("thread1\n");
		thread_yield();
	}
}

void
thread2(void)
{
	while(1) {
		printf("thread2\n");
		thread_yield();
	}
}
