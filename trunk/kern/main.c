#include <lib/console.h>
#include <kern/memory.h>
#include <kern/thread.h>

void thread1(void);
void thread2(void);

int 
main(void)
{
	printf("starting shiitake..\n");
	return 0;
	size_t memory_size = memory_init();
	printf("%u byte of memory initializd.\n", memory_size);
	thread_init();
	printf("thread initialized.\n");
	thread_create(thread2);
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
