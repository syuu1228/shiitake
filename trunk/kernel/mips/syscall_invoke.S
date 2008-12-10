#include <mips/asm.h>
	.text
	.globl	syscall_invoke
	.ent	syscall_invoke
syscall_invoke:
	.set	noreorder
	move	$k0,$a0
	lw	$v0,THREAD_MD_V0($k0)
	lw	$a0,THREAD_MD_A0($k0)
	lw	$a1,THREAD_MD_A1($k0)
	lw	$a2,THREAD_MD_A2($k0)
	lw	$a3,THREAD_MD_A3($k0)
	lw	$k0,%gp_rel(syscall_functions)($gp)
	addu	$k0,$k0,$v0
	lw	$v0,0($k0)
	jal	$v0
	nop
	jr	$ra
	nop
	.set	reorder
