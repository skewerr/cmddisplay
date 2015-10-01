#ifndef CMDDRAW_H
#define CMDDRAW_H

#include "cmddisplay.h"

void draw_line              (display *d, int x1, int y1, int x2, int y2);
void draw_sprite            (display *d, char *path, int x, int y);
void draw_solid_rectangle   (display *d, int x1, int y1, int x2, int y2);
void draw_wire_rectangle    (display *d, int x1, int y1, int x2, int y2);

static void draw_line_v     (display *d, int x, int y1, int y2);
static void draw_line_h     (display *d, int y, int x1, int x2);

static void draw_line_c1 (  // Used to draw straight lines with
    display *d,             // an angular coefficient in the
    int x1, int x2,         // (-1, 1) interval. Candidate
    float m, float n        // pixels are on top of one another.
);                          // m and n (y = mx + n) are given.

static void draw_line_c2 (  // Used to draw straight lines with
    display *d,             // an angular coefficient in the
    int y1, int y2,         // (-inf, -1)U(1, +inf) interval.
    float m, float n        // Candidate pixels are next to
);                          // each other. Again, m and n.

#endif
