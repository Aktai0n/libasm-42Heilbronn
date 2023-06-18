	.file	"atoi_base_test.c"
	.intel_syntax noprefix
	.text
	.type	ft_isspace, @function
ft_isspace:
.LFB22:
	.cfi_startproc
	lea	eax, [rdi-9]
	cmp	eax, 4
	setbe	al
	cmp	edi, 32
	sete	dl
	or	eax, edx
	ret
	.cfi_endproc
.LFE22:
	.size	ft_isspace, .-ft_isspace
	.globl	ft_atoi_base
	.type	ft_atoi_base, @function
ft_atoi_base:
.LFB25:
	.cfi_startproc
	test	rdi, rdi
	je	.L26
	push	r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	push	r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	push	r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	push	r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	push	rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	push	rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	sub	rsp, 8
	.cfi_def_cfa_offset 64
	mov	rbp, rdi
	mov	rbx, rsi
	test	rsi, rsi
	je	.L15
	mov	rdi, rsi
	call	strlen
	mov	r12, rax
	mov	eax, 0
	cmp	r12, 1
	jbe	.L2
	mov	r15d, 0
	lea	r14, [rbx+r12]
.L6:
	movzx	r13d, BYTE PTR [rbx+r15]
	lea	eax, [r13-43]
	test	al, -3
	je	.L17
	movsx	edi, r13b
	call	ft_isspace
	test	al, al
	jne	.L18
	add	r15, 1
	cmp	r12, r15
	je	.L4
	lea	rax, [r15+rbx]
.L5:
	cmp	r13b, BYTE PTR [rax]
	je	.L19
	add	rax, 1
	cmp	rax, r14
	jne	.L5
	jmp	.L6
.L4:
	movzx	r13d, BYTE PTR [rbp+0]
	movsx	edi, r13b
	call	ft_isspace
	test	al, al
	je	.L29
	add	rbp, 1
	jmp	.L4
.L29:
	lea	eax, [r13-43]
	test	al, -3
	jne	.L20
	mov	edi, 1
.L10:
	mov	eax, edi
	neg	eax
	cmp	r13b, 45
	cmove	edi, eax
	add	rbp, 1
	movzx	r13d, BYTE PTR [rbp+0]
	lea	eax, [r13-43]
	test	al, -3
	je	.L10
.L8:
	movzx	r8d, BYTE PTR [rbx]
	mov	eax, 0
	jmp	.L11
.L20:
	mov	edi, 1
	jmp	.L8
.L13:
	imul	rax, r12
	add	rax, rdx
	add	rbp, 1
.L11:
	movzx	esi, BYTE PTR [rbp+0]
	test	r8b, r8b
	je	.L12
	mov	ecx, r8d
	mov	edx, 0
.L14:
	cmp	sil, cl
	je	.L13
	add	rdx, 1
	movzx	ecx, BYTE PTR [rbx+rdx]
	test	cl, cl
	jne	.L14
.L12:
	imul	eax, edi
.L2:
	add	rsp, 8
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	pop	rbx
	.cfi_def_cfa_offset 48
	pop	rbp
	.cfi_def_cfa_offset 40
	pop	r12
	.cfi_def_cfa_offset 32
	pop	r13
	.cfi_def_cfa_offset 24
	pop	r14
	.cfi_def_cfa_offset 16
	pop	r15
	.cfi_def_cfa_offset 8
	ret
.L15:
	.cfi_restore_state
	mov	eax, 0
	jmp	.L2
.L17:
	mov	eax, 0
	jmp	.L2
.L18:
	mov	eax, 0
	jmp	.L2
.L19:
	mov	eax, 0
	jmp	.L2
.L26:
	.cfi_def_cfa_offset 8
	.cfi_restore 3
	.cfi_restore 6
	.cfi_restore 12
	.cfi_restore 13
	.cfi_restore 14
	.cfi_restore 15
	mov	eax, 0
	ret
	.cfi_endproc
