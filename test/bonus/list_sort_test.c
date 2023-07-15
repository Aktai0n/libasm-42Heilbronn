#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#include "./list/list.h"

static void print_string(void* ptr) {
    const char* str = ptr;
    printf("%s", str);
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
    if (ft_listcmp(*list1, *list2, cmp) == 0) {
        printf("%sTest passed!\n", BOLD_GREEN);
    } else {
        printf("%sTest failed!\n", BOLD_RED);
    }
    printf("%s\n", RESET);
}

void list_sort_test(void) {
    long int seed = time(NULL);
    t_list* list1 = NULL;
    t_list* list2 = NULL;

    printf("\n%s-------------------- list sort test ------------------------%s\n", BOLD_LIGHT_BLUE, RESET);

    compare_list_sort(&list1, &list2, strcmp, print_string);

    list1 = ft_populate_list(10);
    list2 = ft_populate_list(10);
    compare_list_sort(&list1, &list2, strcmp, print_string);
    ft_listclear(&list1, free);
    ft_listclear(&list2, free);

    list1 = generate_test_data_list(10, (uint32_t)seed);
    list2 = generate_test_data_list(10, (uint32_t)seed);
    compare_list_sort(&list1,
                      &list2,
                      compare_test_data,
                      print_test_data);
    ft_listclear(&list1, destroy_test_data);
    ft_listclear(&list2, destroy_test_data);

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
