#include <stdio.h>

#include "linkedlist.h"

int main(void) {
    struct list_head* x = list_init(" world");
    list_prepend(x, "hello");
    list_append(x, ". okay!");
    list_append(x, "\ntest");

    char* buf;
    while ((buf = list_pop(x)) != NULL) {
        printf("%s", buf);
    }

    return 0;
}
