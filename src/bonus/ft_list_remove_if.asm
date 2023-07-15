section .text

%include "platform_specific.inc"

global FT_LIST_REMOVE_IF

extern FREE

; Prototype:
;   void ft_list_remove_if(t_list** list,
;                          void* data_ref,
;                          int (*cmp_func)(),
;                          void (*free_func)(void*)
;                         )
; Parameters:
;   list = rdi
;   data_ref = rsi
;   cmp_func = rdx
;   free_func = rcx
; Register layout:
;   rbx = t_list* iterator
;   r12 = t_list* previous node
;   r13 = t_list* next node
;   r14 = cmp_func
;   r15 = free_func
; Stack layout:
;   rbp - 8 = data_ref
;   rbp - 16 = list

FT_LIST_REMOVE_IF:
    test rdi, rdi
    jz .RETURN

    push rbp ; function prologue
    mov rbp, rsp
    ; mov rbp, rsi

    push rsi ; save arguments on stack
    push rdi
    push rbx ; save registers
    push r12
    push r13
    push r14
    push r15

    mov r14, rdx
    mov r15, rcx

    mov rbx, QWORD [rdi] ; t_list* it = *list
    test rbx, rbx ; it == NULL
    jz .BREAK1
    xor r12, r12 ; t_list* prev = NULL

    .LOOP1:
        mov r13, QWORD [rbx + 8] ; t_list* next = it->next

        xor rax, rax ; clear return register
        mov rdi, QWORD [rbx]
        mov rsi, QWORD [rbp - 8]
        call r14 ; cmp_func(it->data, data_ref)

        test eax, eax ; return_value != 0
        jne .NO_MATCH
            test r12, r12 ; test whether it's the first node in the list
            jz .IF1
                mov QWORD [r12 + 8], r13 ; prev->next = next
                jmp .ENDIF1
            .IF1:
                mov rdx, QWORD [rbp - 16]
                mov QWORD [rdx], r13 ; *list = next
            .ENDIF1:

            mov rdi, QWORD [rbx]
            call r15 ; free_func(it->data)
            mov rdi, rbx
            call FREE ; free(it)
            xor rbx, rbx ; it = NULL
        .NO_MATCH:

        mov r12, rbx ; prev = it
        mov rbx, r13 ; it = next
        test rbx, rbx
        jnz .LOOP1
    .BREAK1:

    pop r15 ; restore registers
    pop r14
    pop r13
    pop r12
    pop rbx
    pop rdi
    pop rsi

    mov rsp, rbp ; function epilogue
    pop rbp
.RETURN:
    ret