#include <kern/syscall.h>
#include <kern/file_system.h>
#include <kern/console.h>

void *syscall_functions[SYSCALL_MAX] = {
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
