section .text
global ft_write

%include "platform_specific.inc"

extern GET_ERRNO

; Prototype:
;    ssize_t ft_write(int fd, const void* buf, size_t size)
; Parameters:
;   fd = rdi
;   buf = rsi
;   size = rdx

ft_write:
    mov rax, WRITE_SYSCALL_CODE
    syscall
    ; test rax, rax ; check for write error
    ; jz .SET_ERRNO
    cmp rax, 0
    jl .SET_ERRNO
    ret

.SET_ERRNO:
    push rbp ; function prologue
    mov rbp, rsp

    neg rax ; negate rax to get the error code
    push rax ; save the error code
    call GET_ERRNO
    pop rcx ; move the error code to rcx
    mov DWORD [rax], ecx ; errno = error code

    mov rsp, rbp ; function epilogue
    pop rsp

    mov rax, -1
    ret ; return -1