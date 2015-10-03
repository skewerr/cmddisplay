#include "cmddisplay.h"
#include "cmdfill.h"

void
fill_boundary_fill (display *d, int x, int y)
{
    if (x < 0 || x >= d->width
        || y < 0 || y >= d->height
        || d->screen[y*d->width + x] != EMPTY_CHAR)
        return;

    display_paint(d, x, y);

    fill_boundary_fill(d, x+1, y);
    fill_boundary_fill(d, x-1, y);
    fill_boundary_fill(d, x, y+1);
    fill_boundary_fill(d, x, y-1);
}
