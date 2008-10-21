#include <lib/list.h>
#include <lib/console.h>
#include <lib/types.h>

#define DPRINTF printf

void list_insert_before(list_node * list, list_node * node)
{
	DPRINTF("list:%p node:%p\n", list, node);
	node->prev = list->prev;
	node->next = list;
	if (node->prev)
		node->prev->next = node;
	list->prev = node;
//	list_dump(list);
}

void list_insert_after(list_node * list, list_node * node)
{
	DPRINTF("list:%p node:%p\n", list, node);
	node->prev = list;
	node->next = list->next;
	if (node->next)
		node->next->prev = node;
	list->next = node;
//	list_dump(list);
}

void list_insert_head (list_node *list, list_node *node)
{
	DPRINTF("list:%p node:%p\n", list, node);
	list_insert_after(list_head(list), node);
//	list_dump(list);
}

void list_insert_tail (list_node *list, list_node *node)
{
	DPRINTF("list:%p node:%p\n", list, node);
	list_insert_after(list_tail(list), node);
//	list_dump(list);
}

void list_delete(list_node * node)
{
	DPRINTF("node:%p\n", node);
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	node->prev = NULL;
	node->next = NULL;
}

void list_move_before(list_node * list, list_node * node)
{
	DPRINTF("list:%p node:%p\n", list, node);
//	list_delete (node);
	list_insert_before (list, node);
//	list_dump(list);
}

void list_move_after(list_node * list, list_node * node)
{
	DPRINTF("list:%p node:%p\n", list, node);
//	list_delete (node);
	list_insert_after (list, node);
//	list_dump(list);
}

void list_move_head (list_node *list, list_node *node)
{
	DPRINTF("list:%p node:%p\n", list, node);
	list_delete (node);
	list_insert_head (list, node);
//	list_dump(list);
}

void list_move_tail (list_node *list, list_node *node)
{
	DPRINTF("list:%p node:%p\n", list, node);
	list_delete (node);
	list_insert_tail (list, node);
//	list_dump(list);
}

list_node *list_tail(list_node * node)
{
	DPRINTF("node:%p\n", node);
	for (; node->next; node = node->next)
		;
	DPRINTF("node:%p\n", node);
	return node;
}

list_node *list_head(list_node * node)
{
	DPRINTF("node:%p\n", node);
	for (; node->prev; node = node->prev)
		;
	DPRINTF("node:%p\n", node);
	return node;
}

void list_node_copy(list_node * dest, list_node * src)
{
	DPRINTF("dest:%p src:%p\n", dest, src);
	dest->next = src->next;
	dest->prev = src->prev;
}

int list_count(list_node * node)
{
	DPRINTF("node:%p\n", node);
	int i = 0;
	LIST_FOR_EACH (node) i++;
	DPRINTF("return:%d\n", i);
	return i;
}

void list_dump(const list_node * const node)
{
	DPRINTF("node:%p\n", node);
	list_node *lp = (list_node *) node;
	LIST_FOR_EACH (lp)
		DPRINTF("list:%p prev:%p next:%p\n", lp, lp->prev, lp->next);
}
