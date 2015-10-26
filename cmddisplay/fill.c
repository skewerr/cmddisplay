#include "fill.h"

void
fill_boundary(display *d, int x, int y)
{
    if (x < 0 || x >= d->width ||
        y < 0 || y >= d->height)
        return;

    display_fill(d, x, y);

    if (display_getc(d, x, y+1) == EMPTY_CHAR)
        fill_boundary(d, x, y+1);

    if (display_getc(d, x+1, y) == EMPTY_CHAR)
        fill_boundary(d, x+1, y);

    if (display_getc(d, x, y-1) == EMPTY_CHAR)
        fill_boundary(d, x, y-1);

    if (display_getc(d, x-1, y) == EMPTY_CHAR)
        fill_boundary(d, x-1, y);
}
