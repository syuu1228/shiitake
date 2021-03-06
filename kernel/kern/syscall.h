#ifndef KERN_SYSCALL_H
#define KERN_SYSCALL_H

#define SYSCALL_PUTCHAR 0
#define	SYSCALL_GETCHAR 1
#define SYSCALL_GETATTR 2
#define	SYSCALL_OPENDIR 3
#define	SYSCALL_READDIR 4
#define	SYSCALL_SEEKDIR 5
#define	SYSCALL_TELLDIR 6
#define	SYSCALL_CLOSEDIR 7
#define	SYSCALL_OPEN 8
#define	SYSCALL_READ 9
#define	SYSCALL_LSEEK 10
#define	SYSCALL_CLOSE 11
#define	SYSCALL_MAX 12

#ifdef _KERNEL
extern void *syscall_functions[];
#endif
#endif
