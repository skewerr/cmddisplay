#include <stdbool.h>
#include "cmddisplay.h"
#include "cmdclip.h"

#define true 1
#define false 0

int
clip_line (
    display *d,
    int *x1, int *x2,
    int *y1, int *y2,
    float m, float n )
{
    if (*x1 < 0 && *x2 < 0)                     // Testing for the left
        return true;                            // screen boundary.
    else if (*x1 < 0)                           // x = 0.
    { *x1 = 0; *y1 = n; }
    else
    { *x2 = 0; *y2 = n; }

    if (*y1 >= d->height && *y2 >= d->height)   // Testing for the upper
        return true;                            // screen boundary.
    else if (*y1 >= d->height)                  // y = d->height - 1
    { *y1 = d->height -1; *x1 = (*y1 - n)/m; }
    else
    { *y2 = d->height -1; *x2 = (*y2 - n)/m; }

    if (*x1 >= d->width && *x2 >= d->width)     // Testing for the right
        return true;                            // screen boundary.
    else if (*x1 >= d->width)                   // x = d->width - 1
    { *x1 = d->width -1; *y1 = m*(*x1) + n; }
    else
    { *x2 = d->width -1; *y2 = m*(*x1) + n; }

    if (*y1 < 0 && *y2 < 0)                     // Testing for the lower
        return true;                            // screen boundary.
    else if (*y1 < 0)                           // y = 0
    { *y1 = 0; *x1 = (-n)/m; }
    else
    { *y2 = 0; *x2 = (-n)/m; }

    return false;
}


int
clip_line_x (
    display *d,
    int *x1, int *x2,
    float m, float n )
{
    float   y1f = m*(*x1) + n;
    float   y2f = m*(*x2) + n;
    int     y1  = (long) ((y1f >= 0) ? (y1f + 0.5):(y1f - 0.5));
    int     y2  = (long) ((y2f >= 0) ? (y2f + 0.5):(y2f - 0.5));

    return clip_line(d, x1, x2, &y1, &y2, m, n);
}


int
clip_line_y (
    display *d,
    int *y1, int *y2,
    float m, float n )
{
    float   x1f = (*y1 - n)/m;
    float   x2f = (*y2 - n)/m;
    int     x1  = (long) ((x1f >= 0) ? (x1f + 0.5):(x1f - 0.5));
    int     x2  = (long) ((x2f >= 0) ? (x2f + 0.5):(x2f - 0.5));

    return clip_line(d, &x1, &x2, y1, y2, m, n);
}
