section .text

%include "platform_specific.inc"

global FT_STRLEN ; make the function visible to other files

; Prototype:
;   size_t ft_strlen(const char* str)
; Parameters:
;   str = rdi

FT_STRLEN:
    mov rax, rdi ; char* temp = str

    .LOOP1:
        cmp BYTE [rax], 0 ; *temp == '\0'
        je .BREAK1
        inc rax ; ++temp
        jmp .LOOP1
    .BREAK1:

    sub rax, rdi ; temp - str
    ret

