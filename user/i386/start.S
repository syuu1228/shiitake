	.text
	.globl	start
start:
	movl	$_edata, %edi
	movl	$_end, %ecx
	subl	%edi, %ecx
	xorb	%al, %al
	cld
	rep
	stosb
	call	main
	ret

	.globl	putchar
putchar:
	movl	$0, %eax
	int	$0x80
	ret

	.globl	getchar
getchar:
	movl	$1, %eax
	int	$0x80
	ret
