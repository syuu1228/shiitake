#ifndef I386_SYSCALL_H_
#define I386_SYSCALL_H_
#include <i386/frame.h>

void syscall_handle(trapframe_t *frame);

#endif
