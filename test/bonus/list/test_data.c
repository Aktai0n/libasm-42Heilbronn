#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "list.h"

void print_test_data(void* ptr) {
    const struct s_test_data* data = ptr;
    printf("num = %d, char = %c, fract = %f\n",
            data->number,
            data->character,
            data->fraction);
}

struct s_test_data init_test_data(int n, char c, double f) {
    return (struct s_test_data){
        .number = n,
        .character = c,
        .fraction = f,
    };
}

void destroy_test_data(void* ptr) {
    struct s_test_data* data = ptr;
    free(data);
}