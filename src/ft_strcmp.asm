section .text

%include "platform_specific.inc"

global FT_STRCMP

; Prototype:
;   int ft_strcmp(const char* s1, const char* s2)
; Parameters:
;   s1 = rdi
;   s2 = rsi

FT_STRCMP:
    xor rax, rax ; size_t i = 0
    .LOOP1:
        mov cl, BYTE [rdi + rax] ; char temp_s1 = s1[i]
        mov dl, BYTE [rsi + rax] ; char temp_s2 = s2[i]
        test cl, cl ; s1[i] != '\0'
        jnz .NOT_ZERO
        test dl, dl ; s1[i] == '\0' && s2[i] == '\0'
        jz .BREAK1
    .NOT_ZERO:
        cmp cl, dl ; temp_s1 == temp_s2
        je .EQUAL
            movzx rax, cl ; move zero extended
            movzx rdx, dl
            sub rax, rdx
            ret ; return temp_s1 - temp_s2
        .EQUAL:
        inc rax ; ++i
        jmp .LOOP1
    .BREAK1:

    xor rax, rax
    ret ; return 0
