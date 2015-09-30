#include <stdio.h>
#include <stack.h>
#include <tower.h>


void
tower_print (tower *t)
{
    printf("\nA = ");
    stack_print(&t->a);
    printf("B = ");
    stack_print(&t->b);
    printf("C = ");
    stack_print(&t->c);
}


void
tower_create (tower *t, int size)
{
    stack_create(&t->a, size);
    stack_create(&t->b, size);
    stack_create(&t->c, size);

    int i;
    for (i = size+3; i > 3; i--)
        stack_push(&t->a, i);
}


void
tower_destroy (tower *t)
{
    stack_destroy(&t->a);
    stack_destroy(&t->b);
    stack_destroy(&t->c);
}


void
tower_move (stack *a, stack *b)
{
    if (
        stack_is_empty(a) ||            // Make sure we don't move
        (!stack_is_empty(b) &&          // a disc from an empty stack
        stack_top(a) > stack_top(b))    // or put a disc on top of a
    )                                   // smaller one.
        return;
    
    stack_push(b, stack_pop(a));
}
