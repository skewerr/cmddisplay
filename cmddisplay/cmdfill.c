#include "cmddisplay.h"
#include "cmdqueue.h"
#include "cmdfill.h"

void
fill_boundary_fill (display *d, int x, int y)
{
    if (x < 0 || x >= d->width
        || y < 0 || y >= d->height
        || display_getc(d, x, y) != EMPTY_CHAR)
        return;

    display_paint(d, x, y);

    fill_boundary_fill(d, x+1, y);
    fill_boundary_fill(d, x-1, y);
    fill_boundary_fill(d, x, y+1);
    fill_boundary_fill(d, x, y-1);
}

void
fill_scan_line (display *d, polygon *p)
{
    v_queue pa_ver;
    v_queue_create(&pa_ver, p->ver.length);
    
    /* Grabbing minimum and maximum y. */

    int y_min, y_max;
    int i;
    for (i = 0; i < p->ver.length; i++)
    {
        pos t_ver = v_queue_dequeue(&p->ver);

        if (!i || t_ver.y < y_min)
            y_min = t_ver.y;
        if (!i || t_ver.y > y_max)
            y_max = t_ver.y;

        v_queue_enqueue(&p->ver, t_ver);
    }

    /* Grabbing the significant vertices. */

    pos a, b;

    a = v_queue_dequeue(&p->ver);

    for (i = 0; i < p->ver.length + 1; i++)
    {
        b = a;
        a = v_queue_dequeue(&p->ver);

        v_queue_enqueue(&p->ver, b);

        struct {
            double ang_coef, lin_coef;
            int x_min, x_max;
        } side;

        side.ang_coef = (a.y - b.y)/(a.x - b.x);
        side.lin_coef = a.y - side.ang_coef*a.x;

        pos intersec;

        if (!(side.ang_coef))
            continue;

        // intersec.x = ;
    }

    v_queue_enqueue(&p->ver, a);


    v_queue_destroy(&pa_ver);
}
