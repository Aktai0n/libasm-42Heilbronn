#include "list.h"

size_t ft_listlen(const t_list* list) {
    size_t len = 0;
    while (list != NULL) {
        ++len;
        list = list->next;
    }
    return len;
}

int main(void) {
    return 0;
}