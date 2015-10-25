#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef struct {
    int top;
    int size;
    int *content;
} stack;

void stack_create(stack *, int);
void stack_resize(stack *, int);
void stack_push(stack *, int);
int  stack_pop(stack *);

void stack_copy(stack *, stack *);
void stack_join(stack *, stack *);
void stack_empty(stack *);
void stack_fill(stack *);
void stack_invert(stack *);
void stack_destroy(stack *);

void stack_print(stack *);

int  stack_top(stack *);
int  stack_size(stack *);

bool stack_is_empty(stack *);
bool stack_is_full(stack *);

#endif
