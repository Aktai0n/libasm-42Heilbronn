#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "libasm.h"

void compare_strcmp(const char* s1, const char* s2) {
#ifdef TEST_VERBOSE
    printf("Testing with:\ns1 = %s, address = %p\ns2 = %s, address = %p\n", 
           s1,
           (void*)s1,
           s2,
           (void*)s2);
#endif
    int ft_result = ft_strcmp(s1, s2);
    int std_result = strcmp(s1, s2);
#ifdef TEST_VERBOSE
    printf("ft_strcmp = %d\nstrcmp = %d\n", ft_result, std_result);
#endif
    // the returned values can vary as long as they are both positive,
    // negative or zero
    if ((ft_result > 0 && std_result > 0) ||
        (ft_result < 0 && std_result < 0) ||
        (ft_result == 0 && std_result == 0)) {
        printf("%sTest passed!\n", BOLD_GREEN);
    } else {
        printf("%sTest failed!\n", BOLD_RED);
    }
    printf("%s\n", RESET);
}

void strcmp_test(void) {
    printf("\n\n%s-------------------- strcmp test ------------------------%s\n\n", BOLD_LIGHT_BLUE, RESET);
    char stack_string1[] = "42 Heilbronn";
    char* heap_string = malloc(strlen(stack_string1) + 1);
    strcpy(heap_string, stack_string1);

    printf("%ss1 has additional tabs at the end:\n%s", LIGHT_BLUE, RESET);
    compare_strcmp("42 Heilbronn\t\t", stack_string1);

    printf("%ss2 has additional newline at the end:\n%s", LIGHT_BLUE, RESET);
    compare_strcmp(stack_string1, "42 Heilbronn\n");

    printf("%ss2 is empty:\n%s", LIGHT_BLUE, RESET);
    compare_strcmp("hello World", "");

    printf("%sboth are empty:\n%s", LIGHT_BLUE, RESET);
    compare_strcmp("", "");

    printf("%ss1 and s2 are identcal:\n%s", LIGHT_BLUE, RESET);
    compare_strcmp(stack_string1, heap_string);

    printf("%ss1 and s2 are the same string:\n%s", LIGHT_BLUE, RESET);
    compare_strcmp(heap_string, heap_string);

    free(heap_string);
}
