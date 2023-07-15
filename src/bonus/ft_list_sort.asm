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
;   r13 = the next node of r12
; Stack layout:
;   rbp - 8 = copy of cmp_func
;   rbp - 16 = copy of list

FT_LIST_SORT:
    test rdi, rdi ; list == NULL
    jz .RETURN
    cmp QWORD [rdi], 0 ; *list == NULL
    je .RETURN

    push rbp ; function prologue
    mov rbp, rsp

    push rsi ; save registers
    push rdi
    push rbx
    push r12
    push r13

    mov rbx, QWORD [rdi] ; t_list* outer_node = *list
    cmp QWORD [rbx + 8], 0 ; outer_node->next == NULL
    je .BREAK1
    .LOOP1:
        mov r12, rbx ; t_list* innter_node = outer_node
        .LOOP2:
            xor rax, rax ; clear return register
            mov r13, QWORD [r12 + 8] ; t_list* next = inner_node->next
            mov rdi, QWORD [r12]
            mov rsi, QWORD [r13]
            call QWORD [rbp - 8] ; cmp_func(inner_node->data, next->data)
            test eax, eax ; ret_val <= 0
            jle .NO_SWAP
                ; Repurpose the 128-bit floating point registers to
                ; move all 16 bytes of the struct t_list at once
                movups xmm0, [r12]
                movups xmm1, [r13]
                movups [r12], xmm1
                movups [r13], xmm0
            .NO_SWAP:
            mov r12, QWORD [r12 + 8] ; inner_node = inner_node->next
            cmp QWORD [rbx + 8], 0 ; inner_node->next != NULL
            jne .LOOP2
        .BREAK2:
        mov rbx, QWORD [rbx + 8] ; outer_node = outer_node->next
        cmp QWORD [rbx + 8], 0 ; outer_node->next != NULL
        jne .LOOP1
    .BREAK1:

    pop r13 ; restore registers
    pop r12
    pop rbx
    pop rdi
    pop rsi

    mov rsp, rbp ; function epilogue
    pop rbp
.RETURN:
    ret