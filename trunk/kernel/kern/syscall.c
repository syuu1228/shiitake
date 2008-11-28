#include <kern/syscall.h>

void *syscall_entries[SYSCALL_MAX] = {
	(void *)putchar,
	(void *)getchar,
	(void *)getattr,
	(void *)opendir,
	(void *)readdir,
	(void *)seekdir,
	(void *)telldir,
	(void *)closedir,
	(void *)open,
	(void *)read,
	(void *)lseek,
	(void *)close,
};
