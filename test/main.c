#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "libasm.h"

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


static void run_all(void) {
    strcmp_test();
    strcpy_test();
    strdup_test();
    strlen_test();
    write_test();
    read_test();

#ifdef LIBASM_BONUS
    atoi_base_test();
    list_push_front_test();
    list_size_test();
    list_sort_test();
    list_remove_if_test();
#endif
}

int main(int argc, char** argv) {
    if (argc == 1) {
        run_all();
        return 0;
    }

    bool test_has_run[11] = {0};

    for (int i = 1; i < argc; ++i) {
        char* param = argv[i];
        if (strcmp(param, "strlen") == 0 && !test_has_run[0]) {
            strlen_test();
            test_has_run[0] = true;
        } else if (strcmp(param, "strcpy") == 0 && !test_has_run[1]) {
            strcpy_test();
            test_has_run[1] = true;
        } else if (strcmp(param, "strcmp") == 0 && !test_has_run[2]) {
            strcmp_test();
            test_has_run[2] = true;
        } else if (strcmp(param, "write") == 0 && !test_has_run[3]) {
            write_test();
            test_has_run[3] = true;
        } else if (strcmp(param, "read") == 0 && !test_has_run[4]) {
            read_test();
            test_has_run[4] = true;
        } else if (strcmp(param, "strdup") == 0 && !test_has_run[5]) {
            strdup_test();
            test_has_run[5] = true;
        }
    #ifdef LIBASM_BONUS
        else if (strcmp(param, "atoi_base") == 0 && !test_has_run[6]) {
            atoi_base_test();
            test_has_run[6] = true;
        } else if (strcmp(param, "list_push_front") == 0 && !test_has_run[7]) {
            list_push_front_test();
            test_has_run[7] = true;
        } else if (strcmp(param, "list_size") == 0 && !test_has_run[8]) {
            list_size_test();
            test_has_run[8] = true;
        } else if (strcmp(param, "list_sort") == 0 && !test_has_run[9]) {
            list_sort_test();
            test_has_run[9] = true;
        } else if (strcmp(param, "list_remove_if") == 0 && !test_has_run[10]) {
            list_remove_if_test();
            test_has_run[10] = true;
        }
    #endif // LIBASM_BONUS
        else {
            printf("\n\n%sUnknown option: %s\n\n%s", BOLD_RED, param, RESET);
        }
    }

}
