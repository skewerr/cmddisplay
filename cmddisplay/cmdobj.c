#include "cmddisplay.h"
#include "cmdqueue.h"
#include "cmdobj.h"

#define true    1
#define false   0

/* Polygons. */

void
pol_create (polygon *p, int faces)
{
    v_queue_create(&p->ver, faces);
    p->filled = false;
}

void
pol_destroy (polygon *p)
{
    v_queue_destroy(&p->ver);
}

void
pol_add_vertex (polygon *p, int x, int y)
{
    pos v;
    v.x = x;
    v.y = y;

    if (v_queue_is_full(&p->ver))
        v_queue_dequeue(&p->ver);

    v_queue_enqueue(&p->ver, v);
}

/* Circumferences. */

void
circ_create (circumference *c, int x, int y, int rad)
{
    c->center.x = x;
    c->center.y = y;
    c->rad      = rad;
    c->filled   = false;
}

void
circ_set_center (circumference *c, int x, int y)
{
    c->center.x = x;
    c->center.y = y;
}

void
circ_set_radius (circumference *c, int rad)
{
    c->rad = rad;
}
