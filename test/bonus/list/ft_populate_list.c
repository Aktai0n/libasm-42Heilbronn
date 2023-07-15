#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libasm.h"
#include "list.h"

t_list* ft_populate_list(size_t size) {
    t_list* list = NULL;
    char buffer[1000] = {0};

    for (size_t i = 0; i < size; ++i) {
        snprintf(buffer, sizeof(buffer), "node %zu", i);
        char* data = malloc(strlen(buffer) + 1);
        if (data == NULL) {
            ft_listclear(&list, free);
            return NULL;
        }
        strcpy(data, buffer);

        t_list* node = ft_listnew(data);
        if (node == NULL) {
            ft_listclear(&list, free);
            return NULL;
        }
        node->next = list;
        list = node;
    }
    return list;
}
