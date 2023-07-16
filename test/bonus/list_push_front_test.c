#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libasm.h"
#include "./list/list.h"
#include "test.h"

static void print_string(void* ptr) {
    const char* str = ptr;
    printf("%s", str);
}

void compare_list_push_front(t_list** list1,
                             t_list** list2,
                             void* data_to_add,
                             size_t data_len,
                             print_func print) {
    t_list* save_list1_head = *list1;
#ifdef TEST_VERBOSE
    printf("Testing with:\n");
    ft_print_list(*list1, print);
#endif
    void* data1 = malloc(data_len);
    memcpy(data1, data_to_add, data_len);
    void* data2 = malloc(data_len);
    memcpy(data2, data_to_add, data_len);
    ft_listadd_front(list2, data2);
    ft_list_push_front(list1, data1);
#ifdef TEST_VERBOSE
    printf("ft_list_push_front:\n");
    ft_print_list(*list1, print);
    printf("reference_list_push_front:\n");
    ft_print_list(*list2, print);
#endif
    if (memcmp((*list1)->data, (*list2)->data, data_len) == 0 &&
        (*list1)->next == save_list1_head) {
        printf("%sTest passed!\n", BOLD_GREEN);
    } else {
        printf("%sTest failed!\n", BOLD_RED);
    }
    printf("%s\n", RESET);
}

void list_push_front_test(void) {
    printf("\n\n%s-------------------- list push front test ------------------------%s\n\n", BOLD_LIGHT_BLUE, RESET);
    t_list* list1 = ft_populate_list(100);
    t_list* list2 = ft_populate_list(100);
    char teststring[] = "Some string";

    printf("%swith string list:\n%s", LIGHT_BLUE, RESET);
    compare_list_push_front(&list1,
                            &list2,
                            teststring,
                            sizeof(teststring),
                            print_string);
    
    printf("%swith string list:\n%s", LIGHT_BLUE, RESET);
    compare_list_push_front(&list1,
                            &list2,
                            teststring,
                            sizeof(teststring),
                            print_string);

    ft_listclear(&list1, free);
    ft_listclear(&list2, free);

    struct s_test_data data = init_test_data(1, '*', 0.33);

    printf("%swith empty list:\n%s", LIGHT_BLUE, RESET);
    compare_list_push_front(&list1,
                            &list2,
                            &data,
                            sizeof(data),
                            print_test_data);

    printf("%swith struct s_test_data:\n%s", LIGHT_BLUE, RESET);
    compare_list_push_front(&list1,
                            &list2,
                            &data,
                            sizeof(data),
                            print_test_data);
    
    ft_listclear(&list1, destroy_test_data);
    ft_listclear(&list2, destroy_test_data);

    

}
