#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "display.h"
#include "misc.h"

/*
 * This is going to be the core of the cmddisplay library.
 * The functions here defined are as follows:
 *
 * display_create - creates displays after receiving width and height.
 * display_destroy - frees memory previously used by a display.
 * display_puts - formats a string and puts it in a display in (x,y).
 * display_putc - puts a character at position (x,y) of a display.
 * display_fill - puts a FILL_CHAR at position (x,y) of a display.
 * display_empty - puts an EMPTY_CHAR at position (x,y) of a display.
 * display_clear - turns every pixel in a display into EMPTY_CHAR.
 * display_show - exhibits the display onscreen.
 */

void
display_create(display *d, int width, int height)
{
    d->width = width;
    d->height = height;
    d->scr = malloc(width*height);

    if (d->scr == NULL)
    {
        fprintf(stderr, "ERROR: Error allocating memory for a display.\n");
        exit(1);
    }

    display_clear(d);
}

void
display_destroy(display *d)
{
    free(d->scr);
}


void
display_puts(display *d, int x, int y, char *fmt, ...)
{
    char *buf = malloc(d->width + 1);
    int tmpx, i;

    if (buf == NULL)
    {
        fprintf(stderr, "ERROR: Error allocating memory for display_puts "
            "string buffer.\n");
        exit(1);
    }

    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, d->width + 1, fmt, ap);
    va_end(ap);

    tmpx = x;

    for (i = 0; *(buf + i); i++)
    {
        if (*(buf + i) != '\n')
        {
            display_putc(d, tmpx, y, *(buf + i));
            tmpx++;
        }
        else
        {
            tmpx = x;
            y++;
        }
    }

    free(buf);
}

void
display_putc(display *d, int x, int y, char c)
{
    if (x >= 0 && x < d->width && y >= 0 && y < d->height)
        *(d->scr + (d->height - y - 1)*d->width + x) = c;
}

void
display_fill(display *d, int x, int y)
{
    display_putc(d, x, y, FILL_CHAR);
}

void
display_empty(display *d, int x, int y)
{
    display_putc(d, x, y, EMPTY_CHAR);
}

void
display_clear(display *d)
{
    int i;
    for (i = 0; i < d->width*d->height; i++)
        *(d->scr + i) = EMPTY_CHAR;
}


void
display_show(display *d)
{
    misc_clear_scr();

    char *buf = malloc(d->height*(d->width + 1) + 1);
    char *lin = malloc(d->width + 2);
    char *stl = d->scr;
    int i, j;

    if (buf == NULL || lin == NULL)
    {
        fprintf(stderr, "ERROR: Error allocating memory for display buffer "
            "creation in display_show().\n");
        exit(1);
    }

    *buf = *(lin + d->width + 1) = '\0';
    *(lin + d->width) = '\n';

    for (i = 0; i < d->height; i++)
    {
        for (j = 0; j < d->width; j++)
            *(lin + j) = *(stl++);

        strcat(buf, lin);
    }

    misc_set_cursor(0,0);
    printf(buf);

    free(buf);
    free(lin);
}
