#ifndef LIST_H
#define LIST_H

#include <stdint.h>

#include "libasm.h"
#ifndef LIBASM_BONUS
#error "This file is only meant to be used with the libasm bonus!"
#endif

typedef int (*cmp_func)();
typedef void (*free_func)(void*);
typedef void (*print_func)(void*);

/// @brief creates a new t_list element with next set to NULL
///        and data set to the given parameter
/// @param data a pointer to any data that should be stored
///             in the data segment of the new node
/// @return the newly created node or NULL if the allocation fails
t_list* ft_listnew(void* data);

/// @brief creates a new t_list node at the beginning of
///        the list pointed to by begin_list with its data set to
///        the data parameter
/// @param begin_list a pointer to the head of a t_list linked list
///        if the head is NULL, it's set to the created node
/// @param data a pointer to any type of data to be stored in the list
void ft_listadd_front(t_list** begin_list, void* data);

/// @brief calculates the length of the linked list
/// @param list the head of the linked list
/// @return the length of the linked list
int ft_listlen(const t_list* list);

/// @brief sorts the linked list in O(n²)
/// @param list a pointer to the head of a linked list
/// @param cmp a function pointer to compare the data segments of the
///            linked list. Its used as follows: cmp(node->data, node->next->data)
void ft_listsort(t_list** list, cmp_func cmp);

/// @brief erases all nodes in the linked list where the comparison function returns zero to
/// @param list a pointer to the head of a linked list
/// @param data the reference data which all elements are compared to
/// @param pred a function pointer to compare the data reference to the elements.
///             It's used as follows: pred(node->data, data)
/// @param del a function pointer to destroy the data segment in the linked list.
///            It's used as follows: del(node->data)
void ft_listdel_pred(t_list** list, void* data, cmp_func pred, free_func del);

/// @brief prints the linked list to stdout
/// @param list the head of the linked list to be printed
/// @param print a function pointer to print the data segment of each element
///              It's used as follows: print(node->data)
void ft_print_list(const t_list* list, print_func print);

/// @brief erases all elements of a linked list and resets the head to NULL
/// @param list a pointer to the head of a linked list
/// @param del a function pointer used to destroy the data segment of each element.
///            It's used as follows: del(node->data)
void ft_listclear(t_list** list, free_func del);

/// @brief creates a new linked list of the given size
///        with allocated strings as data segments.
/// @param size the length the newly created list
/// @return a pointer to the head of the newly created list
///         or NULL if any allocation fails
t_list* ft_populate_list(size_t size);

/// @brief compares the two linked lists
/// @param list1 the head of a linked list
/// @param list2 the head of a different linked list
/// @param cmp a function pointer to compare the two data segments
///            of the linked lists.
///            It's used as follows: cmp(list1_node->data, list2_node->data)
/// @return zero if the two lists are equal,
///         a positive value if list1 < list2 and
///         a negative value if list1 > list2
int ft_listcmp(const t_list* list1, const t_list* list2, cmp_func cmp);


struct s_test_data {
    int number;
    char character;
    double fraction;
};

void print_test_data(void* ptr);
int compare_test_data(const struct s_test_data* lhs,
                      const struct s_test_data* rhs);
struct s_test_data init_test_data(int n, char c, double f);
void destroy_test_data(void* ptr);
t_list* generate_test_data_list(size_t size, uint32_t seed);
struct s_test_data* dup_test_data(const struct s_test_data to_copy);


#endif // LIST_H
