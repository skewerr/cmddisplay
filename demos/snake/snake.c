#include <windows.h>
#include <conio.h>
#include <stdbool.h>
#include <cmddisplay.h>
#include <cmddraw.h>
#include <queue.h>

#define UP      72
#define LEFT    75
#define RIGHT   77
#define DOWN    80
#define ESC     27

#define B_SIZE  16

typedef struct {
    queue q;
    char d;
    pos h;
} snake;

static int g_sleep;


void
game_over (display *d)
{
    draw_sprite(d, "f/over", 12, 5);
    display_show(d);
    exit(0);
}


bool
valid_key (char c, snake *s)
{
    if (   (c == UP    && s->d == DOWN)
        || (c == DOWN  && s->d == UP)
        || (c == RIGHT && s->d == LEFT)
        || (c == LEFT  && s->d == RIGHT) )
        return false;

    if (c != UP && c != DOWN
        && c != LEFT && c != RIGHT
        && c != ESC)
        return false;

    return true;
}


void
snake_create (display *d, snake *s)
{
    queue_create(&s->q, (d->height-1)*(d->width-1));

    int i;
    for (i = 0; i < B_SIZE; i++)
    {
        s->h = position(4+i, d->height-4);
        queue_enqueue(&s->q, s->h);
    }

    s->d = RIGHT;
}


void
snake_move (display *d, snake *s)
{
    switch (s->d)
    {
        case UP:    s->h.y++; break;
        case DOWN:  s->h.y--; break;
        case LEFT:  s->h.x--; break;
        case RIGHT: s->h.x++; break;
        case ESC:   exit(1); break;
    }

    queue_dequeue(&s->q);
    queue_enqueue(&s->q, s->h);

    if (s->h.x < 1 || s->h.x >= d->width-1
        || s->h.y < 1 || s->h.y >= d->height-1)
        game_over(d);
}


void
draw_borders (display *d)
{
    draw_line(d, 0, 0, d->width-1, 0);
    draw_line(d, 0, 0, 0, d->height-1);
    draw_line(d, 0, d->height-1, d->width-1, d->height-1);
    draw_line(d, d->width-1, 0, d->width-1, d->height-1);
}


void
draw_snake (display *d, snake *s)
{
    queue_invert(&s->q);

    int i;
    for (i = 0; i < s->q.length; i++)
    {
        pos p = queue_dequeue(&s->q);
        display_paint(d, p.x, p.y);
        queue_enqueue(&s->q, p);
    }

    queue_invert(&s->q);
}


void
game_loop (display *d)
{
    snake s;
    snake_create(d, &s);

    while (1)
    {
        char c;
        while (kbhit())
            c = getch();

        if (valid_key(c, &s))
            s.d = c;

        snake_move(d, &s);
        display_clear(d);
        draw_borders(d);
        draw_snake(d, &s);
        display_show(d);

        Sleep(g_sleep);
    }
}


int
main (int argc, char **argv)
{
    display d;
    display_create(&d, 60, 30);

    if (argc > 1)
        g_sleep = atoi(argv[1]);
    else
        g_sleep = 50;

    game_loop(&d);

    display_destroy(&d);
}
