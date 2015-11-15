#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "draw.h"
#include "clip.h"
#include "misc.h"

/*
 * This unit contains functions useful for drawing objects onto
 * a display. There are a few static functions that will aid other
 * functions in this unit, such as draw_line_* functions.
 *
 * The functions here are the following:
 *
 * draw_line - used to draw lines in a display, given coordinates.
 * draw_file - used to load file contents into a display. Starts
 *     at given (x,y) coordinates.
 * draw_circumference - used to draw circumferences in a display,
 *     given center coordinates and radius.
 *
 * Static functions:
 *
 * draw_line_h - used to draw horizontal lines in a display.
 * draw_line_v - used to draw vertical lines in a display.
 * draw_line_c1 - used to draw lines with vertical candidate pixels.
 * draw_line_c2 - used to draw lines with horizontal candidate pixels.
 */

/* Prototypes. */

static void draw_line_h(display *, int, int, int);
static void draw_line_v(display *, int, int, int);
static void draw_line_c1(display *, int, int, float, float);
static void draw_line_c2(display *, int, int, float, float);


void
draw_circumference(display *d, int x, int y, unsigned int radius)
{
    float m;
    int i, j;

    if (radius == 0)
    {
        display_fill(d, x, y);
        return;
    }

    display_fill(d, x + radius, y);
    display_fill(d, x, y + radius);
    display_fill(d, x - radius, y);
    display_fill(d, x, y - radius);

    i = radius;
    j = 0;

    for (;;)
    {
        m = (float) j/i;

        if (m >= 1)
            break;

        float a1 = fabs(pow(radius, 2) - (pow(i, 2) + pow(j+1, 2)));
        float a2 = fabs(pow(radius, 2) - (pow(i-1, 2) + pow(j, 2)));
        float a3 = fabs(pow(radius, 2) - (pow(i-1, 2) + pow(j+1, 2)));

        if (a1 <= a2 && a1 <= a3)
            display_fill(d, x + i, y + ++j);
        else if (a2 <= a3)
            display_fill(d, x + --i, y + j);
        else
            display_fill(d, x + --i, y + ++j);
        
        display_fill(d, x+j, y+i);
        display_fill(d, x-j, y+i);
        display_fill(d, x-i, y+j);
        display_fill(d, x-i, y-j);
        display_fill(d, x-j, y-i);
        display_fill(d, x+j, y-i);
        display_fill(d, x+i, y-j);
    }
}


void
draw_file(display *d, int x, int y, char *path)
{
    FILE *fp;
    int i;
    char t;

    if ((fp = fopen(path, "r")) == NULL)
    {
        fprintf(stderr, "ERROR: Error opening file %s.\n", path);
        perror("\tError given");
        exit(EXIT_FAILURE);
    }

    y = d->height - y - 1;

    for (i = x; (t = fgetc(fp)) != EOF;)
    {
        if (t == '\n')
        {
            y--;
            i = x;
        }
        else if (t != ' ')
            display_putc(d, i++, y, t);
        else
            i++;
    }
}


void
draw_line(display *d, int x1, int y1, int x2, int y2)
{
    float m = ((x2 - x1) ? (float) (y2 - y1)/(x2 - x1) : 0.0f);
    float n = y1 - m*x1;

    if (clip_line(d, &x1, &y1, &x2, &y2))
        return;

    if (x1 == x2)
        draw_line_v(d, x1, y1, y2);
    else if (y1 == y2)
        draw_line_h(d, y1, x1, x2);

    else if (fabs(m) < 1)
        draw_line_c1(d, x1, x2, m, n);
    else if (fabs(m) > 1)
        draw_line_c2(d, y1, y2, m, n);

    else
    {
        for (; x1 != x2; x1 += (x1 < x2) ? 1:-1)
        {
            display_fill(d, x1, y1);
            y1 += (y1 < y2) ? 1:-1;
        }

        display_fill(d, x2, y2);
    }
}

static void
draw_line_c1(display *d, int x1, int x2, float m, float n)
{
    int c1y, c2y;

    if (x1 > x2)
        misc_switch_val(&x1, &x2);

    c1y = round_f(m*x1 + n);
    c2y = c1y + ((m > 0) ? 1:-1);

    for (; x1 < x2; x1++)
    {
        float dif1 = fabs(m*x1 + n - c1y);
        float dif2 = fabs(m*x1 + n - c2y);

        if (dif2 < dif1)
        {
            c1y = c2y;
            c2y += (m > 0) ? 1:-1;
        }

        display_fill(d, x1, c1y);
    }

    display_fill(d, x2, round_f(m*x2 + n));
}

static void
draw_line_c2(display *d, int y1, int y2, float m, float n)
{
    int c1x, c2x;

    if (y1 > y2)
        misc_switch_val(&y1, &y2);

    c1x = round_f((y1 - n)/m);
    c2x = c1x + ((m > 0) ? 1:-1);

    for (; y1 < y2; y1++)
    {
        float dif1 = fabs((y1 - n)/m - c1x);
        float dif2 = fabs((y1 - n)/m - c2x);

        if (dif2 < dif1)
        {
            c1x = c2x;
            c2x += (m > 0) ? 1:-1;
        }

        display_fill(d, c1x, y1);
    }

    display_fill(d, round_f((y2 - n)/m), y2);
}

static void
draw_line_v(display *d, int x, int y1, int y2)
{
    for (; y1 != y2; y1 += (y1 < y2) ? 1:-1)
        display_fill(d, x, y1);

    display_fill(d, x, y2);
}

static void
draw_line_h(display *d, int y, int x1, int x2)
{
    for (; x1 != x2; x1 += (x1 < x2) ? 1:-1)
        display_fill(d, x1, y);

    display_fill(d, x2, y);
}
