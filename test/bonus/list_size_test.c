#include <stdio.h>
#include <stdlib.h>


#include "libasm.h"
#include "list/list.h"

static void print_string(void* ptr) {
    const char* str = ptr;
    printf("%s", str);
}

void compare_list_size(t_list* list) {
    printf("Testing with:\n");
    ft_print_list(list, print_string);
    int ft_result = ft_list_size(list);
    int reference_result = ft_listlen(list);
    printf("ft_list_size: %d\n", ft_result);
    printf("listsize_reference: %d\n", reference_result);
    if (ft_result == reference_result) {
        printf("%sTest passed!\n", BOLD_GREEN);
    } else {
        printf("%sTest failed!\n", BOLD_RED);
    }
    printf("%s\n", RESET);

}


void list_size_test(void) {
    printf("\n%s-------------------- list size test ------------------------%s\n", BOLD_LIGHT_BLUE, RESET);
    t_list* list1 = ft_populate_list(10);
    t_list* list2 = ft_populate_list(1000);
    t_list stack_list = {
        .data = "Hello world",
        .next = NULL
    };

    compare_list_size(list1);
    compare_list_size(list2);
    compare_list_size(NULL);
    compare_list_size(&stack_list);

    ft_listclear(&list1, free);
    ft_listclear(&list2, free);

}