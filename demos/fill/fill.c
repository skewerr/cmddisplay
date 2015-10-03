#include <unistd.h>
#include <cmddisplay.h>
#include <cmddraw.h>

int
main (void)
{
    display scr;
    display_create(&scr, 80, 30);

    draw_line(&scr, 3, 6, 24, 23);
    draw_line(&scr, 24, 23, 50, 10);
    draw_line(&scr, 50, 10, 3, 6);

    display_show(&scr);
    sleep(1);

    fill_boundary_fill(&scr, 20, 12);
    display_show(&scr);
    sleep(1);

    display_clear(&scr);
    draw_circumference(&scr, 40, 15, 4);
    display_show(&scr);
    sleep(1);

    draw_circumference(&scr, 40, 15, 8);
    display_show(&scr);

    display_destroy(&scr);
}
