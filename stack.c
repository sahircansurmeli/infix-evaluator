//
// Created by Sahircan Sürmeli on 23.1.2022.
//

#include <stdlib.h>
#include "mem_error.h"
#include "stack.h"

stack *push(stack *head, char op) {
    stack *new;

    new = malloc(sizeof(stack_t));
    if (new == NULL)
        print_mem_error();

    new->op = op;
    new->next = head;

    return new;
}

stack *pop(stack *head) {
    stack *p;

    if (head == NULL)
        return NULL;

    p = head->next;
    free(head);

    return p;
}

stack_val_t *push_val(stack_val_t *head, float val) {
    stack_val_t *new;

    new = malloc(sizeof(stack_val_t));
    if (new == NULL)
        print_mem_error();

    new->val = val;
    new->next = head;

    return new;
}

stack_val_t *pop_val(stack_val_t *head) {
    stack_val_t *p;

    if (head == NULL)
        return NULL;

    p = head->next;
    free(head);

    return p;
}
