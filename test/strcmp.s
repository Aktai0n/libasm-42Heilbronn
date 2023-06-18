	.file	"strcmp_test.c"
	.intel_syntax noprefix
	.text
	.p2align 4
	.globl	ft_strcmp
	.type	ft_strcmp, @function
ft_strcmp:
.LFB22:
	.cfi_startproc
	xor	eax, eax
	.p2align 4,,10
	.p2align 3
.L2:
	movzx	edx, BYTE PTR [rdi+rax]
	movzx	ecx, BYTE PTR [rsi+rax]
	test	dl, dl
	jne	.L4
	test	cl, cl
	je	.L8
.L5:
	movzx	eax, dl
	sub	eax, ecx
	ret
	.p2align 4,,10
	.p2align 3
.L4:
	add	rax, 1
	cmp	dl, cl
	je	.L2
	jmp	.L5
	.p2align 4,,10
	.p2align 3
.L8:
	xor	eax, eax
	ret
	.cfi_endproc
.LFE22:
	.size	ft_strcmp, .-ft_strcmp
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"Testing with:\ns1 = %s, address = %p\ns2 = %s, address = %p\n"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC1:
	.string	"ft_strcmp = %d, strcmp = %d\n"
.LC2:
	.string	"Test passed!"
.LC3:
	.string	"Test failed!"
	.text
	.p2align 4
	.globl	compare_strcmp
	.type	compare_strcmp, @function
compare_strcmp:
.LFB23:
	.cfi_startproc
	push	r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	mov	r8, rsi
	mov	rcx, rsi
	mov	rdx, rdi
	push	rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	mov	r12, rsi
	mov	rbp, rdi
	mov	rsi, rdi
	push	rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	mov	edi, OFFSET FLAT:.LC0
	xor	eax, eax
	call	printf
	xor	eax, eax
	.p2align 4,,10
	.p2align 3
.L10:
	movzx	edx, BYTE PTR [rbp+0+rax]
	movzx	ecx, BYTE PTR [r12+rax]
	test	dl, dl
	jne	.L12
	test	cl, cl
	je	.L18
.L13:
	movzx	ebx, dl
	sub	ebx, ecx
.L11:
	mov	rdi, rbp
	mov	rsi, r12
	call	strcmp
	mov	esi, ebx
	mov	edi, OFFSET FLAT:.LC1
	mov	ebp, eax
	mov	edx, eax
	xor	eax, eax
	call	printf
	cmp	ebp, ebx
	je	.L19
	mov	edi, OFFSET FLAT:.LC3
	call	puts
	pop	rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	mov	edi, 10
	pop	rbp
	.cfi_def_cfa_offset 16
	pop	r12
	.cfi_def_cfa_offset 8
	jmp	putchar
	.p2align 4,,10
	.p2align 3
.L12:
	.cfi_restore_state
	add	rax, 1
	cmp	dl, cl
	je	.L10
	jmp	.L13
	.p2align 4,,10
	.p2align 3
.L18:
	xor	ebx, ebx
	jmp	.L11
	.p2align 4,,10
	.p2align 3
.L19:
	mov	edi, OFFSET FLAT:.LC2
	call	puts
	pop	rbx
	.cfi_def_cfa_offset 24
	mov	edi, 10
	pop	rbp
	.cfi_def_cfa_offset 16
	pop	r12
	.cfi_def_cfa_offset 8
	jmp	putchar
	.cfi_endproc
.LFE23:
	.size	compare_strcmp, .-compare_strcmp
	.section	.rodata.str1.1
.LC4:
	.string	"42 Heilbronn\n"
.LC5:
	.string	""
.LC6:
	.string	"hello World"
	.text
	.p2align 4
	.globl	strcmp_test
	.type	strcmp_test, @function
strcmp_test:
.LFB24:
	.cfi_startproc
	movabs	rax, 7092159396924371508
	push	rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	mov	edi, 13
	sub	rsp, 16
	.cfi_def_cfa_offset 32
	mov	QWORD PTR [rsp+3], rax
	movabs	rax, 31083672377650281
	mov	QWORD PTR [rsp+8], rax
	call	malloc
	lea	rsi, [rsp+3]
	mov	edi, OFFSET FLAT:.LC4
	mov	rbx, rax
	mov	rax, QWORD PTR [rsp+3]
	mov	QWORD PTR [rbx], rax
	mov	rax, QWORD PTR [rsp+8]
	mov	QWORD PTR [rbx+5], rax
	call	compare_strcmp
	lea	rdi, [rsp+3]
	mov	esi, OFFSET FLAT:.LC4
	call	compare_strcmp
	mov	esi, OFFSET FLAT:.LC5
	mov	edi, OFFSET FLAT:.LC6
	call	compare_strcmp
	mov	esi, OFFSET FLAT:.LC5
	mov	rdi, rsi
	call	compare_strcmp
	mov	rsi, rbx
	lea	rdi, [rsp+3]
	call	compare_strcmp
	mov	rdi, rbx
	mov	rsi, rbx
	call	compare_strcmp
	add	rsp, 16
	.cfi_def_cfa_offset 16
	mov	rdi, rbx
	pop	rbx
	.cfi_def_cfa_offset 8
	jmp	free
	.cfi_endproc
.LFE24:
	.size	strcmp_test, .-strcmp_test
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB25:
	.cfi_startproc
	sub	rsp, 8
	.cfi_def_cfa_offset 16
	xor	eax, eax
	call	strcmp_test
	xor	eax, eax
	add	rsp, 8
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE25:
	.size	main, .-main
	.ident	"GCC: (GNU) 12.2.1 20221121 (Red Hat 12.2.1-4)"
	.section	.note.GNU-stack,"",@progbits
