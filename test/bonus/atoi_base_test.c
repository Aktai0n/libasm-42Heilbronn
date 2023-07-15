#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "libasm.h"

static bool my_isspace(int c) {
    return (c == ' ' ||
            c == '\t' ||
            c == '\n' ||
            c == '\v' ||
            c == '\f' ||
            c == '\r');
}

static bool is_in_base(char c, const char* base, size_t* pos) {
    for (*pos = 0; base[*pos] != '\0'; ++(*pos)) {
        if (base[*pos] == c) {
            return true;
        }
    }
    return false;
}

static bool validate_base(const char* base) {

    size_t base_len = strlen(base);
    if (base_len <= 1) {
        return false;
    }
    for (size_t i = 0; i < base_len; ++i) {
        if (base[i] == '+' || base[i] == '-' || my_isspace(base[i])) {
            return false;
        }
        for (size_t j = i + 1; j < base_len; ++j) {
            if (base[i] == base[j]) {
                return false;
            }
        }
    }
    return true;
}

int my_atoi_base(const char* str, const char* base) {
    if (str == NULL || base == NULL || !validate_base(base)) {
        return 0;
    }
    const char* s = str;
    size_t base_len = strlen(base);

    while (my_isspace(*s)) {
        ++s;
    }
    int sign = 1;
    while (*s == '-' || *s == '+') {
        if (*s == '-') {
            sign = -sign;
        }
        ++s;
    }
    size_t result = 0;
    for (size_t digit = 0; is_in_base(*s, base, &digit); ++s) {
        result = (result * base_len) + digit;
    }
    // maybe check for int overflow
    return (int)result * sign;
}

void compare_atoi_base(char* num_string,
                       char* base) {
    printf("Testing with:\nnum_string = %s\nbase = %s\n", num_string, base);
    int my_result = my_atoi_base(num_string, base);
    int ft_result = ft_atoi_base(num_string, base);
    printf("ft_atoi_base: %d\n", ft_result);
    printf("reference_atoi_base: %d\n", my_result);
    if (ft_result == 0) {
        perror("errno");
    }
    if (my_result == ft_result) {
        printf("%sTest passed!\n", BOLD_GREEN);
    } else {
        printf("%sTest failed!\n", BOLD_RED);
    }
    printf("%s\n", RESET);
}

void atoi_base_test(void) {
    char decimal[] = "0123456789";
    char hex[] = "0123456789ABCDEF";
    char octal[] = "012345678";
    char binary[] = "01";

    printf("\n%s-------------------- atoi base test ------------------------%s\n", BOLD_LIGHT_BLUE, RESET);
    compare_atoi_base("", "");
    compare_atoi_base("   111", "1");
    compare_atoi_base("0001", "121");
    compare_atoi_base("10", binary);
    compare_atoi_base("100", decimal);
    compare_atoi_base("\t\f\v ++-+-30", hex);
    compare_atoi_base("\t\f\v \r+101010someting else", binary);
}

// int main(void) {

//     compare_atoi_base("100", decimal, 100);
//     compare_atoi_base("0", octal, 0);
//     compare_atoi_base("      +++42", decimal, 42);
//     compare_atoi_base("\t\f\v ++-+-30", hex, 48);
//     compare_atoi_base(NULL, binary, 0);
//     compare_atoi_base("something", "0", 0);
//     compare_atoi_base("\t\f\v \r+101010someting else", binary, 42);
//     // printf("%d\n", my_atoi_base("invalid", binary));
// }
