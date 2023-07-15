#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "libasm.h"

char* my_strdup(const char* str) {
    if (str == NULL) {
        return NULL;
    }
    size_t len = strlen(str);
    char* dest = malloc(len + 1);
    if (dest == NULL) {
        return NULL;
    }
    strcpy(dest, str);
    dest[len] = '\0';
    return dest;
}

/*
*   Determine whether the strdup in string.h
*   is available
*/
#if (defined _POSIX_C_SOURCE && \
    (_XOPEN_SOURCE >= 500 || \
    _POSIX_C_SOURCE >= 200809L)) || \
    (defined __DARWIN_C_LEVEL && \
    __DARWIN_C_LEVEL >= 200112L)
#define reference_strdup(str) strdup(str)
#else
#define reference_strdup(str) my_strdup(str)
#endif

void compare_strdup(const char* str) {
    printf("Testing with:\nstr = %s, address = %p\n", str, (void*)str);
    char* std_result = reference_strdup(str);
    char* ft_result = ft_strdup(str);
    printf("ft_strdup: %s\n", ft_result);
    printf("strdup: %s\n", std_result);
    if (strcmp(std_result, ft_result) == 0) {
        printf("Test passed!\n");
    } else {
        printf("Test failed\n");
    }
    printf("\n");
    free(ft_result);
    free(std_result);
}

void strdup_test(void) {
    char stack_string[] = "42 Heilbronn";
    char* static_string = "Something";
    char* heap_string = malloc(strlen(static_string) + 1);
    strcpy(heap_string, static_string);

    compare_strdup(stack_string);
    compare_strdup(static_string);
    compare_strdup(heap_string);
    compare_strdup("");

    free(heap_string);
}
