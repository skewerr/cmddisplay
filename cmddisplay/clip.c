#include "clip.h"
#include "misc.h"

#define true    1
#define false   0

/*
 * This unit contains functions responsible for clipping elements
 * based on what a display can contain. Its functions will receive
 * pointers to coordinates or other elements, which they will change
 * if need be. If they conclude that the element cannot be displayed
 * and therefore shall be completely clipped, it will return true.
 * When that happens, the functions that called them should stop
 * trying to rasterise the element further.
 *
 * The functions are as follows:
 *
 * clip_line - receives pointers to line coordinates and clips it.
 *     The algorithm used for the clipping is Cohen-Sutherland's.
 */

int
clip_line(display *d, int *x1, int *y1, int *x2, int *y2)
{
    float m = (*x2 - *x1) ? (float) (*y2 - *y1)/(*x2 - *x1) : 0;
    float n = *y1 - m*(*x1);

    /* Relative to the left boundary. */

    if (*x1 < 0 && *x2 < 0)
        return true;
    else if (*x1 < 0)
    {
        *x1 = 0;
        *y1 = round_f(n);
    }
    else if (*x2 < 0)
    {
        *x2 = 0;
        *y2 = round_f(n);
    }

    /* Relative to the bottom boundary. */

    if (*y1 < 0 && *y2 < 0)
        return true;
    else if (*y1 < 0)
    {
        *y1 = 0;
        *x1 = round_f(-n/m);
    }
    else if (*y2 < 0)
    {
        *y2 = 0;
        *x2 = round_f(-n/m);
    }

    /* Relative to the right boundary. */

    if (*x1 >= d->width && *x2 >= d->width)
        return true;
    else if (*x1 >= d->width)
    {
        *x1 = d->width - 1;
        *y1 = round_f(m*(*x1) + n);
    }
    else if (*x2 >= d->width)
    {
        *x2 = d->width - 1;
        *y2 = round_f(m*(*x2) + n);
    }

    /* Relative to the top boundary. */

    if (*y1 >= d->height && *y2 >= d->height)
        return true;
    else if (*y1 >= d->height)
    {
        *y1 = d->height - 1;
        *x1 = round_f((*y1 - n)/m);
    }
    else if (*y2 >= d->height)
    {
        *y2 = d->height - 1;
        *x2 = round_f((*y2 - n)/m);
    }

    return false;
}
