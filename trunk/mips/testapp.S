	.text
	.globl	_start
	.ent	_start
	.set noreorder
_start:
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
	.end	_start
