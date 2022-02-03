#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#include "queue.h"
#include "stack.h"

float eval(queue_t *);
queue_t *parse(const char *);
int isoperator(char);
int isopeningp(char);
int isclosingp(char);
int precedence(char);
char associativity(char);

int main() {
    const char *expr = "[(4 + 3) * (2 - 4)] * 5";
    const int EXPECTED_RESULT = -70;
    queue_t *postfix = parse(expr);
    float result = eval(postfix);

    printf("%f\n", result);

    return EXIT_SUCCESS;
}

float eval(queue_t *queue) {
    stack_val_t *stack = NULL;

    while (queue != NULL) {
        if (queue->t == VAL) {
            stack = push_val(stack, queue->val);
        }
        else if (queue->t == OP) {
            float l, r, res;
            r = stack->val;
            stack = pop_val(stack);
            l = stack->val;
            stack = pop_val(stack);
            switch (queue->op) {
                case '+':
                    res = l + r;
                    break;
                case '-':
                    res = l - r;
                    break;
                case '*':
                    res = l * r;
                    break;
                case '/':
                    res = l / r;
                    break;
                case '^':
                    res = powf(l, r);
                    break;
            }
            stack = push_val(stack, res);
        }
        queue = queue->next;
    }

    return stack->val;
}

queue_t *parse(const char *expr) {
    queue_t *queue = NULL;
    stack *stack = NULL;
    int i, len;
    char c;

    len = (int) strlen(expr);

    i = 0;
    while (i < len) {
        while (isspace(expr[i]))
            i++;

        c = expr[i];

        if (isdigit(c)) {
            int bytes;
            float val;
            sscanf(expr+i, "%f%n", &val, &bytes);
            queue = enqueue_val(queue, val, bytes);
            i += (bytes - 1);
        }

        else if (isoperator(c)) {
            char o2;
            while (stack != NULL && !isopeningp((o2 = stack->op))
            && (precedence(o2) > precedence(c) || (precedence(o2) == precedence(c) && associativity(c) == 'l'))) {
                queue = enqueue_op(queue, o2);
                stack = pop(stack);
            }
            stack = push(stack, c);
        }

        else if (isopeningp(c)) {
            stack = push(stack, c);
        }

        else if (isclosingp(c)) {
            while (stack != NULL && !isopeningp(stack->op)) {
                queue = enqueue_op(queue, stack->op);
                stack = pop(stack);
                if (stack == NULL) {
                    printf("Mismatched parantheses!\n");
                    return NULL;
                }
            }
            if (stack == NULL || !isopeningp(stack->op)) {
                printf("Mismatched parantheses!\n");
                return NULL;
            }
            stack = pop(stack);
        }

        i++;
    }

    while (stack != NULL) {
        if (isopeningp(stack->op) || isclosingp(stack->op)) {
            printf("Mismatched parantheses!\n");
            return NULL;
        }
        queue = enqueue_op(queue, stack->op);
        stack = pop(stack);
    }

    return queue;
}

int isoperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int isopeningp(char c) {
    return c == '(' || c == '[' || c == '{';
}

int isclosingp(char c) {
    return c == ')' || c == ']' || c == '}';
}

int precedence(char c) {
    if (isopeningp(c) || isclosingp(c))
        return 3;
    if (c == '*' || c == '/')
        return 2;
    if (c == '+' || c == '-')
        return 1;
    return 0;
}

char associativity(char c) {
    if (c == '^')
        return 'r';
    return 'l';
}