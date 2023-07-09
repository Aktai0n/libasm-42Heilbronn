#include <stdlib.h>

#include "libasm.h"
#include "list.h"



void ft_listclear(t_list** list, free_func del) {
    if (list == NULL) {
        return;
    }
    for (t_list* node = *list; node != NULL;) {
        t_list* next = node->next;
        del(node->data);
        free(node);
        node = next;
    }
    *list = NULL;
}