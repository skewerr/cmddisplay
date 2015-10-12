#include <math.h>
#include "cmdqueue.h"
#include "cmdobj.h"
#include "cmdtrf.h"

void
pol_translate (polygon *p, int tx, int ty)
{
    int i;
    for (i = 0; i < p->ver.length; i++)
    {
        pos t_ver = v_queue_dequeue(&p->ver);
        t_ver.x += tx;
        t_ver.y += ty;
        v_queue_enqueue(&p->ver, t_ver);
    }
}

void
pol_scale (polygon *p, int ex, int ey, int fx, int fy)
{
    pol_translate(p, -fx, -fy);

    int i;
    for (i = 0; i < p->ver.length; i++)
    {
        pos t_ver = v_queue_dequeue(&p->ver);
        t_ver.x *= ex;
        t_ver.y *= ey;
        v_queue_enqueue(&p->ver, t_ver);
    }

    pol_translate(p, fx, fy);
}

void
pol_rotate (polygon *p, float deg, int fx, int fy)
{
    pol_translate(p, -fx, -fy);

    double r_deg = deg * M_PI / 180;
    
    int i;
    for (i = 0; i < p->ver.length; i++)
    {
        pos t_ver = v_queue_dequeue(&p->ver);

        float nx = t_ver.x*cos(r_deg) - t_ver.y*sin(r_deg);
        float ny = t_ver.x*sin(r_deg) + t_ver.y*cos(r_deg);
        
        t_ver.x = (long) (nx + ((nx > 0) ? 0.5:-0.5));
        t_ver.y = (long) (ny + ((ny > 0) ? 0.5:-0.5));
        
        v_queue_enqueue(&p->ver, t_ver);
    }

    pol_translate(p, fx, fy);
}
