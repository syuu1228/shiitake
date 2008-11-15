	.text
	.globl	_start
	.ent	_start
	.set noreorder
_start:
	/* Setup sp and gp */
	la $gp, _gp
	la $sp, _sp
	/* Clear bss */
	la $s0, _fbss	/* First address */
	la $s1, _end	/* Last  address */
	addu $s1, 3
	li $s2, ~3
	and $s1, $s2
1:
	sw $zero, 0($s0)
	bne $s0, $s1, 1b
	addiu $s0, 4
	jal main
	nop
	jr $ra
	nop
	.end	_start


	.globl main
	.ent main
	.set noreorder
main:
	li $v0, 1
	li $a0, 0x10
	li $a1, 0x20
	li $a2, 0x30
	li $a3, 0x40
	syscall
	li $v0, 2
	li $a0, 0x100
	li $a1, 0x200
	li $a2, 0x300
	li $a3, 0x400
	syscall
	jr $ra
	nop
	.end main
