#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>


#include "libasm.h"
#include "test.h"

#ifndef TESTFILE_NAME
#define TESTFILE_NAME "README.md"
#endif

static void compare_write(int fd, void* buffer, size_t len) {
#ifdef TEST_VERBOSE
    printf("Testing with:\nfd = %d, len = %zu, buffer = ", fd, len);
    fwrite(buffer, len, 1, stdout);
    printf("\n");
#endif
    errno = 0;
    ssize_t std_result = write(fd, buffer, len);
    int save_ft_errno = errno;
    errno = 0;
    ssize_t ft_result = ft_write(fd, buffer, len);
    int save_std_errno = errno;
#ifdef TEST_VERBOSE
    printf("ft_write: ret_val = %ld, errno = %d\n", ft_result, save_ft_errno);
    if (save_ft_errno < 0) {
        printf("error string = %s\n", strerror(save_ft_errno));
    }
    printf("write: ret_val = %ld, errno = %d\n", std_result, save_std_errno);
    if (save_std_errno < 0) {
        printf("error string = %s\n", strerror(save_std_errno));
    }
#endif
    if (ft_result == std_result && save_ft_errno == save_std_errno) {
        printf("%sTest passed!\n", BOLD_GREEN);
    } else {
        printf("%sTest failed!\n", BOLD_RED);
    }
    printf("%s\n", RESET);
}

void write_test(void) {
    printf("\n\n%s-------------------- write test ------------------------%s\n\n", BOLD_LIGHT_BLUE, RESET);
    FILE* valid_file = tmpfile();
    int valid_fd = fileno(valid_file);
    char stack_string[] = "42 Heilbronn";
    char* static_string = "Hello World!";
    int fd = open(TESTFILE_NAME, O_RDONLY);
    char* heap_string = read_file(fd);
    close(fd);

    printf("%swith valid fd and stack buffer:\n%s", LIGHT_BLUE, RESET);
    compare_write(valid_fd, stack_string, sizeof(stack_string));
#ifdef TEST_VERBOSE
    printf("file contents:\n");
    print_file(valid_fd, stdout);
#endif
    rewind(valid_file);

    printf("%swith valid fd and big heap buffer:\n%s", LIGHT_BLUE, RESET);
    compare_write(valid_fd, heap_string, strlen(heap_string));

    printf("%sto stdout with string literal:\n%s", LIGHT_BLUE, RESET);
    compare_write(STDOUT_FILENO, static_string, strlen(static_string));

    printf("%swith empty buffer and size zero:\n%s", LIGHT_BLUE, RESET);
    static_string = "";
    compare_write(valid_fd, static_string, strlen(static_string));

    printf("%swith invalid fd:\n%s", LIGHT_BLUE, RESET);
    compare_write(-1, stack_string, sizeof(stack_string));

    printf("%swith already closed fd:\n%s", LIGHT_BLUE, RESET);
    fclose(valid_file);
    compare_write(valid_fd, stack_string, sizeof(stack_string));
    free(heap_string);
}
