#include <stdio.h>
#include <cmddisplay.h>
#include <cmddraw.h>
#include <stack.h>
#include <tower.h>


void
tower_move_a (display *d, tower *t, stack *a, stack *b)
{
    // ANIMATE STUFF
}


void
tower_solve (
    display *d, tower *t, int n,
    stack *a, stack *b, stack *c)
{
    if (n == 1)                         // Only a disc to move...
    {                                   // Only a thing to do.
        tower_move_a(d, t, a, b);       // Otherwise,
        return;                         // Move the n-1 discs from
    }                                   // the top of our base one,
                                        // then move the base disc.
    tower_solve(d, t, n-1, a, c, b);    // Move the n-1 discs back
    tower_move_a(d, t, a, b);           // to the top of our base.
    tower_solve(d, t, n-1, c, b, a);    // AND BOB'S YOUR UNCLE
}


void
tower_start (display *d)
{
    tower t;
    int n;

    printf("Number of discs: ");
    scanf("%d", &n);

    tower_create(&t, n);
    tower_solve(d, &t, n, &t->a, &t->c, &t->b);
    tower_destroy(&t);
}


int
main (void)
{
    display d;
    display_create(&d, 120, 35);

    tower_start(&d);

    display_destroy(&d);
}
