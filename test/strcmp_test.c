#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#if 0
int ft_strcmp(const char* s1, const char* s2) {
    for (size_t i = 0; !(s1[i] == '\0' && s2[i] == '\0'); ++i) {
        if (s1[i] != s2[i]) {
            return (unsigned char)s1[i] - (unsigned char)s2[i];
        }
    }
    return 0;
}
#else
int ft_strcmp(const char* s1, const char* s2) {
    for (;!(*s1 == '\0' && *s2 == '\0'); ++s1, ++s2) {
        if (*s1 != *s2) {
            return (unsigned char)*s1 - (unsigned char)*s2;
        }
    }
    return 0;
}

#endif

void compare_strcmp(const char* s1, const char* s2) {
    printf("Testing with:\ns1 = %s, address = %p\ns2 = %s, address = %p\n", s1, s1, s2, s2);
    int ft_result = ft_strcmp(s1, s2);
    int std_result = strcmp(s1, s2);
    printf("ft_strcmp = %d, strcmp = %d\n", ft_result, std_result);
    if (ft_result == std_result) {
        printf("Test passed!\n");
    } else {
        printf("Test failed!\n");
    }
    printf("\n");
}

void strcmp_test() {
    char stack_string1[] = "42 Heilbronn";
    char* heap_string = malloc(strlen(stack_string1) + 1);
    strcpy(heap_string, stack_string1);

    compare_strcmp("42 Heilbronn\n", stack_string1);
    compare_strcmp(stack_string1, "42 Heilbronn\n");
    compare_strcmp("hello World", "");
    compare_strcmp("", "");
    compare_strcmp(stack_string1, heap_string);
    compare_strcmp(heap_string, heap_string);

    free(heap_string);
}


int main() {
    strcmp_test();
    return 0;
}