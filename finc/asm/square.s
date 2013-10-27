# For example, square(5) = 25, square(9) = 81

.type square, @function
.globl square
square:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	imull	%eax, %eax
	movl	%ebp, %esp
	popl	%ebp
	ret
