#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "display.h"
#include "misc.h"

/* Defining global variables. */

char FILL_CHAR = 219;
char EMPTY_CHAR = ' ';

/*
 * This is going to be the core of the cmddisplay library.
 * The functions here defined are as follows:
 *
 * display_create - creates displays after receiving width and height.
 * display_destroy - frees memory previously used by a display.
 * display_gets - reads a string from a display, given length and position.
 * display_getc - reads a character from position (x,y) in a display.
 * display_puts - formats a string and puts it in a display in (x,y).
 * display_putc - puts a character at position (x,y) of a display.
 * display_fill - puts a FILL_CHAR at position (x,y) of a display.
 * display_empty - puts an EMPTY_CHAR at position (x,y) of a display.
 * display_clear - turns every pixel in a display into EMPTY_CHAR.
 * display_show - exhibits the display onscreen.
 * display_set_fill - changes the FILL_CHAR character.
 * display_set_empty - changes the EMPTY_CHAR character.
 */

void
display_create(display *d, int width, int height)
{
    d->width = width;
    d->height = height;
    d->buf = NULL;

    if ((d->scr = malloc(width*height)) == NULL)
    {
        fprintf(stderr, "ERROR: Error allocating memory for a display.\n");
        exit(EXIT_FAILURE);
    }

    display_clear(d);
}

void
display_destroy(display *d)
{
    free(d->scr);
    free(d->buf);
}


void
display_gets(char *str, int size, display *d, int x, int y)
{
    int i;

    for (i = 0; (i < size - 1) && (x < d->width); i++)
        *(str++) = display_getc(d, x++, y);

    *str = '\0';
}

char
display_getc(display *d, int x, int y)
{
    if (x >= 0 && x < d->width && y >= 0 && y < d->height)
        return *(d->scr + (d->height - y - 1)*d->width + x);
    else
        return EMPTY_CHAR;
}


void
display_puts(display *d, int x, int y, char *fmt, ...)
{
    int tmpx, i;
    char *buf;

    if ((buf = malloc(d->width + 1)) == NULL)
    {
        fprintf(stderr, "ERROR: Error allocating memory for display_puts "
            "string buffer.\n");
        exit(EXIT_FAILURE);
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
    int i, j;
    char *buf, *lin, *stl;

    misc_clear_scr();

    if (d->buf == NULL)
    {
        if ((d->buf = malloc(d->height*(d->width + 1) + 1)) == NULL)
        {
            fprintf(stderr, "ERROR: Error allocating memory for display "
                "buffer in display_show() call.\n");
            exit(EXIT_FAILURE);
        }
    }

    if ((lin = malloc(d->width + 2)) == NULL)
    {
        fprintf(stderr, "ERROR: Error allocating memory for line buffer "
            "creation in display_show() call.\n");
        exit(EXIT_FAILURE);
    }

    buf = d->buf;
    stl = d->scr;

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

    free(lin);
}

void
display_set_fill(char nf)
{
    FILL_CHAR = nf;
}

void
display_set_empty(char ne)
{
    EMPTY_CHAR = ne;
}
