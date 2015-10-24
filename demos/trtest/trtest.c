#include <unistd.h>
#include <cmddisplay.h>
#include <cmddraw.h>
#include <cmdobj.h>
#include <cmdtrf.h>
#include <cmdqueue.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

#define UP      72
#define LEFT    75
#define RIGHT   77
#define DOWN    80

int
main(void)
{
    display sc;
    polygon p;
    pos c;

    display_create(&sc, 160, 100);
    pol_create(&p, 7);

    pol_add_vertex(&p, 20, 5);
    pol_add_vertex(&p, 25, 5);
    pol_add_vertex(&p, 22.5, 5 + sqrt(18.75));

    c.x = 22.5;
    c.y = 5 + (sqrt(18.75)/3);

    srand(time(NULL));

    pol_scale(&p, 3, 3, c.x, c.y);
    pol_translate(&p, 30, 14);
    c.x += 30;
    c.y += 14;

    int i; char dir = 0;
    for(i = 0;;i++)
    {
        draw_polygon(&sc, &p);
        display_show(&sc);
        display_clear(&sc);
        pol_rotate(&p, -5, c.x, c.y);
        display_puts(&sc, 0, 0, "rot count: %d", i);

        display_put_raw(&sc, c.x, c.y, 'C');

        while (kbhit())
            dir = getch();

        switch (dir)
        {
            case UP: c.y++; break;
            case DOWN: c.y--; break;
            case RIGHT: c.x++; break;
            case LEFT: c.x--; break;
            case 'a': pol_add_vertex(&p, c.x, c.y); break;
            case 'h': pol_rotate(&p, 5, c.x, c.y); break;
            case 'r': pol_rotate(&p, -5, c.x, c.y); break;
        }
        
        dir = 0;
        usleep(15000);
    }

    display_destroy(&sc);
}
