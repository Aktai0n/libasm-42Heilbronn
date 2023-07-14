#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "list.h"

void print_test_data(void* ptr) {
    const struct s_test_data* data = ptr;
    printf("{ num = %d, char = %c, fract = %f }",
            data->number,
            data->character,
            data->fraction);
}

int compare_test_data(const struct s_test_data* lhs,
                      const struct s_test_data* rhs) {
    if (lhs->number == rhs->number) {
        return 0;
    } else if (lhs->number < rhs->number) {
        return -1;
    } else {
        return 1;
    }
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

t_list* generate_test_data_list(size_t size, uint32_t seed) {
    srand(seed);
    t_list* list = NULL;

    for (size_t i = 0; i < size; ++i) {
        int n = rand();
        char c = (char)((i % 95) + 32); // transform i to printable char
        double f = (double)n / (double)RAND_MAX;
        struct s_test_data* data = malloc(sizeof(struct s_test_data));
        if (data == NULL) {
            ft_listclear(&list, destroy_test_data);
            return NULL;
        }
        *data = init_test_data(n, c, f);
        
        t_list* node = ft_listnew(data);
        if (node == NULL) {
            destroy_test_data(data);
            ft_listclear(&list, destroy_test_data);
            return NULL;
        }
        node->next = list;
        list = node;
    }
    return list;
}

struct s_test_data* dup_test_data(const struct s_test_data to_copy) {
    struct s_test_data* data = malloc(sizeof(struct s_test_data));
    if (data == NULL) {
        return NULL;
    }
    *data = to_copy;
    return data;
}