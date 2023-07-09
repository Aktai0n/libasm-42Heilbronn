#include <stdio.h>

#include "list.h"
#include "libasm.h"

void ft_print_list(const t_list* list, void (*print_func)(void*)) {
    if (list == NULL) {
        printf("(empty)\n");
        return;
    }
    size_t size = 0;
    for (; list != NULL; list = list->next) {
        print_func(list->data);
        printf(" -> ");
        ++size;
    }
    printf("(null)\n");
    printf("list size = %zu\n", size);
}