#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "libasm.h"
#include "./list/list.h"
#include "test.h"

void compare_list_remove_if(t_list** list1,
                            t_list** list2,
                            void* to_remove,
                            cmp_func cmp,
                            free_func del,
                            print_func print) {
    (void)print;
#ifdef TEST_VERBOSE
    printf("Testing with:\n");
    ft_print_list(*list1, print);
    printf("To remove:\n");
    print(to_remove);
    printf("\n");
#endif
    ft_list_remove_if(list1, to_remove, cmp, del);
    ft_listdel_pred(list2, to_remove, cmp, del);
#ifdef TEST_VERBOSE
    printf("ft_list_remove_if:\n");
    ft_print_list(*list1, print);
    printf("reference_list_remove_if:\n");
    ft_print_list(*list2, print);
#endif
    if (ft_listcmp(*list1, *list2, cmp) == 0) {
        printf("%sTest passed!\n", BOLD_GREEN);
    } else {
        printf("%sTest failed!\n", BOLD_RED);
    }
    printf("%s\n", RESET);
}

void list_remove_if_test(void) {
    printf("\n\n%s-------------------- list remove if test ------------------------%s\n\n", BOLD_LIGHT_BLUE, RESET);

    t_list* list1 = NULL;
    t_list* list2 = NULL;

    printf("%swith empty list:\n%s", LIGHT_BLUE, RESET);
    compare_list_remove_if(&list1,
                           &list2,
                           "unused string",
                           strcmp,
                           free,
                           print_string);

    list1 = ft_populate_list(10);
    list2 = ft_populate_list(10);

    printf("%sremove from the end:\n%s", LIGHT_BLUE, RESET);
    compare_list_remove_if(&list1,
                           &list2,
                           "node 0",
                           strcmp,
                           free,
                           print_string);
    
    printf("%sremove from the beginning:\n%s", LIGHT_BLUE, RESET);
    compare_list_remove_if(&list1,
                           &list2,
                           "node 9",
                           strcmp,
                           free,
                           print_string);
    
    printf("%sremove from the middle:\n%s", LIGHT_BLUE, RESET);
    compare_list_remove_if(&list1,
                           &list2,
                           "node 5",
                           strcmp,
                           free,
                           print_string);

    printf("%stry to remove nonexisting element:\n%s", LIGHT_BLUE, RESET);
    compare_list_remove_if(&list1,
                           &list2,
                           "Not in there",
                           strcmp,
                           free,
                           print_string);
    
    printf("%sremove two elements:\n%s", LIGHT_BLUE, RESET);
    char str[] = "node 4";
    char* str1 = malloc(sizeof(str));
    strcpy(str1, str);
    char* str2 = malloc(sizeof(str));
    strcpy(str2, str);
    ft_listadd_front(&list1, str1);
    ft_listadd_front(&list2, str2);
    compare_list_remove_if(&list1,
                           &list2,
                           str,
                           strcmp,
                           free,
                           print_string);
    
    ft_listclear(&list1, free);
    ft_listclear(&list2, free);

    long int seed = time(NULL);
    list1 = generate_test_data_list(10, (uint32_t)seed);
    list2 = generate_test_data_list(10, (uint32_t)seed);

    struct s_test_data data_to_remove = init_test_data(1, '*', 0.333);
    struct s_test_data* data1 = dup_test_data(data_to_remove);
    struct s_test_data* data2 = dup_test_data(data_to_remove);

    ft_listadd_front(&list1, data1);
    ft_listadd_front(&list2, data2);

    printf("%swith struct s_test_data:\n%s", LIGHT_BLUE, RESET);
    compare_list_remove_if(&list1,
                           &list2,
                           &data_to_remove,
                           compare_test_data,
                           destroy_test_data,
                           print_test_data);

    ft_listclear(&list1, destroy_test_data);
    ft_listclear(&list2, destroy_test_data);
}
