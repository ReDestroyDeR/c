//
// Created by red on 22.04.2025.
//

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#endif //LINKEDLIST_H

struct list_head {
    void *val;
    struct list_head *tail;
};

enum list_status {
    ok = 0,
    input_is_null = 1,
};

struct list_head* list_init(void *head);

/// O(1)
enum list_status list_prepend(struct list_head *head, void *new_head);

/// O(n)
enum list_status list_append(struct list_head *head, void *new_last);

void* list_pop(struct list_head *head);
