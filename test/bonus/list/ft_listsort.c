#include "list.h"

static void swap_nodes(t_list* node1, t_list* node2) {
    t_list temp = *node1;
    *node1 = *node2;
    *node2 = temp;
}

void ft_listsort(t_list** list, cmp_func cmp) {
    if (list == NULL || *list == NULL) {
        return;
    }
    for (t_list* outer_node = *list; outer_node->next != NULL; outer_node = outer_node->next) {
        for (t_list* node = outer_node; node->next != NULL; node = node->next) {
            t_list* next = node->next;
            int cmp_result = cmp(node->data, next->data);
            if (cmp_result > 0) {
                swap_nodes(node, next);
            }
        }
    }
}
