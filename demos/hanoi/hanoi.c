#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include <cmddisplay/display.h>
#include <cmddisplay/draw.h>
#include <stdio.h>
#include <stdlib.h>
#include <stack.h>
#include <tower.h>

unsigned int g_sleep = 15;


void
fill_discs(display *d, stack *s, int x)
{
    if (stack_is_empty(s))
        return;

    int disc = stack_pop(s);
    draw_line(d, x - disc, s->top+1, x + disc, s->top+1);
    fill_discs(d, s, x);
    stack_push(s, disc);
}


void
draw_tower(display *d, tower *t)
{
    draw_line(d, 0, 0, d->width-1, 0);
    draw_line(d,   d->width/4, 0,   d->width/4, d->height-13);
    draw_line(d,   d->width/2, 0,   d->width/2, d->height-13);
    draw_line(d, 3*d->width/4, 0, 3*d->width/4, d->height-13);

    fill_discs(d, &t->a,   d->width/4);
    fill_discs(d, &t->b,   d->width/2);
    fill_discs(d, &t->c, 3*d->width/4);
}


void
tower_move_a(display *d, tower *t, stack *a, stack *b)
{
    static int move_count = 0;

    int disc = stack_pop(a);
    int pos1 = (d->width/4) * ((a == &t->a) ? 1 : 
                               (a == &t->b) ? 2 : 3);
    int pos2 = (d->width/4) * ((b == &t->a) ? 1 :
                               (b == &t->b) ? 2 : 3);

    if (pos1 == pos2)
        return;

    int i;
    for (i = a->top+1; i < d->height-9; i++)
    {
        display_clear(d);

        draw_tower(d, t);
        draw_line(d, pos1 - disc, i, pos1 + disc, i);
        display_puts(d, 3, d->height-4, "Movements: %d", move_count);

        display_show(d);

#ifdef _WIN32
        Sleep(g_sleep);
#else
        usleep(g_sleep*1000);
#endif
    }
    for (i = pos1; i != pos2; i += (pos2 > pos1) ? 1:-1)
    {
        display_clear(d);

        draw_tower(d, t);
        draw_line(d, i - disc, d->height-9, i + disc, d->height-9);
        display_puts(d, 3, d->height-4, "Movements: %d", move_count);

        display_show(d);

#ifdef _WIN32
        Sleep(g_sleep);
#else
        usleep(g_sleep*1000);
#endif
    }
    for (i = d->height-9; i > b->top; i--)
    {
        display_clear(d);

        draw_tower(d, t);
        draw_line(d, pos2 - disc, i, pos2 + disc, i);
        display_puts(d, 3, d->height-4, "Movements: %d", move_count);

        display_show(d);

#ifdef _WIN32
        Sleep(g_sleep);
#else
        usleep(g_sleep*1000);
#endif
    }

    move_count++;
    stack_push(b, disc);
    display_puts(d, 3, d->height-4, "Movements: %d", move_count);
    display_show(d);
}


void
tower_solve(
    display *d, tower *t, int n,
    stack *a, stack *b, stack *c)
{
    if (n == 1)
    {
        tower_move_a(d, t, a, b);
        return;
    }

    tower_solve(d, t, n-1, a, c, b);
    tower_move_a(d, t, a, b);
    tower_solve(d, t, n-1, c, b, a);
}


void
tower_play(display *d, tower *t)
{
    int move;

    for (;;)
    {
        draw_tower(d, t);
        display_show(d);

        printf("\nMoves follow: N1N2, where N1 and N2 are the"
            " number of the corresponding stacks you want to"
            " move discs from and to, respectively.\n"
            "Example: 12, 32, 13, 23...\n\n");

        printf("\nMake your move:   \b\b");
        scanf("%d", &move);

        switch (move)
        {
            case 12: tower_move_a(d, t, &t->a, &t->b); break;
            case 13: tower_move_a(d, t, &t->a, &t->c); break;
            case 21: tower_move_a(d, t, &t->b, &t->a); break;
            case 23: tower_move_a(d, t, &t->b, &t->c); break;
            case 31: tower_move_a(d, t, &t->c, &t->a); break;
            case 32: tower_move_a(d, t, &t->c, &t->b); break;
            default: printf("\b\rCan't be done.      ");
        }
    }
}


void
tower_start(display *d)
{
    tower t;
    int n, p;

    printf("Number of discs: ");
    scanf("%d", &n);

    if (n > 15 || n <= 0)
    {
        printf("Please use a lower number of discs.\n"
                "0 or lower also won't do.\n");
        exit(1);
    }

    printf("\nDo you want to play or see the solution?\n"
        "1 - Play, anything else - See the solution\n");
    scanf("%d", &p);

    tower_create(&t, n);

    if (p == 1)
        tower_play(d, &t);
    else
        tower_solve(d, &t, n, &t.a, &t.c, &t.b);

    tower_destroy(&t);
}


int
main(int argc, char **argv)
{
    display d;
    display_create(&d, 120, 30);

    if (argc > 1)
    {
        char *e;
        g_sleep = strtoul(argv[1], &e, 10);

        if (e == argv[1])
        {
            printf("Invalid number.\n");
            exit(1);
        }
    }

    display_set_fill('O');
    tower_start(&d);

    display_destroy(&d);
}
