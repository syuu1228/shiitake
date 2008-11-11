#include <kern/file_descriptor.h>
#include <lib/string.h>

static file_descriptor_t *file_descriptor_construct(void);
static list_node_t fd_list;

//#define DPRINTF (printf("[%s:%s:%d] ", __FILE__, __FUNCTION__, __LINE__), printf)
#define DPRINTF(...) do{}while(0)

#define FILE_DESCRIPTOR_DUMP(fd) \
	printf("fd:%p list:%p prev:%p next:%p using:%d offset:%u private_data:%p\n", \
	fd, (fd)->list, (fd)->list.prev, (fd)->list.next, (fd)->using, (fd)->offset, (fd)->private_data)

void
file_descriptor_init(void)
{
	DPRINTF("\n");
	memset(&fd_list, 0, sizeof(list_node_t));
}

file_descriptor_t *
file_descriptor_construct(void)
{
	DPRINTF("\n");
	static int count = 0;
	file_descriptor_t *fd = (file_descriptor_t *)calloc(1, sizeof(file_descriptor_t));
	fd->no = count++;
	fd->using = false;
	list_move_tail(&fd_list, &(fd->list));
#ifdef DEBUG
	FILE_DESCRIPTOR_DUMP(fd);
#endif
	return fd;
}

file_descriptor_t *
file_descriptor_new(void)
{
	DPRINTF("\n");
	list_node_t *lp;
	LIST_FOR_EACH(&fd_list, lp)
	{
		file_descriptor_t *fd = LIST_GET(lp, list, file_descriptor_t);
#ifdef DEBUG
		FILE_DESCRIPTOR_DUMP(fd);
#endif
		if(!fd->using)
			return fd;
	}
	return file_descriptor_construct();
}

file_descriptor_t *
file_descriptor_get(int no)
{
	DPRINTF("no:%d\n", no);
	list_node_t *lp;
	LIST_FOR_EACH(&fd_list, lp)
	{
		file_descriptor_t *fd = LIST_GET(lp, list, file_descriptor_t);
#ifdef DEBUG
		FILE_DESCRIPTOR_DUMP(fd);
#endif
		if(fd->no == no)
			return fd;
	}
	DPRINTF("return:NULL\n");
	return NULL;
}

void 
file_descriptor_open(file_descriptor_t *fd)
{
#ifdef DEBUG
	FILE_DESCRIPTOR_DUMP(fd);
#endif
	fd->using = true;
}

void 
file_descriptor_close(file_descriptor_t *fd)
{
#ifdef DEBUG
	FILE_DESCRIPTOR_DUMP(fd);
#endif
	fd->using = false;
}
