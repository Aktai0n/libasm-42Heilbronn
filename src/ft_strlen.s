section .text
global ft_strlen ; make the function visible to other files

; Prototype:
;   size_t ft_strlen(const char* str)
; Parameters:
;   str = rdi
ft_strlen:
    mov rax, rdi ; char* temp = str
.LOOP1:
    cmp BYTE [rax], 0 ; *temp == '\0'
    je .BREAK1
    inc rax ; ++temp
    jmp .LOOP1
.BREAK1:
    sub rax, rdi ; temp - str
    ret

