#ifndef LIST_H
#define LIST_H



#include "libasm.h"
#ifndef LIBASM_BONUS
#error "This file is only meant to be used with the libasm bonus!"
#endif

typedef int (*cmp_func)();
typedef void (*free_func)(void*);

t_list* ft_listnew(void* data);
void ft_listadd_front(t_list** begin_list, void* data);
int ft_listlen(const t_list* list);
void ft_listsort(t_list** list, int (*cmp)());

void ft_print_list(const t_list* list, void (*print_func)(void*));
void ft_listclear(t_list** list, free_func del);
t_list* ft_populate_list(size_t size);


struct s_test_data {
    int number;
    char character;
    double fraction;
};

void print_test_data(void* ptr);
struct s_test_data init_test_data(int n, char c, double f);
void destroy_test_data(void* ptr);

#endif // LIST_H