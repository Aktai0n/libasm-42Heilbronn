#include <unistd.h>
#include <stdio.h>
#include <errno.h>



int main() {
    ssize_t write_ret = write(1, "Testing\n", 8);
    if (write_ret == -1) {
        printf("write failed because %d\n", errno);
    }
}