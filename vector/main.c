//
// Created by red on 27.04.2025.
//

#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

struct Box {
    int val;
};

struct Box* alloc_box(const int val) {
    struct Box *box = malloc(sizeof(struct Box));
    box->val = val;
    return box;
}

void print_box(const size_t idx, const struct Box *ptr) {
    printf("  #%llu: val->%d", idx, ptr->val);
}

void main() {
    struct Vec my_vec = vec_with_capacity(2);

    for (int i = 0; i < 10; i++) {
        vec_push_back(&my_vec, alloc_box(i));
    }

    vec_print(&my_vec, print_box);


    struct Vec popped = vec_with_capacity(10);

    for (int i = 0; i < 5; i++) {
        struct Box *val = vec_pop_front(&my_vec);
        vec_push_back(&popped, val);
    }

    vec_print(&popped, print_box);
    vec_print(&my_vec, print_box);

    vec_free(my_vec);
}