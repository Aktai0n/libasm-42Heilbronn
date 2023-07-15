#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "libasm.h"

void compare_write(int fd, void* buffer, size_t len) {
    printf("Testing with:\nfd = %d, len = %zu, buffer = ", fd, len);
    fwrite(buffer, len, 1, stdout);
    printf("\n");
    errno = 0;
    ssize_t std_result = write(fd, buffer, len);
    int save_ft_errno = errno;
    errno = 0;
    ssize_t ft_result = ft_write(fd, buffer, len);
    int save_std_errno = errno;
    printf("ft_write: ret_val = %ld, errno = %d\n", ft_result, save_ft_errno);
    if (save_ft_errno < 0) {
        printf("error string = %s\n", strerror(save_ft_errno));
    }
    printf("write: ret_val = %ld, errno = %d\n", std_result, save_std_errno);
    if (save_std_errno < 0) {
        printf("error string = %s\n", strerror(save_std_errno));
    }
    if (ft_result == std_result && save_ft_errno == save_std_errno) {
        printf("Test passed!\n");
    } else {
        printf("Test failed\n");
    }
    printf("\n");
}

static void print_file(int fd) {

    struct stat status = {0};
    if (fstat(fd, &status) == -1) {
        return;
    }
    size_t size = (size_t)status.st_size;
    char* buffer = malloc(size + 1);
    if (buffer == NULL) {
        return;
    }
    buffer[size] = '\0';
    read(fd, buffer, size);
    fwrite(buffer, size, 1, stdout);
    free(buffer);
}

void write_test(void) {
    printf("\n-------------------- write test ------------------------\n");
    FILE* valid_file = tmpfile();
    int valid_fd = fileno(valid_file);
    char stack_string[] = "42 Heilbronn";
    char* static_string = "Hello World!";

    compare_write(valid_fd, stack_string, sizeof(stack_string));
    printf("file contents:\n");
    print_file(valid_fd);
    rewind(valid_file);
    compare_write(STDOUT_FILENO, static_string, strlen(static_string));
    static_string = "";
    compare_write(valid_fd, static_string, strlen(static_string));
    compare_write(-1, stack_string, sizeof(stack_string));
    fclose(valid_file);
    compare_write(valid_fd, stack_string, sizeof(stack_string));
}
