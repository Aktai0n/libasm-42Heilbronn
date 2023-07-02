section .text
global ft_list_size



; Prototype:
;   int ft_list_size(t_list* list)
; Parameters:
;   list = rdi


ft_list_size:
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