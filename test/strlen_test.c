#include <string.h>
#include <stdio.h>

#include "libasm.h"

void compare(const char* s) {
    printf("Testing with %s\n", s);
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