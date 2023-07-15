section .text

%include "platform_specific.inc"

global FT_STRDUP

extern MALLOC
extern FT_STRLEN
extern FT_STRCPY

; Prototype:
;   char* ft_strdup(const char* str)
; Parameters
;   str = rdi

FT_STRDUP:
    push rbp ; function prologue
    mov rbp, rsp

    test rdi, rdi ; str == NULL
    jz .RETURN_ZERO

    push rbx ; save rbx
    mov rbx, rdi ; save the string pointer
    push rsi ; save rsi

    call FT_STRLEN
    push rax ; save the length
    lea rdi, [rax + 1] ; bytes to allocate = len + 1
    call MALLOC
    test rax, rax ; dest == NULL
    jz .MALLOC_FAILED

    mov rdi, rax ; copy dest = dest
    mov rsi, rbx ; copy src = str
    call FT_STRCPY
    pop rcx ; restore the length
    mov BYTE [rax + rcx], 0 ; dest[len] = '\0'

    pop rsi ; restore rsi
    pop rbx ; restore rbx

    mov rsp, rbp ; function epilogue
    pop rbp
    ret


.MALLOC_FAILED:
    add rsp, 8 ; reset the stack and registers
    pop rsi
    pop rbx

.RETURN_ZERO:
    mov rsp, rbp ; function epilogue
    pop rbp
    xor rax, rax
    ret ; return NULL