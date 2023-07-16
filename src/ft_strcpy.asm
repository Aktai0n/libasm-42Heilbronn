section .text

%include "platform_specific.inc"

global FT_STRCPY

; Prototype: 
;   char* ft_strcpy(char* dest, const char* src)
; Parameters:
; dest = rdi
; src = rsi

FT_STRCPY:
    xor rcx, rcx ; size_t i = 0
    mov rax, rdi ; prepare return value
    cmp BYTE [rsi], 0 ; *src == '\0'
    je .BREAK1
    .LOOP1:
        mov dl, BYTE [rsi + rcx] ; char src_char = src[i]
        mov BYTE [rdi + rcx], dl ; dest[i] = src[i]
        inc rcx
        cmp dl, 0 ; src[i] == '\0'
        jne .LOOP1
    .BREAK1:
    mov BYTE [rdi + rcx], 0 ; dest[i] = '\0'
    ret ; return dest