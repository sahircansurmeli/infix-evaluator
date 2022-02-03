//
// Created by Sahircan Sürmeli on 23.1.2022.
//

#ifndef EXPRESSIONS_STACK_H
#define EXPRESSIONS_STACK_H

typedef struct stack_s stack;
typedef struct stack_val_s stack_val_t;

struct stack_s {
    char op;
    stack *next;
};

struct stack_val_s {
    float val;
    stack_val_t *next;
};

stack *push(stack *, char);
stack *pop(stack *);
stack_val_t *push_val(stack_val_t *, float);
stack_val_t *pop_val(stack_val_t *);

#endif //EXPRESSIONS_STACK_H
