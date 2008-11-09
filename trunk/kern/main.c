#include <lib/console.h>
#include <kern/memory.h>
#include <kern/thread.h>

void thread1(void);
void thread3(void);

int thread2[] =
{
	0x24020001, /*        li      v0,1 */
	0x24040010, /*        li      a0,16 */
	0x24050020, /*        li      a1,32 */
	0x24060030, /*        li      a2,48 */
	0x24070040, /*        li      a3,64 */
	0x0000000c, /*        syscall */
	0x24020002, /*        li      v0,2 */
	0x24040100, /*        li      a0,256 */
	0x24050200, /*        li      a1,512 */
	0x24060300, /*        li      a2,768 */
	0x24070400, /*        li      a3,1024 */
	0x0000000c, /*        syscall */
	0x03e00008, /*        jr      ra */
	00000000    /*        nop */
};

int 
main(void)
{
	printf("starting shiitake..\n");
	size_t memory_size = memory_init();
	printf("%u byte of memory initializd.\n", memory_size);
	thread_init();
	printf("thread initialized.\n");
	thread_t *t2 = thread_create((void (*)(void))thread2);
	t2->md.sr |= 16; /* user mode */
	thread_create(thread3);
	thread1();
	return 0;
}

void
thread1(void)
{
	int i;
	for(i = 0; i < 10; i++) {
		printf("thread1\n");
		thread_yield();
	}
}

void
thread3(void)
{
	printf("thread3\n");
	printf("thread3\n");
	printf("thread3\n");
	printf("thread3\n");
	printf("thread3\n");
}
