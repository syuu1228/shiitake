	.text
	.globl start
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
