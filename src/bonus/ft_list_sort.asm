section .text

%include "platform_specific.inc"

global FT_LIST_SORT

; Prototype:
;   void ft_list_sort(t_list** list, int (*cmp_func)())
; Parameters:
;   list = rdi
;   cmp_func = rsi
; Register layout:
;   rbx = t_list* of the outer loop
;   r12 = t_list* of the inner loop
;   r13 = copy of cmp_func
; Stack layout:
;   rbp - 8 = copy of list

FT_LIST_SORT:
    test rdi, rdi ; list == NULL
    jz .RETURN

    push rbp ; function prologue
    mov rbp, rsp

    push rdi ; save registers
    push rbx
    push r12
    push r13
    mov r13, rsi ; save cmp_func

    mov rbx, QWORD [rdi] ; t_list* outer_node = *list
    test rbx, rbx ; outer_node == NULL
    jz .BREAK1
    .LOOP1:
        mov r12, QWORD [rbx + 8] ; t_list* inner_node = outer_node->next
        .LOOP2:
            test r12, r12 ; inner_node == NULL
            jz .BREAK2

            xor rax, rax ; clear return register
            mov rdi, QWORD [rbx]
            mov rsi, QWORD [r12]
            call r13 ; cmp(outer_node->data, inner_node->data)

            test eax, eax ; ret_val <= 0
            jle .NO_SWAP
                mov rax, QWORD [rbx] ; void* temp1 = outer_node->data
                mov rdx, QWORD [r12] ; void* temp2 = inner_node->data
                mov QWORD [rbx], rdx ; outer_node->data = temp2
                mov QWORD [r12], rax ; inner_node->data = temp1
            .NO_SWAP:

            mov r12, QWORD [r12 + 8]; inner_node = inner_node->next
            jmp .LOOP2
        .BREAK2:
        mov rbx, QWORD [rbx + 8] ; outer_node = outer_node->next
        test rbx, rbx ; outer_node != NULL
        jnz .LOOP1
    .BREAK1:

    mov rsi, r13 ; restore registers
    pop r13
    pop r12
    pop rbx
    pop rdi

    mov rsp, rbp ; function epilogue
    pop rbp
.RETURN:
    ret