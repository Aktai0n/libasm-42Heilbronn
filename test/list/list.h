#ifndef LIST_H
#define LIST_H


#define LIBASM_BONUS // Remove me!!!

#ifndef LIBASM_BONUS
#error "This file is only meant to be used with the libasm bonus!"
#endif

#include "libasm.h"

typedef int (*cmp_func)();
typedef void (*free_func)(void*);

t_list* ft_listnew(void* data);
void ft_listadd_front(t_list** begin_list, void* data);
size_t ft_listlen(const t_list* list);
void ft_listsort(t_list** list, int (*cmp)());

#endif // LIST_H