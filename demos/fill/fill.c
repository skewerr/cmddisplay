#include <unistd.h>
#include <cmddisplay/display.h>
#include <cmddisplay/draw.h>
#include <cmddisplay/fill.h>

int
main(void)
{
    display scr;
    display_create(&scr, 80, 30);

    draw_line(&scr,  3,  6, 24, 23);
    draw_line(&scr, 24, 23, 50, 10);
    draw_line(&scr, 50, 10,  3,  6);
    display_show(&scr);
    sleep(1);

    fill_boundary(&scr, 20, 12);
    display_show(&scr);
    sleep(1);

    display_destroy(&scr);
}
