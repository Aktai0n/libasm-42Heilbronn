

#include "list.h"

int ft_listcmp(const t_list* list1, const t_list* list2, cmp_func cmp) {
    while (!(list1 == NULL || list2 == NULL)) {
        int cmp_result = cmp(list1->data, list2->data);
        if (cmp_result != 0) {
            return cmp_result;
        }
        list1 = list1->next;
        list2 = list2->next;
    }
    if (list1 != NULL) {
        return 1;
    } else if (list2 != NULL) {
        return -1;
    } else {
        return 0;
    }
}