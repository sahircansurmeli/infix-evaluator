//
// Created by Sahircan Sürmeli on 23.1.2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "mem_error.h"

queue_t *create() {
    queue_t *new;

    new = malloc(sizeof(queue_t));
    if (new == NULL)
        print_mem_error();

    return new;
}

queue_t *enqueue(queue_t *head, queue_t *new) {
    queue_t *p;

    new->next = NULL;

    if (head == NULL)
        return new;

    p = head;
    while (p->next != NULL)
        p = p->next;

    p->next = new;

    return head;
}

queue_t *enqueue_val(queue_t *head, float val, int len) {
    queue_t *new = create();

    new->val = val;
    new->t = VAL;
    new->val_len = len;

    return enqueue(head, new);
}

queue_t *enqueue_op(queue_t *head, char op) {
    queue_t *new = create();

    new->op = op;
    new->t = OP;

    return enqueue(head, new);
}

queue_t *dequeue(queue_t *head) {
    queue_t *p;

    if (head == NULL)
        return NULL;

    p = head->next;
    free(head);
    return p;
}

char *str(queue_t *head, int len) {
    char *string, *end;

    string = malloc(len*2 * sizeof(char));
    if (string == NULL)
        print_mem_error();

    end = string;

    while (head != NULL) {
        switch (head->t) {
            case OP:
                snprintf(end, 2, "%c", head->op);
                end++;
                break;
            case VAL:
                snprintf(end, head->val_len + 1, "%f", head->val);
                end += head->val_len;
                break;
        }
        snprintf(end, 2, " ");
        end++;

        head = head->next;
    }

    return string;
}