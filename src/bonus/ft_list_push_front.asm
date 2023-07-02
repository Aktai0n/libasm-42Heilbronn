section .text
global ft_list_push_front

%include "platform_specific.inc"

extern MALLOC

; Prototype:
;   void ft_list_push_front(t_list** list, void* data)
; Parameters:
;   list = rdi
;   data = rsi
; Stack Layout:
;   rbp + 0 = list
ft_list_push_front:
    push rbp ; function prologue
    mov rbp, rsp

    test rdi, rdi ; list == NULL
    jz .RETURN

    push rdi
    mov rdi, 16 ; sizeof(t_list) == 16 bytes
    call MALLOC
    test rax, rax ; new_node == NULL
    jz .RETURN

    mov QWORD [rax], rsi ; new_node->data = data
    mov rdx, QWORD [rbp] ; t_list* temp = *list
    mov QWORD [rax + 8], rdx ; new_node->next = temp
    mov QWORD [rbp], rax ; *list = new_node

.RETURN:
    mov rsp, rbp ; function epilogue
    pop rbp
    ret


