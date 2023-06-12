	.file	"ft_listlen.c"
	.intel_syntax noprefix
	.text
	.p2align 4
	.globl	ft_listlen
	.type	ft_listlen, @function
ft_listlen:
.LFB6:
	.cfi_startproc
	xor	eax, eax
	test	rdi, rdi
	je	.L4
	.p2align 4,,10
	.p2align 3
.L3:
	mov	rdi, QWORD PTR [rdi+8]
	add	rax, 1
	test	rdi, rdi
	jne	.L3
	ret
	.p2align 4,,10
	.p2align 3
.L4:
	ret
	.cfi_endproc
.LFE6:
	.size	ft_listlen, .-ft_listlen
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB7:
	.cfi_startproc
	xor	eax, eax
	ret
	.cfi_endproc
.LFE7:
	.size	main, .-main
	.ident	"GCC: (GNU) 12.2.1 20221121 (Red Hat 12.2.1-4)"
	.section	.note.GNU-stack,"",@progbits
