#ifndef CMDDISPLAY_H
#define CMDDISPLAY_H

static const char EMPTY_CHAR  = ' ';
static const char FILL_CHAR   = 219;

typedef struct {
    int height, width;
    char *screen;
} display;

void display_create     (display *d, int width, int height);
void display_put_raw    (display *d, int x, int y, char c);
void display_paint      (display *d, int x, int y);
void display_empty      (display *d, int x, int y);
void display_show       (display *d);
void display_clear      (display *d);
void display_destroy    (display *d);

void display_puts       (display *d, int x, int y, char *fmt, ...);

#endif
