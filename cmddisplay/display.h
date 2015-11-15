#ifndef _CMDDISPLAY_H
#define _CMDDISPLAY_H

extern char FILL_CHAR;
extern char EMPTY_CHAR;

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

void display_set_fill(char);
void display_set_empty(char);

#endif
