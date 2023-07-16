#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

#include "libasm.h"
#include "test.h"

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

static int my_atoi_base(const char* str, const char* base) {
    if (str == NULL || base == NULL) {
        return 0;
    }
    if (!validate_base(base)) {
        errno = EINVAL;
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
    size_t number = 0;
    for (size_t digit = 0; is_in_base(*s, base, &digit); ++s) {
        number = (number * base_len) + digit;
    }
    long result = (long)number * sign;
    if (result > INT_MAX || result < INT_MIN) {
        errno = ERANGE;
        return 0;
    }
    return (int)result;
}

void compare_atoi_base(char* num_string,
                       char* base) {
    printf("Testing with:\nnum_string = %s\nbase = %s\n", num_string, base);
    errno = 0;
    int my_result = my_atoi_base(num_string, base);
    int save_my_errno = errno;
    errno = 0;
    int ft_result = ft_atoi_base(num_string, base);
    int save_ft_errno = errno;
    printf("ft_atoi_base: %d\n", ft_result);
    if (save_ft_errno != 0) {
        printf("errno = %d, %s\n", save_ft_errno, strerror(save_ft_errno));
    }
    printf("reference_atoi_base: %d\n", my_result);
    if (save_my_errno != 0) {
        printf("errno = %d, %s\n", save_my_errno ,strerror(save_my_errno));
    }
    if (my_result == ft_result && save_ft_errno == save_my_errno) {
        printf("%sTest passed!\n", BOLD_GREEN);
    } else {
        printf("%sTest failed!\n", BOLD_RED);
    }
    printf("%s\n", RESET);
}

void atoi_base_test(void) {
    char decimal[] = "0123456789";
    char hex[] = "0123456789ABCDEF";
    char octal[] = "01234567";
    char binary[] = "01";

    printf("\n\n%s-------------------- atoi base test ------------------------%s\n\n", BOLD_LIGHT_BLUE, RESET);
    compare_atoi_base("", "");
    compare_atoi_base("   111", "1");
    compare_atoi_base("0001", "121");
    compare_atoi_base("10", binary);
    compare_atoi_base("100", decimal);
    compare_atoi_base("\t\f\v ++-+-30", hex);
    compare_atoi_base("\t\f\v \r+101010someting else", binary);
    compare_atoi_base("\t\v\n   -100000000 hello world", binary);
    compare_atoi_base("01234567", octal);
    compare_atoi_base("1111111111111111111111111111111", binary);
    compare_atoi_base("-2147483648", decimal);
    compare_atoi_base("-2147483649", decimal);
    compare_atoi_base("2147483648", decimal);
    compare_atoi_base("21474836480", decimal);
    compare_atoi_base("50000000000", decimal);
}
