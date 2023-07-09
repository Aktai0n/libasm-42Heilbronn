	.file	"strcmp_test.c"
	.intel_syntax noprefix
	.text
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
.LFB22:
	.cfi_startproc
	push	r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	mov	rdx, rdi
	mov	r8, rsi
	mov	rcx, rsi
	push	rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	xor	eax, eax
	mov	rbp, rsi
	mov	rsi, rdi
	push	rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	mov	rbx, rdi
	mov	edi, OFFSET FLAT:.LC0
	call	printf
	mov	rdi, rbx
	mov	rsi, rbp
	xor	eax, eax
	call	ft_strcmp
	mov	rdi, rbx
	mov	rsi, rbp
	mov	r12d, eax
	call	strcmp
	mov	esi, r12d
	mov	edi, OFFSET FLAT:.LC1
	mov	ebx, eax
	mov	edx, eax
	xor	eax, eax
	call	printf
	test	r12d, r12d
	jle	.L6
	test	ebx, ebx
	jg	.L2
.L6:
	test	r12d, ebx
	jns	.L12
.L2:
	mov	edi, OFFSET FLAT:.LC2
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
	or	r12d, ebx
	je	.L2
	mov	edi, OFFSET FLAT:.LC3
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
.LFE22:
	.size	compare_strcmp, .-compare_strcmp
	.section	.rodata.str1.1
.LC4:
	.string	"42 Heilbronn\n\n"
.LC5:
	.string	"42 Heilbronn\n"
.LC6:
	.string	""
.LC7:
	.string	"hello World"
	.text
	.p2align 4
	.globl	strcmp_test
	.type	strcmp_test, @function
strcmp_test:
.LFB23:
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
	mov	esi, OFFSET FLAT:.LC5
	call	compare_strcmp
	mov	esi, OFFSET FLAT:.LC6
	mov	edi, OFFSET FLAT:.LC7
	call	compare_strcmp
	mov	esi, OFFSET FLAT:.LC6
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
.LFE23:
	.size	strcmp_test, .-strcmp_test
	.ident	"GCC: (GNU) 12.2.1 20221121 (Red Hat 12.2.1-4)"
	.section	.note.GNU-stack,"",@progbits
