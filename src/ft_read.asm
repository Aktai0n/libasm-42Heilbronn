section .text
%include "platform_specific.inc"

global FT_READ

extern GET_ERRNO

; Prototype:
;   ssize_t read(int fd, void* buf, size_t size)
; Parameters:
;   fd = rdi
;   buf = rsi
;   size = rdx

FT_READ:
    mov rax, READ_SYSCALL_CODE
    syscall
%ifdef MACOS
    jc .SET_ERRNO
%elifdef LINUX
    test rax, rax ; check for write error
    jl .SET_ERRNO
%endif
    ret

.SET_ERRNO:
    push rbp ; function prologue
    mov rbp, rsp

%ifdef LINUX
    neg rax ; negate rax to get the error code
%endif
    push rax ; save the error code
    call GET_ERRNO
    pop rcx ; move the error code to rcx
    mov DWORD [rax], ecx ; errno = error code

    mov rsp, rbp ; function epilogue
    pop rbp

    mov rax, -1
    ret ; return -1