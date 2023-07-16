section .text

%include "platform_specific.inc"

global FT_LIST_PUSH_FRONT

extern MALLOC

; Prototype:
;   void ft_list_push_front(t_list** list, void* data)
; Parameters:
;   list = rdi
;   data = rsi

FT_LIST_PUSH_FRONT:
    test rdi, rdi ; list == NULL
    jz .FAST_RETURN

    push rbp ; function prologue
    mov rbp, rsp

    push rdi ; save registers
    push rsi ; malloc zeroes rsi, so save it as well

    mov rdi, 16 ; sizeof(t_list) == 16 bytes
    call MALLOC

    pop rsi ; restore registers
    pop rdi

    test rax, rax ; new_node == NULL
    jz .RETURN

    mov QWORD [rax], rsi ; new_node->data = data
    mov rdx, QWORD [rdi] ; t_list* temp = *list
    mov QWORD [rax + 8], rdx ; new_node->next = temp
    mov QWORD [rdi], rax ; *list = new_node

.RETURN:
    mov rsp, rbp ; function epilogue
    pop rbp
.FAST_RETURN:
    ret


