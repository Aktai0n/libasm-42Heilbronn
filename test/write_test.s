	.file	"write_test.c"
	.intel_syntax noprefix
	.text
	.section	.rodata
.LC0:
	.string	"Testing\n"
.LC1:
	.string	"write failed because %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	edx, 8
	mov	esi, OFFSET FLAT:.LC0
	mov	edi, 1
	call	write
	mov	QWORD PTR [rbp-8], rax
	cmp	QWORD PTR [rbp-8], -1
	jne	.L2
	call	__errno_location
	mov	eax, DWORD PTR [rax]
	mov	esi, eax
	mov	edi, OFFSET FLAT:.LC1
	mov	eax, 0
	call	printf
.L2:
	mov	eax, 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 12.2.1 20221121 (Red Hat 12.2.1-4)"
	.section	.note.GNU-stack,"",@progbits
