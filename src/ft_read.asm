section .text
global ft_read

%include "platform_specific.inc"

extern GET_ERRNO

; Prototype:
;   ssize_t read(int fd, void* buf, size_t size)
; Parameters:
;   fd = rdi
;   buf = rsi
;   size = rdx

ft_read:
    mov rax, READ_SYSCALL_CODE
    syscall
    test rax, rax ; check for read error
    jz _set_errno
    ret

_set_errno:
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