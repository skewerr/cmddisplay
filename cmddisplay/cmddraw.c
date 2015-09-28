#include <math.h>
#include "cmddisplay.h"
#include "cmddraw.h"
#include "cmdclip.h"
#include "misc.h"


void
draw_line (display *d, int x1, int y1, int x2, int y2)
{
    if (x1 == x2)                           // Vertical line.
    {
        draw_line_v(d, x1, y1, y2);         // x is constant.
        return;
    }
    else if (y1 == y2)                      // Horizontal line.
    {
        draw_line_h(d, y1, x1, x2);         // y is constant.
        return;
    }

    float m = (float) (y2 - y1)/(x2 - x1);  // Angular coefficient.
    float n = y1 - m*x1;                    // Linear coefficient.

    if (fabs(m) < 1)
        draw_line_c1(d, x1, x2, m, n);      // Vertical candidates.

    else if (fabs(m) > 1)
        draw_line_c2(d, y1, y2, m, n);      // Horizontal candidates.

    else
    {
        if (x1 > x2)                        // If the angular coef. is 1
            switch_value(&x1, &x2);         // we should waste no more
                                            // processing power trying to
        int i;                              // rasterize the line segment.
        for (i = x1; i <= x2; i++)
            display_paint(d, i, i + n);     // Just (x, x + n).
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

    int i;
    for (i = x1; i <= x2; i++)
    {
        // TODO
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

    int i;
    for (i = x1; i <= x2; i++)
    {
        // TODO
    }
}
