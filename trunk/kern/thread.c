#include <kern/thread.h>
#include <kern/memory.h>
#include <lib/assert.h>
#include <lib/console.h>

#define DPRINTF (printf("[%s:%s:%d] ", __FILE__, __FUNCTION__, __LINE__), printf)

static thread_t *running = 0;
static list_node_t runq;

extern void md_thread_create(thread_t *t, void (*function)(void));
extern void md_thread_switch(thread_t *cur, void *new);

static inline void
add_queue(thread_t *t)
{
	DPRINTF("t:%p\n", t);
	list_move_tail(&(t->list), &runq);
	list_dump(&runq);
}

static inline void
remove_queue(thread_t *t)
{
	DPRINTF("t:%p\n", t);
	list_delete(&(t->list));
	list_dump(&runq);
}

static inline thread_t *
get_queue(void)
{
	DPRINTF("\n");
	list_dump(&runq);
	DPRINTF("return: %p\n", LIST_GET(runq.next, list, thread_t));
	return LIST_GET(runq.next, list, thread_t);
}

static inline void
rotate_queue(void)
{
	DPRINTF("\n");
	list_dump(&runq);
	add_queue(running);
}

void 
thread_init(void)
{
	DPRINTF("\n");
	running = thread_create(NULL);
	assert(get_queue == running);
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
	next = get_queue();
	DPRINTF("current:%p next:%p\n", running, next);
	if(running != next)
		md_thread_switch(running, next);
}
