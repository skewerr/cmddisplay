#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "cmddisplay.h"
#include "misc.h"

static const char EMPTY_CHAR  = ' ';
static const char FILL_CHAR   = 219;


void
display_create (display *d, int width, int height)
{
    d->height   = height;
    d->width    = width;
    d->screen   = (char*) malloc(height*width*sizeof(char));

    int i;
    for (i = 0; i < height*width; i++)
        d->screen[i] = EMPTY_CHAR;
}


void
display_put_raw (display *d, int x, int y, char c)
{
    if (x >= 0 && x < d->width
        && y >= 0 && y < d->height)
        d->screen[y*d->width + x] = c;
}


void
display_paint (display *d, int x, int y)
{
    if (x >= 0 && x < d->width
        && y >= 0 && y < d->height)
        d->screen[y*d->width + x] = FILL_CHAR;
}


void
display_empty (display *d, int x, int y)
{
    if (x >= 0 && x < d->width
        && y >= 0 && y < d->height)
        d->screen[y*d->width + x] = EMPTY_CHAR;
}


void
display_show (display *d)
{
    static bool cleared = false;

    if (!cleared)
    {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        cleared = true;
    }

    char buf[d->height*(d->width + 1) + 1];
    char line[d->width + 2];
    int i, j;

    line[d->width + 1]  = '\0';
    line[d->width]      = '\n';
    buf[0]              = '\0';

    for (i = d->height-1; i >= 0; i--)
    {
        for (j = 0; j < d->width; j++)
            line[j] = d->screen[i*d->width + j];

        strcat(buf, line);
    }

    set_cursor(0, 0);
    printf(buf);
}


void
display_clear (display *d)
{
    int i;
    for (i = 0; i < d->height*d->width; i++)
        d->screen[i] = EMPTY_CHAR;
}


void
display_destroy (display *d)
{
    free(d->screen);
}
