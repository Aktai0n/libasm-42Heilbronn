#include "list.h"
#include <stdlib.h>
#include <stdio.h>

void ft_listdel_pred(t_list** list, void* data, cmp_func pred, free_func del) {
    if (list == NULL) {
        return;
    }
    t_list* prev = NULL;
    for (t_list* node = *list; node != NULL;) {
        t_list* next = node->next;
        if (pred(node->data, data) == 0) {
            if (prev == NULL) {
                *list = next; // update the listhead
            } else {
                prev->next = node->next;
            }
            del(node->data);
            free(node);
            node = NULL;
        }
        prev = node;
        node = next;
    }
}
