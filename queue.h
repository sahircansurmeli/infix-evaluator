//
// Created by Sahircan Sürmeli on 23.1.2022.
//

#ifndef EXPRESSIONS_QUEUE_H
#define EXPRESSIONS_QUEUE_H

typedef enum { OP, VAL } type;
typedef struct queue_s queue_t;

struct queue_s {
    char op;
    float val;
    int val_len;
    type t;
    queue_t *next;
};

queue_t *enqueue_val(queue_t *, float, int);
queue_t *enqueue_op(queue_t *, char);
queue_t *dequeue(queue_t *);
char *str(queue_t *, int);

#endif //EXPRESSIONS_QUEUE_H
