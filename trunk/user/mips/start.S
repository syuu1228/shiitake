	.text
	.globl	_start
	.ent	_start
	.set noreorder
_start:
	la $gp, _gp
	la $s0, _fbss
	la $s1, _end
	addu $s1, 3
	li $s2, ~3
	and $s1, $s2
1:
	sw $zero, 0($s0)
	bne $s0, $s1, 1b
	addiu $s0, 4
	addiu $sp,$sp,-24
	sw $ra,20($sp)
	sw $fp,16($sp)
	move $fp,$sp
	jal main
	nop
	lw $ra,20($sp)
	lw $fp,16($sp)
	addiu $sp,$sp,24
	jr $ra
	nop

	.end
