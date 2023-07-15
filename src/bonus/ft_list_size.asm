section .text

%include "platform_specific.inc"

global FT_LIST_SIZE



; Prototype:
;   int ft_list_size(t_list* list)
; Parameters:
;   list = rdi

FT_LIST_SIZE:
    xor rax, rax ; int size = 0
    test rdi, rdi ; list == NULL
    jz .BREAK1

    .LOOP1:
        mov rdi, QWORD [rdi + 8] ; list = list->next
        inc rax ; ++size
        test rdi, rdi ; list != NULL
        jnz .LOOP1
    .BREAK1:
    ret
