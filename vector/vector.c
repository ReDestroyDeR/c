//
// Created by red on 27.04.2025.
//

#include "vector.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../debug.h"

#if DEBUG_ON
// Not Thread Safe
int vec_id_seq = 0;
#endif

const long double growth_factors[] = {1.6, 1.3, 1.1, 1.05};
const long double load_to_grow = 0.75;

long double growth_factor(struct Vec *vec) {
    long double load = (long double) vec->size / (long double) vec->capacity;
    if (load < load_to_grow) {
        X_DEBUG(printf("[Vec] load (%Lg) < load_to_grow (%Lg)\n", load, load_to_grow);)
        return 1;
    }

    long double growth_factor;

    if      (vec->capacity > 2 << 20) growth_factor = growth_factors[3]; // Для чисел от 524288 растет в 1.05 раз
    else if (vec->capacity > 2 << 14) growth_factor = growth_factors[2]; // Для чисел от 32768 до 524287 в 1.1 раз
    else if (vec->capacity > 2 << 10) growth_factor = growth_factors[1]; // Для чисел от 1024 до 32767 растет в 1.3 раза
    else                              growth_factor = growth_factors[0]; // Для чисел до 1024 растет в 1.6 раз

    X_DEBUG(printf("[Vec] load (%Lg) >= load_to_grow (%Lg)\n", load, load_to_grow);)
    X_DEBUG(printf("[Vec] Growth Factor for capacity %llu = %Lg\n", vec->capacity, growth_factor);)

    return growth_factor;
}

void grow(struct Vec *vec, size_t dst_offset) {
    const long double factor = growth_factor(vec);

    const size_t new_capacity = (size_t) ((long double) vec->capacity * factor);

    void** new_buffer = malloc(sizeof(void*) * new_capacity);

    memcpy(&new_buffer[dst_offset], vec->data, sizeof(void*) * vec->capacity);

    vec->data = new_buffer;
    vec->capacity = new_capacity;
}

const size_t default_capacity = 2 << 4;

struct Vec vec_new() {
    return vec_with_capacity(default_capacity);
}

struct Vec vec_with_capacity(size_t capacity) {
    struct Vec vec;

    X_DEBUG(vec.vec_uid = vec_id_seq++;)
    vec.capacity = capacity;
    vec.data = malloc(sizeof(void*) * capacity);

    vec.size = 0;
    vec.mod_count = 0;

    X_DEBUG(printf("[Vec] allocated new. vec->capacity: %llu\n", capacity);)

    return vec;
}

int vec_insert(struct Vec *vec, size_t pos, void *data) {
    X_DEBUG(printf("[Vec] start insert: %p. pos: %llu\n", data, pos);)

    if (pos > vec->capacity) {
        return -1;
    }

    vec->data[pos] = data;

    X_DEBUG(printf("[Vec] end insert: %p. pos: %llu. vec->size: %llu\n\n", data, pos, vec->size);)

    return 0;
}

void vec_push_front(struct Vec *vec, void *data) {
    X_DEBUG(printf("[Vec] start push_front: %p\n", data);)

    grow(vec, 1);

    vec->data[0] = data;
    vec->size++;
    vec->mod_count++;

    X_DEBUG(printf("[Vec] end push_front: %p. vec->size: %llu\n\n", data, vec->size);)
}

void vec_push_back(struct Vec *vec, void *data) {
    X_DEBUG(printf("[Vec] start push_back: %p\n", data);)
    grow(vec, 0);

    vec->data[vec->size++] = data;
    vec->mod_count++;

    X_DEBUG(printf("[Vec] end push_back: %p. vec->size: %llu\n\n", data, vec->size);)
}

void* vec_get(const struct Vec *vec, size_t pos) {
    X_DEBUG(printf("[Vec] start get. pos: %llu\n", pos);)
    if (pos >= vec->size) {
        X_DEBUG(printf("[Vec] end get. pos %llu >= vec->size %llu\n\n", pos, vec->size);)
        return NULL;
    }

    void *res = vec->data[pos];
    X_DEBUG(printf("[Vec] end get. pos: %llu. res: %p\n\n", pos, res);)
    return res;
}

void* vec_pop_front(struct Vec *vec) {
    X_DEBUG(printf("[Vec] start pop_front\n");)
    if (vec->size == 0) {
        X_DEBUG(printf("[Vec] end pop_front. vec is empty\n\n");)
        return NULL;
    }

    void* data = vec->data[0];
    vec->size--;
    memcpy(vec->data, &vec->data[1], sizeof(void*) * vec->size);
    vec->mod_count++;

    X_DEBUG(printf("[Vec] end pop_front. res: %p\n\n", data);)
    return data;
}

void* vec_pop_back(struct Vec *vec) {
    X_DEBUG(printf("[Vec] start pop_back\n");)
    if (vec->size == 0) {
        X_DEBUG(printf("[Vec] end pop_back. vec is empty\n\n");)
        return NULL;
    }

    void* data = vec->data[--vec->size];
    vec->mod_count++;

    X_DEBUG(printf("[Vec] end pop_back. res: %p\n\n", data);)
    return data;
}

void vec_free(const struct Vec vec) {
    free(vec.data);
}
