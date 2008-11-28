	.text
	.globl	syscall_handle
	.ent	syscall_handle
syscall_handle:
	.set	noreorder
	move	$k0,$a0
	lw	$k1,THREAD_MD_V0($k0)
	lw	$a0,THREAD_MD_A0($k0)
	lw	$a1,THREAD_MD_A1($k0)
	lw	$a2,THREAD_MD_A2($k0)
	lw	$a3,THREAD_MD_A3($k0)
	.set	reorder
	.end	syscall_handle
	