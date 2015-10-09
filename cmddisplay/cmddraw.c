#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "cmddisplay.h"
#include "cmdqueue.h"
#include "cmddraw.h"
#include "cmdclip.h"
#include "cmdmisc.h"
#include "cmdobj.h"


/* Prototypes. */
static void draw_line_c1    (display *d, int x1, int x2, float m, float n);
static void draw_line_c2    (display *d, int y1, int y2, float m, float n);
static void draw_line_h     (display *d, int y, int x1, int x2);
static void draw_line_v     (display *d, int x, int y1, int y2);


void
draw_polygon (display *d, polygon *p)
{
    pos a, b;
    int i;

    if (p->ver.length < 3)
    {
        printf("ERROR: Attempt to draw invalid polygon.\n");
        return;
    }

    a = v_queue_dequeue(&p->ver);

    for (i = 0; i < p->ver.length + 1; i++)
    {
        b = a;
        a = v_queue_dequeue(&p->ver);

        v_queue_enqueue(&p->ver, b);

        draw_line(d, a.x, a.y, b.x, b.y);
    }

    v_queue_enqueue(&p->ver, a);
}


void
draw_solid_rectangle (display *d, int x1, int y1, int x2, int y2)
{
    int i, j;
    for (i = x1; i != x2; i += (x1 > x2) ? -1:1)
        for (j = y1; j != y2; j += (y1 > y2) ? -1:1)
            display_paint(d, i, j);
}


void
draw_wire_rectangle (display *d, int x1, int y1, int x2, int y2)
{
    draw_line(d, x1, y1, x1, y2);
    draw_line(d, x1, y1, x2, y1);
    draw_line(d, x1, y2, x2, y2);
    draw_line(d, x2, y1, x2, y2);
}


void
draw_circumference (display *d, int x, int y, int radius)
{
    display_paint(d, x + radius, y);
    display_paint(d, x, y + radius);
    display_paint(d, x - radius, y);
    display_paint(d, x, y - radius);

    int i = radius, j = 0;
    for (;;)
    {
        float m = (float) j/i;

        if (m >= 1)
            break;

        float a1 = fabs(pow(radius, 2) - (pow(i, 2) + pow(j+1, 2)));
        float a2 = fabs(pow(radius, 2) - (pow(i-1, 2) + pow(j, 2)));
        float a3 = fabs(pow(radius, 2) - (pow(i-1, 2) + pow(j+1, 2)));

        if (a1 <= a2 && a1 <= a3)
            display_paint(d, x + i, y + ++j);
        else if (a2 <= a3)
            display_paint(d, x + --i, y + j);
        else
            display_paint(d, x + --i, y + ++j);
        
        display_paint(d, x+j, y+i);
        display_paint(d, x-j, y+i);
        display_paint(d, x-i, y+j);
        display_paint(d, x-i, y-j);
        display_paint(d, x-j, y-i);
        display_paint(d, x+j, y-i);
        display_paint(d, x+i, y-j);
    }
}


void
draw_sprite (display *d, char *path, int x, int y)
{
    FILE *sp = fopen(path, "r");

    if (sp == NULL)
    {
        printf("ERROR: Can't read file %s. Does it exist?\n", path);
        exit(1);
    }

    char t, i = x;
    while ((t = fgetc(sp)) != EOF)
    {
        if (t != '\n' && t != ' ')
            display_put_raw(d, i++, d->height-1 - y, t);
        else if (t == ' ')
            i++;
        else
        { y++; i = x; }
    }

    fclose(sp);
}


void
draw_line (display *d, int x1, int y1, int x2, int y2)
{
    if (x1 == x2)
    {
        draw_line_v(d, x1, y1, y2);
        return;
    }
    else if (y1 == y2)
    {
        draw_line_h(d, y1, x1, x2);
        return;
    }

    float m = (float) (y2 - y1)/(x2 - x1);
    float n = y1 - m*x1;

    if (fabs(m) < 1)
        draw_line_c1(d, x1, x2, m, n);

    else if (fabs(m) > 1)
        draw_line_c2(d, y1, y2, m, n);

    else
    {
        if (x1 > x2)
            switch_value(&x1, &x2);

        int i;
        for (i = x1; i <= x2; i++)
            display_paint(d, i, ((m > 0) ? 1:-1)*i + n);
    }
}


static void
draw_line_v (display *d, int x, int y1, int y2)
{
    int i;

    if (y1 > y2)
        switch_value(&y1, &y2);

    for (i = y1; i <= y2; i++)
        display_paint(d, x, i);
}


static void
draw_line_h (display *d, int y, int x1, int x2)
{
    int i;

    if (x1 > x2)
        switch_value(&x1, &x2);

    for (i = x1; i <= x2; i++)
        display_paint(d, i, y);
}


static void
draw_line_c1 (
    display *d,
    int x1, int x2,
    float m, float n )
{
    if (clip_line_x(d, &x1, &x2, m, n))
        return;

    if (x1 > x2)
        switch_value(&x1, &x2);

    int y1 = (long) (m*x1 + n + 0.5);

    int c1 = y1, c2 = y1 + ((m > 0) ? 1:-1);

    int i;
    for (i = x1; i <= x2; i++)
    {
        float dif1 = fabs((m*i + n) - c1);
        float dif2 = fabs((m*i + n) - c2);

        if (dif1 > dif2)
        {
            display_paint(d, i, c2);
            c1 += (m > 0) ? 1:-1;
            c2 += (m > 0) ? 1:-1;
        }
        else
            display_paint(d, i, c1);
    }
}


static void
draw_line_c2 (
    display *d,
    int y1, int y2,
    float m, float n )
{
    if (clip_line_y(d, &y1, &y2, m, n))
        return;

    if (y1 > y2)
        switch_value(&y1, &y2);

    int x1 = (long) ((y1 - n)/m + 0.5);

    int c1 = x1, c2 = x1 + ((m > 0) ? 1:-1);

    int i;
    for (i = y1; i <= y2; i++)
    {
        float dif1 = fabs((i - n)/m - c1);
        float dif2 = fabs((i - n)/m - c2);

        if (dif1 > dif2)
        {
            display_paint(d, c2, i);
            c1 += (m > 0) ? 1:-1;
            c2 += (m > 0) ? 1:-1;
        }
        else
            display_paint(d, c1, i);
    }
}
