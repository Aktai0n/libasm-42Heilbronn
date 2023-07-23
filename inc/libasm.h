#ifndef LIBASM_H
#define LIBASM_H

#include <stddef.h>
#include <sys/types.h>


#define RESET "\033[0m"
#define BOLD "\033[1m"
#define RED "\033[91m"
#define GREEN "\033[32m"
#define LIGHT_BLUE "\033[94m"
#define BOLD_RED "\033[1m\033[91m"
#define BOLD_GREEN "\033[1m\033[32m"
#define BOLD_LIGHT_BLUE "\033[1m\033[94m"

// always include the bonus part
#ifndef LIBASM_BONUS
#define LIBASM_BONUS
#endif

/// @brief counts the number of characters in str
///        until it reaches a null character '\0'
/// @param str a non NULL array of characters delimited by \0
/// @return the number of characters in the string
size_t ft_strlen(const char* str);

/// @brief copies the string src into dest,
///        including the terminating '\0' of src.
///        Beware of buffer overruns!
/// @param dest the non NULL destination buffer
/// @param src the non NULL string to be copied
/// @return the string dest
char* ft_strcpy(char* dest, const char* src);

/// @brief compares the strings s1 and s2 char by char
/// @param s1 the fist non NULL string
/// @param s2 the second non NULL string
/// @return 0 if s1 == s2, > 0 if s1 > s2 and < 0 if s1 < s2
int ft_strcmp(const char* s1, const char* s2);

/// @brief copies the string s to a newly allocated block
///        of memory
/// @param s the non NULL string to be copied
/// @return the newly created string
///         or NULL if the allocation fails
char* ft_strdup(const char* s);

/// @brief writes count bytes of buf to the file descriptor fd
/// @param fd the file descriptor to be written to
/// @param buf an array of binary data to be written to fd
/// @param count the number of bytes to be written to fd
/// @return on success the number of bytes written.
///         On error -1 with errno set to indicate the error
ssize_t ft_write(int fd, const void* buf, size_t count);

/// @brief reads count bytes from the file descriptor fd
///        and stores them in the buffer pointed to by buf
/// @param fd the file descriptor to be read from
/// @param buf a pointer to the memory region the read data
///            should be stored in
/// @param count the number of bytes to be read
/// @return on success the number of bytes read.
///         If this number is smaller than count (or 0)
///         this indicates an EOF
///         On error -1 with errno set to indicate the error
ssize_t ft_read(int fd, void* buf, size_t count);

#ifdef LIBASM_BONUS

typedef struct s_list {
    void* data;
    struct s_list* next;
} t_list;

/// @brief converts the string str into an integer.
///        The charset of str is determined by the string base.
/// 
///        Restrictions for base: length >= 2, no whitespace
///        characters, no + or - and no duplicate characters
/// @param str the string to be converted
/// @param base the charset of str
/// @return the integer representation of str
///         or 0 on error with errno set to indicate the error:\n
///         EINVAL if base is malformed 
///         ERANGE if the integer representation of str would cause overflow
int ft_atoi_base(char* str, char* base);

/// @brief creates a new t_list node at the beginning of
///        the list pointed to by begin_list with its data set to
///        the data parameter
/// @param begin_list a pointer to the head of a t_list linked list
///        if the head is NULL, it's set to the created node
/// @param data a pointer to any type of data to be stored in the list
void ft_list_push_front(t_list** begin_list, void* data);

/// @brief calculates the length of the linked list
/// @param list the head of the linked list
/// @return the length of the linked list
int ft_list_size(t_list* begin_list);

/// @brief sorts the linked list in O(n²)
/// @param list a pointer to the head of a linked list
/// @param cmp a function pointer to compare the data segments of the
///            linked list. Its used as follows: cmp(node->data, node->next->data)
void ft_list_sort(t_list** begin_list, int (*cmp)());

/// @brief erases all nodes in the linked list where the comparison function returns zero to
/// @param list a pointer to the head of a linked list
/// @param data the reference data which all elements are compared to
/// @param pred a function pointer to compare the data reference to the elements.
///             It's used as follows: pred(node->data, data)
/// @param del a function pointer to destroy the data segment in the linked list.
///            It's used as follows: del(node->data)
void ft_list_remove_if(t_list** begin_list, void* data_ref, int (*cmp)(), void (*free_fct)(void*));


#endif // LIBASM_BONUS



#endif // LIBASM_H
