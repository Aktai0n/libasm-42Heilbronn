#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#include "libasm.h"
#include "test.h"

#ifndef TESTFILE_NAME
#define TESTFILE_NAME "README.md"
#endif

void compare_strlen(const char* s) {
#ifdef TEST_VERBOSE
    printf("Testing with:\nstr = %s\n", s);
#endif
    size_t ft_len = ft_strlen(s);
    size_t len = strlen(s);

#ifdef TEST_VERBOSE
    printf("ft_strlen: %zu\nstrlen: %zu\n", ft_len, len);
#endif
    if (ft_len == len) {
        printf("%sTest passed!\n", BOLD_GREEN);
    } else {
        printf("%sTest failed!\n", BOLD_RED);
    }
    printf("%s\n", RESET);
}

void strlen_test(void) {
    printf("\n\n%s-------------------- strlen test ------------------------%s\n\n", BOLD_LIGHT_BLUE, RESET);
    char stack_string[] = "Hello World";
    int fd = open(TESTFILE_NAME, O_RDONLY);
    char* heap_string = read_file(fd);
    close(fd);

    printf("%sstring literal:\n%s", LIGHT_BLUE, RESET);
    compare_strlen("Hello World");

    printf("%slong string on the heap:\n%s", LIGHT_BLUE, RESET);
    compare_strlen(heap_string);

    printf("%sempty string:\n%s", LIGHT_BLUE, RESET);
    compare_strlen("");

    printf("%sstring on the stack:\n%s", LIGHT_BLUE, RESET);
    compare_strlen(stack_string);


}
