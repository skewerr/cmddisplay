#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef struct {
    int top;
    int size;
    int *content;
} stack;

void stack_create   (stack *s, int size);
void stack_resize   (stack *s, int size);
void stack_push     (stack *s, int data);
int  stack_pop      (stack *s);

void stack_copy     (stack *s, stack *t);
void stack_join     (stack *s, stack *t);
void stack_empty    (stack *s);
void stack_fill     (stack *s);
void stack_invert   (stack *s);
void stack_destroy  (stack *s);

void stack_print    (stack *s);

int  stack_top      (stack *s);
int  stack_size     (stack *s);

bool stack_is_empty (stack *s);
bool stack_is_full  (stack *s);

#endif
