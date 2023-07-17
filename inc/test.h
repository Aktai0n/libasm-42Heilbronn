#ifndef TEST_H
#define TEST_H

#include "libasm.h"

#include <stdio.h>

#ifndef TESTFILE_NAME
#define TESTFILE_NAME "testfile.txt"
#endif

// #ifndef TEST_VERBOSE
// #define TEST_VERBOSE 1
// #endif


void strcmp_test(void);
void strcpy_test(void);
void strdup_test(void);
void strlen_test(void);
void write_test(void);
void read_test(void);

#ifdef LIBASM_BONUS
void atoi_base_test(void);
void list_push_front_test(void);
void list_size_test(void);
void list_sort_test(void);
void list_remove_if_test(void);
#endif


void print_file(int fd, FILE* output);
char* read_file(int fd);
void print_string(void* ptr);

#endif // TEST_H
