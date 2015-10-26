#ifndef _CMDDISPLAY_H
#define _CMDDISPLAY_H

#ifndef _FILL_CHAR
static const char FILL_CHAR = 219;
#else
static const char FILL_CHAR = _FILL_CHAR;
#endif

#ifndef _EMPTY_CHAR
static const char EMPTY_CHAR = ' ';
#else
static const char EMPTY_CHAR = _EMPTY_CHAR;
#endif

typedef struct {
    int width, height;
    char *scr, *buf;
} display;


void display_create(display *, int, int);
void display_destroy(display *);

void display_gets(char *, int, display *, int, int);
char display_getc(display *, int, int);
void display_puts(display *, int, int, char *, ...);
void display_putc(display *, int, int, char);
void display_fill(display *, int, int);
void display_empty(display *, int, int);
void display_clear(display *);

void display_show(display *);

#endif
