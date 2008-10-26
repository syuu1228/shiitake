#include <kern/thread.h>
#include <kern/memory.h>
#include <lib/assert.h>
#include <lib/console.h>

//#define DPRINTF (printf("[%s:%s:%d] ", __FILE__, __FUNCTION__, __LINE__), printf)
#define DPRINTF(...) do{}while(0)
static thread_t *running = 0;
static list_node_t runq = {0};

extern void md_thread_create(thread_t *t, void (*function)(void));
extern void md_thread_switch(thread_t *cur, void *new);

static inline void
add_queue(thread_t *t)
{
	DPRINTF("t:%p\n", t);
	list_move_tail(&runq, &t->list);
//	LIST_DUMP(&runq);
}

static inline void
remove_queue(thread_t *t)
{
	DPRINTF("t:%p\n", t);
	list_delete(&(t->list));
//	LIST_DUMP(&runq);
}

static inline thread_t *
get_queue(void)
{
	DPRINTF("\n");
//	LIST_DUMP(&runq);
	DPRINTF("return: %p\n", LIST_GET(runq.next, list, thread_t));
	return LIST_GET(runq.next, list, thread_t);
}

static inline void
rotate_queue(void)
{
	DPRINTF("\n");
	add_queue(running);
}

void 
thread_init(void)
{
	DPRINTF("\n");
	running = thread_create(NULL);
	assert(get_queue() == running);
}

thread_t *
thread_self(void)
{
	return running;
}

thread_t *
thread_create(void (*function)(void))
{
	DPRINTF("function:%p\n", function);
	thread_t *t = malloc(sizeof(thread_t));
	memset(t, 0, sizeof(thread_t));
	md_thread_create(t, function);
	add_queue(t);
	DPRINTF("&runq:%p runq.prev:%p runq.next:%p\n", &runq, runq.prev, runq.next);
	DPRINTF("t:%p\n", t);
	return t;
}

void 
thread_destroy(thread_t *t)
{
	DPRINTF("t:%p\n", t);
	remove_queue(t);
	free(t);
}

void
thread_wakeup(thread_t *t)
{
	DPRINTF("t:%p\n", t);
	add_queue(t);
}

void
thread_sleep(thread_t *t)
{
	DPRINTF("t:%p\n", t);
	remove_queue(t);
}

void
thread_yield(void)
{
	thread_t *next;

	DPRINTF("\n");
	rotate_queue();
//	LIST_DUMP(&runq);
	next = get_queue();
	DPRINTF("current:%p next:%p\n", running, next);
	if(running != next)
		thread_switch(next);
}

void
thread_switch(thread_t *next)
{
	thread_t *current = running;
	
	assert(current != next);
	running = next;
	md_thread_switch(current, next);
}
