#include "cmddisplay.h"
#include "cmdqueue.h"
#include "cmdobj.h"

#define true    1
#define false   0

void
obj_pol_create (polygon *p, int faces)
{
    v_queue_create(&p->ver, faces);
    p->filled = false;
}

void
obj_pol_destroy (polygon *p)
{
    v_queue_destroy(&p->ver);
}

void
obj_pol_add_vertex (polygon *p, int x, int y)
{
    pos v;
    v.x = x;
    v.y = y;

    if (v_queue_is_full(&p->ver))
        v_queue_dequeue(&p->ver);

    v_queue_enqueue(&p->ver, v);
}