.LFE25:
	.size	ft_atoi_base, .-ft_atoi_base
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"Testing with: num_string = %s\nbase = %s"
	.align 8
.LC1:
	.string	"Result:\nft_atoi_base = %i, expected = %i\n"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC2:
	.string	"Test passed"
.LC3:
	.string	"Test failed"
	.text
	.globl	compare_atoi_base
	.type	compare_atoi_base, @function
compare_atoi_base:
.LFB26:
	.cfi_startproc
	push	r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	push	rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	push	rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	mov	rbp, rdi
	mov	r12, rsi
	mov	ebx, edx
	mov	rdx, rsi
	mov	rsi, rdi
	mov	edi, OFFSET FLAT:.LC0
	mov	eax, 0
	call	printf
	mov	rsi, r12
	mov	rdi, rbp
	call	ft_atoi_base
	mov	ebp, eax
	mov	edx, ebx
	mov	esi, eax
	mov	edi, OFFSET FLAT:.LC1
	mov	eax, 0
	call	printf
	cmp	ebp, ebx
	je	.L34
	mov	edi, OFFSET FLAT:.LC3
	call	puts
.L32:
	mov	edi, 10
	call	putchar
	pop	rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	pop	rbp
	.cfi_def_cfa_offset 16
	pop	r12
	.cfi_def_cfa_offset 8
	ret
.L34:
	.cfi_restore_state
	mov	edi, OFFSET FLAT:.LC2
	call	puts
	jmp	.L32
	.cfi_endproc
.LFE26:
	.size	compare_atoi_base, .-compare_atoi_base
	.section	.rodata.str1.1
.LC4:
	.string	"100"
.LC5:
	.string	"0"
.LC6:
	.string	"      +++42"
.LC7:
	.string	"\t\f\013 ++-+-30"
.LC8:
	.string	"something"
.LC9:
	.string	"\t\f\013 \r+101010someting else"
	.text
	.globl	main
	.type	main, @function
main:
.LFB27:
	.cfi_startproc
	sub	rsp, 56
	.cfi_def_cfa_offset 64
	movabs	rax, 3978425819141910832
	mov	QWORD PTR [rsp+37], rax
	mov	DWORD PTR [rsp+44], 3749943
	movabs	rdx, 3978425819141910832
	movabs	rcx, 5063528411713059128
	mov	QWORD PTR [rsp+16], rdx
	mov	QWORD PTR [rsp+24], rcx
	mov	BYTE PTR [rsp+32], 0
	mov	QWORD PTR [rsp+6], rax
	mov	WORD PTR [rsp+14], 56
	mov	WORD PTR [rsp+3], 12592
	mov	BYTE PTR [rsp+5], 0
	mov	edx, 100
	lea	rsi, [rsp+37]
	mov	edi, OFFSET FLAT:.LC4
	call	compare_atoi_base
	mov	edx, 0
	lea	rsi, [rsp+6]
	mov	edi, OFFSET FLAT:.LC5
	call	compare_atoi_base
	mov	edx, 42
	lea	rsi, [rsp+37]
	mov	edi, OFFSET FLAT:.LC6
	call	compare_atoi_base
	mov	edx, 48
	lea	rsi, [rsp+16]
	mov	edi, OFFSET FLAT:.LC7
	call	compare_atoi_base
	mov	edx, 0
	lea	rsi, [rsp+3]
	mov	edi, 0
	call	compare_atoi_base
	mov	edx, 0
	mov	esi, OFFSET FLAT:.LC5
	mov	edi, OFFSET FLAT:.LC8
	call	compare_atoi_base
	mov	edx, 42
	lea	rsi, [rsp+3]
	mov	edi, OFFSET FLAT:.LC9
	call	compare_atoi_base
	mov	eax, 0
	add	rsp, 56
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE27:
	.size	main, .-main
	.ident	"GCC: (GNU) 12.2.1 20221121 (Red Hat 12.2.1-4)"
	.section	.note.GNU-stack,"",@progbits
