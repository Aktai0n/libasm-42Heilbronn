#include "list.h"

int ft_listlen(const t_list* list) {
    int len = 0;
    while (list != NULL) {
        ++len;
        list = list->next;
    }
    return len;
}
