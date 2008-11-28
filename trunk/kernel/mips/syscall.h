#ifndef MIPS_SYSCALL_H_
#define MIPS_SYSCALL_H_
#include <mips/thread.h>


void syscall_handle(unsigned status, unsigned cause, unsigned epc, md_thread_t *frame);
void syscall_invoke(md_thread_t *frame);
#endif
