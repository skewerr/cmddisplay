#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "stack.h"


// Operation functions.


void
stack_create (stack *s, int size)
{
    s->top      = 0;
    s->size     = size;
    s->content  = (int*) malloc(size * sizeof(int));
}


void
stack_resize (stack *s, int size)
{
    if (s->size == size)
        return;

    if (s->top > size)
        s->top = size;

    s->size     = size;
    s->content  = (int*) realloc(s->content, size * sizeof(int));
}


void
stack_push (stack *s, int data)
{
    if (stack_is_full(s))
    {
        printf("ERRO: Pilha cheia. (push %d)\n", data);
        return;
    }

    s->content[s->top++] = data;
}


int
stack_pop (stack *s)
{
    if (stack_is_empty(s))
    {
        printf("ERRO: Pilha vazia. (pop)\n");
        return 0;
    }

    return s->content[--s->top];
}


void
stack_empty (stack *s)
{
    while (!stack_is_empty(s))
        stack_pop(s);
}

void
stack_fill (stack *s)
{
    static bool seeded = false;

    if (!seeded)
    {
        srand(time(NULL));
        seeded = true;
    }

    while (!stack_is_full(s))
        stack_push(s, rand() % 100);
}


void
stack_copy (stack *s, stack *t)
{
    stack u;

    stack_destroy(s);

    stack_create(&u, t->size);
    stack_create(s, t->size);

    while (!stack_is_empty(t))
        stack_push(&u, stack_pop(t));

    while (!stack_is_empty(&u))
    {
        stack_push(s, stack_top(&u));
        stack_push(t, stack_pop(&u));
    }

    stack_destroy(&u);
}


void
stack_join (stack *s, stack *t)
{
    stack u;

    stack_copy(&u, t);
    stack_invert(&u);

    if (s->size < s->top + t->top)
        stack_resize(s, s->top + t->top);

    while (!stack_is_empty(&u))
        stack_push(s, stack_top(&u));

    stack_destroy(&u);
}


void
stack_invert (stack *s)
{
    stack t;
    stack_create(&t, s->size);

    stack_copy(&t, s);
    stack_empty(s);

    while (!stack_is_empty(&t))
        stack_push(s, stack_pop(&t));

    stack_destroy(&t);
}


void
stack_destroy (stack *s)
{
    free(s->content);
}


// Verification functions.


bool
stack_is_empty (stack *s)
{
    return !(s->top);
}


bool
stack_is_full (stack *s)
{
    return s->top == s->size;
}


// Other functions.


int
stack_top (stack *s)
{
    if (stack_is_empty(s))
    {
        printf("ERRO: Pilha vazia. (top)\n");
        return 0;
    }

    return s->content[s->top - 1];
}


int
stack_size (stack *s)
{
    return s->size;
}


void
stack_print (stack *s)
{
    if (stack_is_empty(s))
    {
        printf("Fim da pilha.\n");
        return;
    }

    int e = stack_pop(s);
    printf("%d -> ", e);

    stack_print(s);
    stack_push(s, e);
}
