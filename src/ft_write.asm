section .text
global ft_write

%ifdef
extern __errno_location
%endif

; Prototype:
;    ssize_t ft_write(int fd, const void* buf, size_t size)
; Parameters:
; fd = rdi
; buf = rsi
; size = rdx

ft_write:
    mov rax, 1 ; syscall number 1 = sys_write
    syscall
    cmp rax, 0 ; check for write error
    jl _set_errno
    ret

_set_errno:
    neg rax, rcx


    mov rax, -1
    ret ; return -1