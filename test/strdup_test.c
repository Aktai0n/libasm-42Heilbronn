#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "libasm.h"
#include "test.h"

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

static void compare_strdup(const char* str) {
#ifdef TEST_VERBOSE
    printf("Testing with:\nstr = %s, address = %p\n", str, (void*)str);
#endif
    char* std_result = reference_strdup(str);
    char* ft_result = ft_strdup(str);
#ifdef TEST_VERBOSE
    printf("ft_strdup: %s\n", ft_result);
    printf("strdup: %s\n", std_result);
#endif
    if (strcmp(std_result, ft_result) == 0) {
        printf("%sTest passed!\n", BOLD_GREEN);
    } else {
        printf("%sTest failed!\n", BOLD_RED);
    }
    printf("%s\n", RESET);
    free(ft_result);
    free(std_result);
}

void strdup_test(void) {
    printf("\n\n%s-------------------- strdup test ------------------------%s\n\n", BOLD_LIGHT_BLUE, RESET);
    char stack_string[] = "42 Heilbronn";
    char* static_string = "Something";
    char* heap_string = malloc(strlen(static_string) + 1);
    strcpy(heap_string, static_string);

    printf("%sstring on the stack:\n%s", LIGHT_BLUE, RESET);
    compare_strdup(stack_string);

    printf("%sstring literal:\n%s", LIGHT_BLUE, RESET);
    compare_strdup(static_string);

    printf("%sstring on the heap:\n%s", LIGHT_BLUE, RESET);
    compare_strdup(heap_string);

    printf("%sempty string:\n%s", LIGHT_BLUE, RESET);
    compare_strdup("");

    free(heap_string);
}
