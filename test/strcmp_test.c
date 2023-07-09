#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "libasm.h"

#if 0
int ft_strcmp(const char* s1, const char* s2) {
    size_t i = 0;
    for (;!(s1[i] == '\0' && s2[i] == '\0'); ++i) {
        if (s1[i] != s2[i]) {
            return (unsigned char)s1[i] - (unsigned char)s2[i];
        }
    }
    if (s1[i] == '\0' && s2[i] == '\0') {
        return 0;
    } else if (s1[i] == '\0') {
        return 1;
    } else {
        return -1;
    }
}

#endif

void compare_strcmp(const char* s1, const char* s2) {
    printf("Testing with:\ns1 = %s, address = %p\ns2 = %s, address = %p\n", s1, s1, s2, s2);
    int ft_result = ft_strcmp(s1, s2);
    int std_result = strcmp(s1, s2);
    printf("ft_strcmp = %d, strcmp = %d\n", ft_result, std_result);
    // the returned values can vary as long as they are both positive,
    // negative or zero
    if ((ft_result > 0 && std_result > 0) ||
        (ft_result < 0 && std_result < 0) ||
        (ft_result == 0 && std_result == 0)) {
        printf("Test passed!\n");
    } else {
        printf("Test failed!\n");
    }
    printf("\n");
}

void strcmp_test(void) {
    char stack_string1[] = "42 Heilbronn";
    char* heap_string = malloc(strlen(stack_string1) + 1);
    strcpy(heap_string, stack_string1);

    compare_strcmp("42 Heilbronn\n\n", stack_string1);
    compare_strcmp(stack_string1, "42 Heilbronn\n");
    compare_strcmp("hello World", "");
    compare_strcmp("", "");
    compare_strcmp(stack_string1, heap_string);
    compare_strcmp(heap_string, heap_string);

    free(heap_string);
}

#ifdef IS_STANDALONE

int main(void) {
    strcmp_test();
    return 0;
}

#endif // IS_STANDALONE