#include <string.h>
#include <stdio.h>

// #include "libasm.h"
size_t ft_strlen(const char* str);

void compare(const char* s) {
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

void strlen_test() {
    char stack_string[] = "Hello World";

    compare("Hello World");
    compare("42");
    compare("");
    compare(stack_string);
}

int main(void) {
    strlen_test();
    return 0;
}