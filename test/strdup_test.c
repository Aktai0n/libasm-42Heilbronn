#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* ft_strdup(const char*);

char* my_strdup(const char* str) {
    if (str == NULL) {
        return NULL;
    }
    size_t len = strlen(str);
    char* dest = malloc(len + 1);
    if (dest == NULL) {
        return NULL;
    }
    strcpy(dest, str);
    dest[len] = '\0';
    return dest;
}

void compare_strdup() {
    
}

int main() {

}