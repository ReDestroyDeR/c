//
// Created by red on 27.04.2025.
//

#pragma once
#include <stdio.h>

#include "../debug.h"

struct Vec {
    X_DEBUG_DEF(unsigned long long vec_uid;)

    size_t size;
    size_t mod_count;

    size_t capacity;
    void** data;
};

struct Vec vec_new           ();
struct Vec vec_with_capacity (size_t capacity);
int        vec_insert        (struct Vec* vec, size_t pos, void* data);
void       vec_push_front    (struct Vec* vec, void* data);
void       vec_push_back     (struct Vec* vec, void* data);
void*      vec_get           (const struct Vec* vec, size_t pos);
void*      vec_pop_front     (struct Vec* vec);
void*      vec_pop_back      (struct Vec* vec);
void       vec_free          (struct Vec vec);

inline void vec_print(struct Vec* vec, void (*print)(size_t, void*)) {
    printf("Vec(\n");
    X_DEBUG(printf("  vec_uid: %llu\n", vec->vec_uid);)
    for (size_t i = 0; i < vec->size; i++) {
        print(i, vec->data[i]);
        printf("\n");
    }
    printf(")\n");
}
