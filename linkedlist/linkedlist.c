//
// Created by red on 22.04.2025.
//

#include "linkedlist.h"

#include <stdio.h>
#include <stdlib.h>

struct list_head* list_init(void* head) {
    struct list_head* head_p = malloc(sizeof(struct list_head));

    if (head_p == NULL) {
        printf("malloc failed\n");
        return NULL;
    }

    head_p->val = head;
    head_p->tail = NULL;

    return head_p;
}


enum list_status list_prepend(struct list_head *head, void *new_head) {
    if (head == NULL) {
        return input_is_null;
    }

    struct list_head* new_tail = list_init(head->val);
    head->tail = new_tail;
    head->val = new_head;

    return ok;
}

enum list_status list_append(struct list_head *head, void *new_last) {
    if (head == NULL) {
        return input_is_null;
    }

    struct list_head* curr_head = head;
    while (curr_head->tail != NULL) {
        curr_head = curr_head->tail;
    }
    curr_head->tail = list_init(new_last);
    return ok;
}

void* list_pop(struct list_head *head) {
    if (head == NULL) {
        return NULL;
    }

    void *val = head->val;

    // Pop the value. It can become null=
    struct list_head *tail = head->tail;

    if (tail == NULL) {
        head->val = NULL;
    } else {
        *head = *tail;
    }

    return val;
}


