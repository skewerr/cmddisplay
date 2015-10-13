#include <unistd.h>
#include <cmddisplay.h>
#include <cmddraw.h>
#include <cmdobj.h>
#include <cmdtrf.h>
#include <cmdqueue.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

int
main(void)
{
    display sc;
    polygon p;
    pos c;

    display_create(&sc, 120, 30);
    pol_create(&p, 5);

    pol_add_vertex(&p, 20, 5);
    pol_add_vertex(&p, 25, 5);
    pol_add_vertex(&p, 22.5, 5 + sqrt(18.75));

    c.x = 22.5;
    c.y = 5 + (sqrt(18.75)/3);

    srand(time(NULL));

    pol_scale(&p, 3, 3, c.x, c.y);
    pol_translate(&p, 20, 4);
    c.x += 20;
    c.y += 4;

    int i;
    for(i = 0;;i++)
    {
        draw_polygon(&sc, &p);
        display_show(&sc);
        display_clear(&sc);
        pol_rotate(&p, -5, c.x, c.y);
        display_puts(&sc, 0, 0, "rot count: %d", i);

        display_put_raw(&sc, c.x, c.y, 'C');

        usleep(15000);
    }

    display_destroy(&sc);
}
