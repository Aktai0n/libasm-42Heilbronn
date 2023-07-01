section .text
global ft_atoi_base

%include "platform_specific.inc"

extern ft_strlen
extern GET_ERRNO

; Prototype:
;    int ft_atoi_base(const char* str, const char* base)
; Parameters:
;   str = rdi
;   base = rsi
; Register layout:
;   rcx = copy of str
;   r8 = copy of base
;   r9 = base_len
;   r10 = sign
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
            cmp BYTE [rsi + rcx], BYTE [rsi + rax] ; base[i] == base[j]
            je .RETURN_ZERO

            inc rax ; ++j
            cmp rax, r9 ; j != base_len
            jne .LOOP2

        inc rcx ; ++i
        cmp rcx, r9 ; i != base_len
        jne .LOOP1

; --------------- skip spacing characters --------------

    mov rcx, rbp ; const char* s = str
    .LOOP3:
        movzx edi, BYTE [rcx] ; c = *s
        call ft_isspace
        test al, al
        jz .BREAK3
        inc rcx ; ++s
        jmp .LOOP3
    .BREAK3:

; --------------- calculate the sign --------------

    mov r10, 1 ; int sign = 1
    .LOOP4:
        cmp BYTE [rcx], 45 ; *s == '-'
        jne .SKIP4
        neg r10 ; sign = -sign
        inc rcx ; ++s
        jmp .LOOP4
    .SKIP4:
        cmp BYTE [rcx], 43 ; *s == '+'
        jne .BREAK4
        inc rcx ; ++s
        jmp .LOOP4
    .BREAK4:

; --------------- calculate the number --------------

    xor rax, rax ; int result = 0
    .LOOP5:
        xor rdx, rdx ; int digit = 0
        movzx edi, BYTE [rcx] ; char c = *s
        ; find the digit in the base
        ; if it's not found the conversion ends
        .LOOP6:
            cmp dil, BYTE [rsi + rdx] ; c == base[digit]
            je .BREAK6
            cmp BYTE [rsi + rdx], 0 ; base[digit] == '\0'
            je .BREAK5
            inc rdx ; ++digit
            jmp .LOOP6
        .BREAK6:
    
        imul rax, r9 ; result * base_len
        jo .OVERFLOW
        add rax, rdx ; result + digit
        jo .OVERFLOW
    .BREAK5:

    imul rax, r10 ; result * sign
    jo .OVERFLOW

    pop rsi ; restore base
    pop rdi ; and str
    mov rsp, rbp ; function epilogue
    pop rbp
    ret

.OVERFLOW:
    pop rsi ; restore base
    pop rdi ; and str
    call GET_ERRNO ; set errno to ERANGE
    mov DWORD [rax], ERANGE_ERROR_CODE

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
    cmp edi, 32 ; c == ' '
    sete dl
    lea eax, [edi - 9] ; substact 9 from c because '\t' has ascii code 9
    cmp eax, 4 ; c >= '\t' && c <= '\r'
    setbe al
    or eax, edx ; combine the results into eax
    ret