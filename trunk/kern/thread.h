#ifndef KERN_THREAD_H_
#define KERN_THREAD_H_
#include <lib/list.h>
#include <arch/config.h>
#include <arch/thread.h>
#include <lib/types.h>

typedef struct thread
{
	md_thread_t md;
	list_node_t list;
	uint8_t stack_area[THREAD_STACK_SIZE];
} thread_t;

thread_t *thread_running;

void thread_init(void);
thread_t *thread_self(void);
thread_t *thread_create(void (*function)(void));
void thread_destroy(thread_t *t);
void thread_wakeup(thread_t *t);
void thread_sleep(thread_t *t);
void thread_rotate(void);
void thread_yield(void);
void thread_switch(thread_t *next);
void thread_finalize(void);

void md_thread_create(thread_t *t, void (*function)(void));
void md_thread_switch(thread_t *cur, void *new);
void md_thread_trampoline(void (*function)(void));
#endif /* KERN_THREAD_H_*/
