#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "libasm.h"

void compare_strcpy(const char* src) {
    size_t src_len = strlen(src);
    char* ft_dest = malloc(src_len + 1);
    char* std_dest = malloc(src_len + 1);

    printf("Testing with:\nsrc = %s, address = %p\n", src, src);
    char* ft_result = ft_strcpy(ft_dest, src);
    char* std_result = strcpy(std_dest, src);

    printf("Destination: ft_strcpy = %s, strcmp = %s\n", ft_dest, std_dest);
    printf("Return value: ft_strcpy = %s, strcpy = %s\n", ft_dest, std_dest);

    if (strcpy(ft_dest, std_dest) == 0 && strcpy(ft_dest, std_dest) == 0) {
        printf("Test passed!\n");
    } else {
        printf("Test failed!\n");
    }
    printf("\n");

    free(ft_dest);
    free(std_dest);

}

void strcpy_test(void) {
    char stack_string[] = "42 Heilbronn";
    char* static_string = "Something";
    char* heap_string = malloc(strlen(static_string) + 1);
    strcpy(heap_string, static_string);

    compare_strcpy(stack_string);
    compare_strcpy(static_string);
    compare_strcpy("");
    compare_strcpy(heap_string);
    compare_strcpy(NULL);

    free(heap_string);
}