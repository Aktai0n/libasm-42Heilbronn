#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>

#include "libasm.h"

#ifndef TESTFILE_NAME
#define TESTFILE_NAME "README.md"
#endif

void compare_read(int fd, size_t len) {
    printf("Testing with:\nfd = %d, len = %zu\n", fd, len);
    char* ft_buffer = calloc(1, len + 1);
    char* std_buffer = calloc(1, len + 1);
    errno = 0;
    ssize_t ft_result = ft_read(fd, ft_buffer, len);
    int save_ft_errno = errno;
    lseek(fd, SEEK_SET, 0);
    errno = 0;
    ssize_t std_result = read(fd, std_buffer, len);
    int save_std_errno = errno;
    printf("ft_read: ret_val = %ld, errno = %d,  buf = %s\n", ft_result, save_ft_errno, ft_buffer);
    if (save_ft_errno < 0) {
        printf("error string = %s\n", strerror(save_ft_errno));
    }
    printf("read: ret_val = %ld, errno = %d, buffer = %s\n", std_result, save_std_errno, std_buffer);
    if (save_std_errno < 0) {
        printf("error string = %s\n", strerror(save_std_errno));
    }
    if (ft_result == std_result && strcmp(ft_buffer, std_buffer) == 0 && save_ft_errno == save_std_errno) {
        printf("Test passed!\n");
    } else {
        printf("Test failed!\n");
    }
    printf("\n");
    free(ft_buffer);
    free(std_buffer);
}

void read_test(void) {
    printf("\n-------------------- read test ------------------------\n");
    int valid_fd = open(TESTFILE_NAME, O_RDONLY);
    int invalid_fd = open(TESTFILE_NAME, O_WRONLY);

    compare_read(valid_fd, ULONG_MAX);
    compare_read(valid_fd, SHRT_MAX);
    lseek(valid_fd, SEEK_SET, 0);
    compare_read(valid_fd, 0);
    compare_read(invalid_fd, 10);
    compare_read(-1, 100);
    close(valid_fd);
    compare_read(valid_fd, SHRT_MAX);
}