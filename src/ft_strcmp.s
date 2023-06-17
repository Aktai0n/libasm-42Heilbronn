section .text
global ft_strcmp

; Prototype:
;   int ft_strcmp(const char* s1, const char* s2)
; Parameters:
; s1 = rdi
; s2 = rsi

ft_strcmp:
    xor rax, rax ; size_t i = 0
    .LOOP1:
        mov cl, BYTE [rdi + rax] ; char temp_s1 = s1[i]
        mov dl, BYTE [rsi + rax] ; char temp_s2 = s2[i]
        inc rax ; ++i

        cmp cl, dl ; temp_s1 == temp_s2
        je .EQUAL
            mov rax, cl
            sub rax, dl
            ret ; return temp_s1 - temp_s2

        .EQUAL:
        cmp cl, 0 ; temp_s1 != '\0'
        jne .LOOP1
        cmp dl, 0 ; temp_s2 != '\0'
        jne .LOOP1

    xor rax, rax
    ret ; return 0

