//
// Created by red on 23.04.2025.
//

#define X_DEBUG(v) if (x_debug == 1) { v }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int x_debug = 0;

struct sorted_slices {
    size_t length;
    struct sorted_slice* ptr;
};

struct sorted_slice {
    size_t left_idx;
    size_t right_idx;
};

struct sorted_slices sorted_slices(size_t in_size) {
    struct sorted_slice* arr = malloc(sizeof(struct sorted_slice) * in_size);

    // arrays of length 1 are sorted
    for (size_t i = 0; i < in_size; i++) {
        arr[i].left_idx = i;
        arr[i].right_idx = i;
    }

    struct sorted_slices res;
    res.length = in_size;
    res.ptr = arr;

    return res;
}

void free_slices(struct sorted_slices del) {
    free(del.ptr);
}

struct sorted_slice merge_in_place(
    struct sorted_slice a,
    struct sorted_slice b,
    int *in
) {
    // Merge two sorted arrays

    // Temporary slice
    size_t a_size = a.right_idx - a.left_idx + 1;
    size_t b_size = b.right_idx - b.left_idx + 1;
    int* merge_field = malloc(sizeof(int) * (a_size + b_size));

    size_t i = a.left_idx;
    size_t j = b.left_idx;

    while (i <= a.right_idx || j <= b.right_idx) {
        while (i <= a.right_idx && (j > b.right_idx || in[i] <= in[j])) {
            merge_field[i - a.left_idx + j - b.left_idx] = in[i];
            i++;
        }

        while (j <= b.right_idx && (i > a.right_idx || in[i] > in[j])) {
            merge_field[i - a.left_idx + j - b.left_idx] = in[j];
            j++;
        }
    }

    // Добавляем отсортированные указатели в next_head
    struct sorted_slice c;
    c.left_idx = a.left_idx;
    c.right_idx = a.left_idx + a_size + b_size - 1;

    memcpy(&in[a.left_idx], merge_field, sizeof(int) * (a_size + b_size));
    free(merge_field);

    return c;
}

void sort(size_t in_size, int* in) {
    if (in_size <= 1) {
        return;
    }

    struct sorted_slices slices = sorted_slices(in_size);

    size_t slices_i = 0; // указатель в slices
    size_t slices_start = 0; // на что будет указывать slices_next после итерации
    size_t slices_next = 0; // указатель в slices. в какой индекс будет добавлен новый slice

    /*   IN    |   SLICES |
     * a b c d |  a b c d |
     * m m c d |  m b c d |
     * m m f f |  m f c d | loop -> f.right == in.length - 1
     * e e e e |  e f c d |
     *
     *       IN      |     SLICES     |
     * a b c d e f g |  a b c d e f g | slices_start = 0
     * x x c d e f g |  x b c d e f g |
     * x x y y e f g |  x y c d e f g |
     * x x y y z z g |  x y z d e f g |
     * x x y y z z g |  x y z g e f g | loop -> g.right = in.length - 1
     * w w w w z z g |  x w z g e f g | after loop -> slices start + 1
     * w w w w o o o |  x w o g e f g | loop -> o.right = in.length - 1
     * q q q q q q q |  x w q g e f g | slices_start + 1
     *
     */

    X_DEBUG(printf("| IN | SLICES |\n");)

    while (slices.length >= 1) {
        X_DEBUG(
            printf("|");
            // print IN
            for (size_t i = 0; i < in_size; i++) {
                printf(" %d", in[i]);
            }
            printf(" |");
            // print SLICES
            for (size_t i = 0; i < in_size; i++) {
                struct sorted_slice slc = slices.ptr[i];
                if (slc.left_idx == slc.right_idx) {
                    printf(" [!%llu]", slc.left_idx);
                } else {
                    printf(" %llu->%llu", slc.left_idx, slc.right_idx);
                }
            }
            printf(" |\n");
        )


        struct sorted_slice a = slices.ptr[slices_i++];

        // Out of bounds - loop
        if (a.right_idx >= in_size - 1) {
            slices.ptr[slices_next].left_idx = a.left_idx;
            slices.ptr[slices_next].right_idx = a.right_idx;
            X_DEBUG(printf("loop -> out of bounds\n");)
            slices_i = slices_start;
            slices_start += 1;
            slices_next = slices_start;
            slices.length /= 2;
            continue;
        }

        struct sorted_slice b = slices.ptr[slices_i++];

        struct sorted_slice c = merge_in_place(a, b, in);
        slices.ptr[slices_next++] = c;

        // Iteration end
        if (c.right_idx >= in_size - 1) {
            X_DEBUG(printf("loop -> c.right_idx >= in_size - 1\n");)

            if (slices.length <= 1) {
                X_DEBUG(printf("finished last iteration\n");)
                break;
            }

            slices_i = slices_start;
            slices_start += 1;
            slices_next = slices_start;
            slices.length /= 2;
        }
    }

    X_DEBUG(
        printf("|");
        // print IN
        for (size_t i = 0; i < in_size; i++) {
            printf(" %d", in[i]);
        }
        printf(" |");
        // print SLICES
        for (size_t i = 0; i < in_size; i++) {
            struct sorted_slice slc = slices.ptr[i];
            if (slc.left_idx == slc.right_idx) {
                printf(" [!%llu]", slc.left_idx);
            } else {
                printf(" %llu->%llu", slc.left_idx, slc.right_idx);
            }
        }
        printf(" |\n");
    )

    free_slices(slices);
}

void main() {
    int const_arr[] = {5, 7, 82, 87, 11, 0, 100};

    int size = sizeof(const_arr) / sizeof(int);
    int* arr = const_arr;

    printf("Unsorted array : ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    sort(size, arr);

    printf("Sorted array   : ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

