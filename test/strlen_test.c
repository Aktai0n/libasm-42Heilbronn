#include <string.h>
#include <stdio.h>

#include "libasm.h"

void compare_strlen(const char* s) {
    printf("Testing with %s\n", s);
    size_t ft_len = ft_strlen(s);
    size_t len = strlen(s);
    
    printf("ft_strlen = %zu, strlen = %zu\n", ft_len, len);
    if (strlen(s) == ft_strlen(s)) {
        printf("Test passed!\n");
    } else {
        printf("Test failed!\n");
    }
}

void strlen_test(void) {
    char stack_string[] = "Hello World";

    compare_strlen("Hello World");
    compare_strlen("42");
    compare_strlen("");
    compare_strlen(stack_string);
}
