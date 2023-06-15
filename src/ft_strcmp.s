section .text
global ft_strcmp

; Prototype:
;   int ft_strcmp(const char* s1, const char* s2);
; Parameters:
; s1 = rdi
; s2 = rsi

ft_strcmp:
    mov rax, rdi ; char* str1 = s1
    mov rcx, rsi ; char* str1 = s2
    .LOOP1:
        cmp BYTE [rax], BYTE [rcx] ; *str1 != *str2
        ; also break when either of the strings is at '\0'
        jne .BREAK1
        inc rax ; ++str1
        inc rcx ; ++str2
        jmp .LOOP1
    .BREAK1:

    sub 

