#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "cmddisplay/cmddisplay.h"

int
main (void)
{
    display d;
    display_create(&d, 50, 20);

    display_show(&d);

    int i;
    for (i = 0; i < 10; i++)
    {
#ifdef _WIN32
        Sleep(200);
#else
        usleep(200000);
#endif
        display_paint(&d, i, i);
        display_show(&d);
    }

    display_destroy(&d);
}
