	.file	"sort.c"
	.text
	.p2align 4
	.globl	sorting_filtered_array
	.type	sorting_filtered_array, @function
sorting_filtered_array:
.LFB16:
	.cfi_startproc
	endbr64
	testq	%rsi, %rsi
	je	.L2
	leaq	(%rdi,%rsi,4), %r8
	xorl	%r9d, %r9d
	.p2align 4,,10
	.p2align 3
.L3:
	movq	%rdi, %rax
	cmpq	%r9, %rsi
	jbe	.L6
	.p2align 4,,10
	.p2align 3
.L5:
	movl	(%rdi), %edx
	movl	(%rax), %ecx
	cmpl	%ecx, %edx
	jle	.L4
	movl	%ecx, (%rdi)
	movl	%edx, (%rax)
.L4:
	addq	$4, %rax
	cmpq	%rax, %r8
	jne	.L5
.L6:
	addq	$1, %r9
	addq	$4, %rdi
	cmpq	%r9, %rsi
	jne	.L3
.L2:
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE16:
	.size	sorting_filtered_array, .-sorting_filtered_array
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
