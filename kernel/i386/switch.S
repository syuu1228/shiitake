#include <i386/asm.h>

	.text
	.globl	md_thread_switch
/*
 * 0(%esp) = ret
 * 4(%esp) = current
 * 8(%esp) = next
 */
md_thread_switch:
	movl	4(%esp),%ecx

	movl	0(%esp),%eax
	movl	%eax,THREAD_MD_EIP(%ecx)
	movl	%ebx,THREAD_MD_EBX(%ecx)
	movl    %esp,THREAD_MD_ESP(%ecx)
	movl	%ebp,THREAD_MD_EBP(%ecx)
	movl	%esi,THREAD_MD_ESI(%ecx)
	movl	%edi,THREAD_MD_EDI(%ecx)
	pushfl
	popl	THREAD_MD_EFLAGS(%edx)

	movl	8(%esp),%ecx
	movl	THREAD_MD_EBX(%ecx),%ebx
	movl	THREAD_MD_ESP(%ecx),%esp
	movl	THREAD_MD_EBP(%ecx),%ebp
	movl	THREAD_MD_ESP(%ecx),%esp
	movl	THREAD_MD_ESI(%ecx),%esi
	movl	THREAD_MD_EDI(%ecx),%edi
	movl	THREAD_MD_EIP(%ecx),%eax
	pushl	THREAD_MD_EFLAGS(%ecx)
	popfl
	movl	THREAD_MD_EIP(%ecx),%eax
	movl	%eax,(%esp)
	ret

	.globl	md_thread_trampoline
md_thread_trampoline:
	call	*%ebx
	call	thread_finalize
	movl	thread_running, %ecx
	movl	THREAD_MD_EBX(%ecx),%ebx
	movl	THREAD_MD_ESP(%ecx),%esp
	movl	THREAD_MD_EBP(%ecx),%ebp
	movl	THREAD_MD_ESP(%ecx),%esp
	movl	THREAD_MD_ESI(%ecx),%esi
	movl	THREAD_MD_EDI(%ecx),%edi
	movl	THREAD_MD_EIP(%ecx),%eax
	pushl	THREAD_MD_EFLAGS(%ecx)
	popfl
	movl	THREAD_MD_EIP(%ecx),%eax
	movl	%eax,(%esp)
	ret
