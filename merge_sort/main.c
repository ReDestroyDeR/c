//
// Created by red on 23.04.2025.
//

#include <stdio.h>
#include "msort.h"

void main() {
    int const_arr[] = {6, 5, 4, 3, 2, 1, 0};

    int size = sizeof(const_arr) / sizeof(int);
    int* arr = const_arr;

    printf("Unsorted array : ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    msort_in_place(size, arr);

    printf("Sorted array   : ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

