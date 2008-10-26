#ifndef LIB_LIST_H_
#define LIB_LIST_H_
#include <lib/console.h>
#include <lib/assert.h>

typedef struct list_node
{
  struct list_node *prev, *next;
} list_node_t;

#define LIST_GET(node, name, type) (type *)((void *)node - offsetof(type, name))
#define LIST_FOR_EACH(head, node) for(node = head; node; node = node->next)
#define LIST_FOR_EACH_REVERSE(tail, node) for(node = tail; node; node = node->prev)
#define LIST_NODE_IS_HEAD(node) (!node->prev)

#define DPRINTF (printf("[%s:%s:%d] ", __FILE__, __FUNCTION__, __LINE__), printf)

static inline void
list_delete(list_node_t *node)
{
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
}


static inline list_node_t *
list_get_head(list_node_t *node)
{
	DPRINTF("node:%p\n", node);
	for(; node->prev; node = node->prev)
		;
	DPRINTF("head:%p\n", node);
	return node;
}

static inline list_node_t *
list_get_tail(list_node_t *node)
{		
	DPRINTF("node:%p\n", node);
	for (; node->next; node = node->next)
		;
	DPRINTF("tail:%p\n", node);
	return node;
}

static inline void
list_move_before(list_node_t *dest, list_node_t *node)
{
	assert(!LIST_NODE_IS_HEAD(dest));
	list_delete(node);
	node->prev = dest->prev;
	node->next = dest;
	if (node->prev)
		node->prev->next = node;
	dest->prev = node;
}

static inline void
list_move_after(list_node_t *dest, list_node_t *node)
{
	DPRINTF("dest:%p node:%p\n", dest, node);
	list_delete(node);
	node->prev = dest;
	node->next = dest->next;
	if (node->next)
		node->next->prev = node;
	dest->next = node;
}

static inline void
list_move_tail(list_node_t *list, list_node_t *node)
{
	DPRINTF("list:%p node:%p\n", list, node);
	list_move_after(list_get_tail(list), node);
}

static inline int
list_count(list_node_t *node)
{
	int i = 0;
	list_node_t *lp;
	LIST_FOR_EACH (node, lp) i++;
	return i;
}

static inline void
list_dump(list_node_t *node)
{
#if 0
	list_node_t *lp;
	LIST_FOR_EACH (node, lp)
		printf("list:%p prev:%p next:%p\n", lp, lp->prev, lp->next);
#endif
}
#endif /* LIB_LIST_H_ */
