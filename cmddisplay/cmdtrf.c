#include <math.h>
#include "cmdqueue.h"
#include "cmdobj.h"
#include "cmdtrf.h"

void
pol_translate (polygon *p, double tx, double ty)
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
pol_scale (polygon *p, double ex, double ey, double fx, double fy)
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
pol_rotate (polygon *p, double deg, double fx, double fy)
{
    pol_translate(p, -fx, -fy);

    deg *= M_PI / 180;
    
    int i;
    for (i = 0; i < p->ver.length; i++)
    {
        pos t_ver = v_queue_dequeue(&p->ver);

        double nx = t_ver.x*cos(deg) - t_ver.y*sin(deg);
        double ny = t_ver.x*sin(deg) + t_ver.y*cos(deg);
        
        t_ver.x = nx;
        t_ver.y = ny;
        
        v_queue_enqueue(&p->ver, t_ver);
    }

    pol_translate(p, fx, fy);
}
