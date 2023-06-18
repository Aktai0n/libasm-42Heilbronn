	.file	"strdup_test.c"
	.intel_syntax noprefix
	.text
	.p2align 4
	.globl	my_strdup
	.type	my_strdup, @function
my_strdup:
.LFB22:
	.cfi_startproc
	test	rdi, rdi
	je	.L9
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	push	rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	mov	rbx, rdi
	sub	rsp, 8
	.cfi_def_cfa_offset 32
	call	strlen
	lea	rbp, [rax+1]
	mov	rdi, rbp
	call	malloc
	test	rax, rax
	je	.L13
	mov	rdx, rbp
	mov	rsi, rbx
	mov	rdi, rax
	call	memcpy
	mov	rcx, rax
.L1:
	add	rsp, 8
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	mov	rax, rcx
	pop	rbx
	.cfi_def_cfa_offset 16
	pop	rbp
	.cfi_def_cfa_offset 8
	ret
.L13:
	.cfi_restore_state
	xor	ecx, ecx
	jmp	.L1
.L9:
	.cfi_def_cfa_offset 8
	.cfi_restore 3
	.cfi_restore 6
	xor	eax, eax
	ret
	.cfi_endproc
.LFE22:
	.size	my_strdup, .-my_strdup
	.p2align 4
	.globl	compare_strdup
	.type	compare_strdup, @function
compare_strdup:
.LFB23:
	.cfi_startproc
	ret
	.cfi_endproc
.LFE23:
	.size	compare_strdup, .-compare_strdup
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB24:
	.cfi_startproc
	xor	eax, eax
	ret
	.cfi_endproc
.LFE24:
	.size	main, .-main
	.ident	"GCC: (GNU) 12.2.1 20221121 (Red Hat 12.2.1-4)"
	.section	.note.GNU-stack,"",@progbits
