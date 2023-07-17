#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "test.h"

void print_string(void* ptr) {
    const char* str = ptr;
    printf("%s", str);
}

void print_file(int fd, FILE* output) {
    struct stat status = {0};
    if (fstat(fd, &status) == -1) {
        perror("fstat");
        return;
    }
    size_t size = (size_t)status.st_size;
    char* buffer = malloc(size + 1);
    if (buffer == NULL) {
        perror("malloc");
        return;
    }
    buffer[size] = '\0';
    ssize_t read_ret = read(fd, buffer, size);
    if (read_ret < 0) {
        perror("read");
        free(buffer);
        return;
    }
    buffer[read_ret] = '\0';
    fwrite(buffer, size, 1, output);
    free(buffer);
}

char* read_file(int fd) {
    struct stat status = {0};
    if (fstat(fd, &status) < 0) {
        perror("fstat");
        return NULL;
    }
    size_t size = (size_t)status.st_size;
    char* buffer = malloc(size + 1);
    if (buffer == NULL) {
        perror("malloc");
        return NULL;
    }
    ssize_t read_ret = read(fd, buffer, size);
    if (read_ret < 0) {
        perror("read");
        free(buffer);
        return NULL;
    }
    buffer[read_ret] = '\0';
    return buffer;
}
