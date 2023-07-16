#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <stdbool.h>

#include "./list/list.h"

static void print_string(void* ptr) {
    const char* str = ptr;
    printf("%s", str);
}

static bool list_is_sorted(const t_list* restrict list, cmp_func cmp) {
    if (list == NULL) {
        return true;
    }
    while (list->next != NULL) {
        const t_list* next = list->next;
        if (cmp(list->data, next->data) > 0) {
            return false;
        }
        list = next;
    }
    return true;
}

void compare_list_sort(t_list** list1,
                       t_list** list2,
                       cmp_func cmp,
                       print_func print) {
    printf("Testing with\n");
    ft_print_list(*list1, print);
    ft_listsort(list2, cmp);
    ft_print_list(*list2, print);
    ft_list_sort(list1, cmp);
    printf("ft_list_sort:\n");
    ft_print_list(*list1, print);
    printf("reference_list_sort:\n");
    ft_print_list(*list2, print);
    if (ft_listcmp(*list1, *list2, cmp) == 0 &&
        list_is_sorted(*list1, cmp)) {
        printf("%sTest passed!\n", BOLD_GREEN);
    } else {
        printf("%sTest failed!\n", BOLD_RED);
    }
    printf("%s\n", RESET);
}

void list_sort_test(void) {
    t_list* list1 = NULL;
    t_list* list2 = NULL;

    printf("\n%s-------------------- list sort test ------------------------%s\n", BOLD_LIGHT_BLUE, RESET);

    printf("%swith empty list:\n%s", LIGHT_BLUE, RESET);
    compare_list_sort(&list1, &list2, strcmp, print_string);

    printf("%swith string as data:\n%s", LIGHT_BLUE, RESET);
    list1 = ft_populate_list(10);
    list2 = ft_populate_list(10);
    compare_list_sort(&list1, &list2, strcmp, print_string);
    ft_listclear(&list1, free);
    ft_listclear(&list2, free);

    printf("%swith struct as data:\n%s", LIGHT_BLUE, RESET);
    long int seed = time(NULL);
    list1 = generate_test_data_list(10, (uint32_t)seed);
    list2 = generate_test_data_list(10, (uint32_t)seed);
    compare_list_sort(&list1,
                      &list2,
                      compare_test_data,
                      print_test_data);
    ft_listclear(&list1, destroy_test_data);
    ft_listclear(&list2, destroy_test_data);

    printf("%swith bigger list:\n%s", LIGHT_BLUE, RESET);
    seed = time(NULL);
    list1 = generate_test_data_list(100, (uint32_t)seed);
    list2 = generate_test_data_list(100, (uint32_t)seed);
    compare_list_sort(&list1,
                      &list2,
                      compare_test_data,
                      print_test_data);
    ft_listclear(&list1, destroy_test_data);
    ft_listclear(&list2, destroy_test_data);
}
