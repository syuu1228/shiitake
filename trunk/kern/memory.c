#include <kern/memory.h>
#include <lib/string.h>
#include <lib/console.h>
#include <lib/list.h>

#define DPRINTF (printf("[%s:%s:%d] ", __FILE__, __FUNCTION__, __LINE__), printf)

typedef struct malloc_unit
{
	struct malloc_unit *prev, *next;
	size_t size;
	bool allocated;
} malloc_unit_t;

malloc_unit_t *unit_list_head;

extern char * md_memory_head(void);
extern char * md_memory_tail(void);

static inline char *
unit_data(malloc_unit_t *unit)
{
	return (char *)(unit + 1);
}

static inline char *
unit_tail(malloc_unit_t *unit)
{
	return ((char *)(unit + 1) + unit->size);
}

static inline malloc_unit_t *
unit_data_to_head(char *data)
{
	return ((malloc_unit_t *)data - 1);
}

static inline void
unit_dump(malloc_unit_t *unit)
{
	DPRINTF("unit:%x tail:%x next:%x prev:%x size:%x allocated:%b\n",
		unit, unit_tail(unit), unit->next, unit->prev, unit->size,
		unit->allocated);
}

static inline void
unit_add(malloc_unit_t *unit, malloc_unit_t *list)
{
	DPRINTF("ent:%x list:%x\n", unit, list);
	unit->prev = list;
	unit->next = list->next;
	if (unit->next)
	{
		DPRINTF("unit->next exists\n");
		unit->next->prev = unit;
	}
	list->next = unit;
	DPRINTF("");
}

static inline void 
unit_merge(malloc_unit_t *unit1, malloc_unit_t *unit2)
{
	DPRINTF("");
	unit_dump(unit1);
	DPRINTF("");
	unit_dump(unit2);
	unit1->next = unit2->next;
	unit1->size += sizeof(malloc_unit_t) + unit2->size;
	DPRINTF("");
	unit_dump(unit1);
}

size_t
memory_init(void)
{
	unit_list_head = (malloc_unit_t *)md_memory_head();
	unit_list_head->next = 0;
	unit_list_head->prev = 0;
        unit_list_head->size = md_memory_tail() - (char *)unit_list_head - sizeof(malloc_unit_t);
	unit_list_head->allocated = false;
	DPRINTF("");
	unit_dump(unit_list_head);
	return unit_list_head->size;
}

void *malloc(size_t size)
{
	malloc_unit_t *unit;
	DPRINTF("size:%d\n", size);
	for (unit = unit_list_head; unit; unit = unit->next)
		if (!unit->allocated && unit->size >= size)
			break;
	if (unit->allocated)
	{
		printf("Ugh, no left memory!\n");
		DPRINTF("return:NULL\n");
		return 0;
	}
	if (unit->size > size + sizeof(malloc_unit_t))
	{
		malloc_unit_t *new_unit =(malloc_unit_t *)(unit_data(unit) + size);
		new_unit->size = unit_tail(unit) - unit_data(new_unit);
		new_unit->allocated = false;
		unit->size = size;
		unit_add(new_unit, unit);
	}
	unit->allocated = true;
	DPRINTF("return:%x\n", unit_data(unit));
	return unit_data(unit);
}

void *calloc(size_t nmemb, size_t size)
{
	void *ptr = malloc(nmemb * size);
	if(!ptr)
		return NULL;
	memset(ptr, 0, nmemb * size);
	return ptr;
}

void free(void *ptr)
{
	DPRINTF("ptr:%x\n", ptr);
	malloc_unit_t *unit = unit_data_to_head(ptr);
	unit->allocated = false;
	if (unit->prev && !unit->prev->allocated 
	    && unit_tail(unit->prev) == (char *)unit)
		unit_merge(unit->prev, unit);
	if (unit->next && !unit->next->allocated 
	    && unit_tail(unit) == (char *)unit->next)
		unit_merge(unit, unit->next);
}

void malloc_dump(void)
{
	malloc_unit_t *unit = unit_list_head;
	do
	{
		DPRINTF("");
		unit_dump(unit);
	} while (unit = unit->next);
}
