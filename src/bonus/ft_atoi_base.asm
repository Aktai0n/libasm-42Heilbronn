section .text
global ft_atoi_base

%include "platform_specific.inc"

extern ft_strlen

; Prototype:
;    int ft_atoi_base(const char* str, const char* base)
; Parameters:
;   str = rdi
;   base = rsi
; Register layout:
;   rcx = copy of str
;   r8 = copy of base
;   r9 = base_len
; Stack layout:
;   rbp + 0 = copy of str
;   rbp + 8 = copy of base

ft_atoi_base:
    push rbp ; function prologue
    mov rbp, rsp

    test rdi, rdi ; str == NULL
    jz .RETURN_ZERO
    test rsi, rsi ; base == NULL
    jz .RETURN_ZERO

    push rdi ; copy str to rbp + 0
    push rsi ; copy base to rbp + 8

    mov rdi, rsi
    call ft_strlen ; get the len of base
    mov r9, rax ; store base_len
    mov rdi, QWORD [rbp + 0] ; restore str

; --------------- validate the base --------------

    cmp r9, 1 ; base_len <= 1
    jbe .RETURN_ZERO

    xor rcx, rcx ; size_t i = 0
    .LOOP1:
        movzx edx, BYTE [rsi + rcx] ; c = base[i]
        cmp dl, 43 ; c == '+'
        je .RETURN_ZERO
        cmp dl, 45 ; c == '-'
        je .RETURN_ZERO
        mov edi, edx
        call ft_isspace
        mov rdi, [rbp + 0] ; restore str
        test al, al ; check base[i] for spacing character
        jz .RETURN_ZERO

        lea rax, [rcx + 1] ; size_t j = i + 1
        .LOOP2:
            cmp dl, BYTE [rsi + rax] ; c == base[j]
            je .RETURN_ZERO

            inc rax ; ++j
            cmp rax, r9 ; j < base_len
            jne .LOOP2

        inc rcx ; ++i
        cmp rcx, r9 ; i < base_len
        jne .LOOP1

    

; --------------- skip spaces and sign --------------









    mov rsp, rbp ; function epilogue
    pop rbp
    ret

.RETURN_ZERO:
    mov rsp, rbp ; function epilogue
    pop rbp
    xor rax, rax
    ret ; return NULL

; Prototype:
;   bool ft_isspace(int c)
; Parameters:
;   c = rdi

ft_isspace:
    cmp rdi, 32 ; c == ' '
    sete dl
    lea eax, [rdi - 9] ; substact 9 from c because '\t' has ascii code 9
    cmp eax, 4 ; c >= '\t' && c <= '\r'
    setbe al
    or eax, edx ; combine the results into eax
    ret
