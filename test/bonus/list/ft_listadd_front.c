#include "list.h"
#include <stdlib.h>

void ft_listadd_front(t_list** begin_list, void* data) {
    if (begin_list == NULL) {
        return;
    }
    t_list* new_node = malloc(sizeof(t_list));
    if (new_node == NULL) {
        return;
    }
    new_node->data = data;
    if (*begin_list != NULL) {
        new_node->next = *begin_list;
    } else {
        new_node->next = NULL;
    }
    *begin_list = new_node;
}