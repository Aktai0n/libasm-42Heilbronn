#include "list.h"

void ft_listadd_front(t_list** begin_list, void* data) {
    if (begin_list == NULL) {
        return;
    }
    t_list* new_node = ft_listnew(data);
    if (new_node == NULL) {
        return;
    }
    if (*begin_list != NULL) {
        new_node->next = *begin_list;
    }
    *begin_list = new_node;
}