
#include "list.h"
#include <stdlib.h>

t_list* ft_listnew(void* data) {
    t_list* node = malloc(sizeof(t_list));
    if (!node) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}
