#ifndef KERN_FILE_DESCRIPTOR_H_
#define KERN_FILE_DESCRIPTOR_H_
#include <lib/types.h>
#include <lib/list.h>

typedef struct
{
	list_node_t list;
	int no;
	bool using;
	off_t offset;
	void *private_data;
} file_descriptor_t;

void file_descriptor_init(void);
file_descriptor_t *file_descriptor_new(void);
file_descriptor_t *file_descriptor_get(int no);
void file_descriptor_open(file_descriptor_t *vfd);
void file_descriptor_close(file_descriptor_t *vfd);
#endif /* KERN_FILE_DESCRIPTOR_H_*/
