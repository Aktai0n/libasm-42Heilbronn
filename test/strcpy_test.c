#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "libasm.h"

static void compare_strcpy(const char* src) {
    size_t src_len = strlen(src);
    char* ft_dest = malloc(src_len + 1);
    char* std_dest = malloc(src_len + 1);

#ifdef TEST_VERBOSE
    printf("Testing with:\nsrc = %s, address = %p\n", src, (void*)src);
#endif
    char* std_result = strcpy(std_dest, src);
    char* ft_result = ft_strcpy(ft_dest, src);
#ifdef TEST_VERBOSE
    printf("ft_strcpy:\ndest = %s, return value = %s\n", ft_dest, ft_result);
    printf("strcpy:\ndest = %s, return value = %s\n", std_dest, std_result);
#endif
    if (strcmp(ft_dest, std_dest) == 0 && strcmp(ft_result, std_result) == 0) {
        printf("%sTest passed!\n", BOLD_GREEN);
    } else {
        printf("%sTest failed!\n", BOLD_RED);
    }
    printf("%s\n", RESET);
    free(ft_dest);
    free(std_dest);

}

void strcpy_test(void) {
    printf("\n\n%s-------------------- strcpy test ------------------------%s\n\n", BOLD_LIGHT_BLUE, RESET);
    char stack_string[] = "42 Heilbronn";
    char* static_string = "Something";
    char* heap_string = malloc(strlen(static_string) + 1);
    strcpy(heap_string, static_string);

    printf("%sstring on the stack:\n%s", LIGHT_BLUE, RESET);
    compare_strcpy(stack_string);

    printf("%sstring literal:\n%s", LIGHT_BLUE, RESET);
    compare_strcpy(static_string);

    printf("%sempty string:\n%s", LIGHT_BLUE, RESET);
    compare_strcpy("");

    printf("%sstring on the heap:\n%s", LIGHT_BLUE, RESET);
    compare_strcpy(heap_string);

    free(heap_string);
}
