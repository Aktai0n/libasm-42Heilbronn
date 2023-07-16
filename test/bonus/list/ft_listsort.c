#include "list.h"

void ft_listsort(t_list** list, cmp_func cmp) {
    if (list == NULL || *list == NULL) {
        return;
    }
    for (t_list* outer_node = *list; outer_node != NULL; outer_node = outer_node->next) {
        for (t_list* inner_node = outer_node->next; inner_node != NULL; inner_node = inner_node->next) {
            if (cmp(outer_node->data, inner_node->data) > 0) {
                void* temp_data = outer_node->data;
                outer_node->data = inner_node->data;
                inner_node->data = temp_data;
            }
        }
    }
}
