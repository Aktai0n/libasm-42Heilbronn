	.file	"strlen_test.c"
	.intel_syntax noprefix
	.text
	.p2align 4
	.globl	ft_strlen
	.type	ft_strlen, @function
ft_strlen:
.LFB0:
	.cfi_startproc
	cmp	BYTE PTR [rdi], 0
	je	.L4
	mov	rax, rdi
	.p2align 4,,10
	.p2align 3
.L3:
	add	rax, 1
	cmp	BYTE PTR [rax], 0
	jne	.L3
	sub	rax, rdi
	ret
	.p2align 4,,10
	.p2align 3
.L4:
	xor	eax, eax
	ret
	.cfi_endproc
.LFE0:
	.size	ft_strlen, .-ft_strlen
	.ident	"GCC: (GNU) 12.2.1 20221121 (Red Hat 12.2.1-4)"
	.section	.note.GNU-stack,"",@progbits
