#include <lib/console.h>
#include <kern/memory.h>
#include <kern/thread.h>
#include <kern/file_system.h>
#include <kern/execute.h>

int 
main(void)
{
	printf("starting shiitake..\n");
	size_t memory_size = memory_init();
	printf("%u byte of memory initializd.\n", memory_size);
	thread_init();
	printf("thread initialized.\n");
	file_system_init();
	printf("file system initialized.\n");
	execute("/TESTAPP");
	thread_yield();
	printf("shiitake stopped.\n");
	return 0;
}
