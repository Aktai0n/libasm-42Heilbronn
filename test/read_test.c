#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>

#include "libasm.h"
#include "test.h"

#ifndef TESTFILE_NAME
#define TESTFILE_NAME "README.md"
#endif

void compare_read(int fd, size_t len) {
#ifdef TEST_VERBOSE
    printf("Testing with:\nfd = %d, len = %zu\n", fd, len);
#endif
    char* ft_buffer = calloc(1, len + 1);
    char* std_buffer = calloc(1, len + 1);
    errno = 0;
    ssize_t ft_result = ft_read(fd, ft_buffer, len);
    int save_ft_errno = errno;
    lseek(fd, SEEK_SET, 0);
    errno = 0;
    ssize_t std_result = read(fd, std_buffer, len);
    int save_std_errno = errno;
#ifdef TEST_VERBOSE
    printf("ft_read: ret_val = %ld, errno = %d,  buffer = %s\n", ft_result, save_ft_errno, ft_buffer);
    if (save_ft_errno != 0) {
        printf("error string = %s\n", strerror(save_ft_errno));
    }
    printf("read: ret_val = %ld, errno = %d, buffer = %s\n", std_result, save_std_errno, std_buffer);
    if (save_std_errno != 0) {
        printf("error string = %s\n", strerror(save_std_errno));
    }
#endif // TEST_VERBOSE
    if (ft_result == std_result &&
        strcmp(ft_buffer, std_buffer) == 0 &&
        save_ft_errno == save_std_errno) {
        printf("%sTest passed!\n", BOLD_GREEN);
    } else {
        printf("%sTest failed!\n", BOLD_RED);
    }
    printf("%s\n", RESET);
    free(ft_buffer);
    free(std_buffer);
}

void read_test(void) {
    printf("\n\n%s-------------------- read test ------------------------%s\n\n", BOLD_LIGHT_BLUE, RESET);
    int valid_fd = open(TESTFILE_NAME, O_RDONLY);
    if (valid_fd < 0) {
        perror("open");
        return;
    }
    int invalid_fd = open(TESTFILE_NAME, O_WRONLY);

    printf("%swith valid fd and big buffer len:\n%s", LIGHT_BLUE, RESET);
    compare_read(valid_fd, INT_MAX);
    lseek(valid_fd, SEEK_SET, 0);

    printf("%swith valid fd and small buffer len:\n%s", LIGHT_BLUE, RESET);
    compare_read(valid_fd, 10);
    lseek(valid_fd, SEEK_SET, 0);

    printf("%swith valid fd and zero buffer len:\n%s", LIGHT_BLUE, RESET);
    compare_read(valid_fd, 0);

    printf("%sfd without read permission:\n%s", LIGHT_BLUE, RESET);
    compare_read(invalid_fd, 10);

    printf("%swith invalid fd:\n%s", LIGHT_BLUE, RESET);
    compare_read(-1, 100);
    close(valid_fd);

    printf("%swith already closed fd:\n%s", LIGHT_BLUE, RESET);
    compare_read(valid_fd, SHRT_MAX);
}
