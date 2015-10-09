#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <cmddisplay.h>
#include <cmdqueue.h>
#include <cmddraw.h>
#include <cmdobj.h>

int
main (void)
{
    display scr;
    polygon p;

    display_create(&scr, 80, 35);
    obj_pol_create(&p, 5);
    srand(time(NULL));

    for (;;)
    {
        obj_pol_add_vertex(&p, 1 + abs(rand() % scr.width-2), 1 + abs(rand() % scr.height-2));
        obj_pol_add_vertex(&p, 1 + abs(rand() % scr.width-2), 1 + abs(rand() % scr.height-2));
        obj_pol_add_vertex(&p, 1 + abs(rand() % scr.width-2), 1 + abs(rand() % scr.height-2));
        obj_pol_add_vertex(&p, 1 + abs(rand() % scr.width-2), 1 + abs(rand() % scr.height-2));
        obj_pol_add_vertex(&p, 1 + abs(rand() % scr.width-2), 1 + abs(rand() % scr.height-2));

        draw_polygon(&scr, &p);

        display_show(&scr);
        display_clear(&scr);
#ifdef _WIN32
        Sleep(150);
#else
        usleep(150000);
#endif
    }
}
