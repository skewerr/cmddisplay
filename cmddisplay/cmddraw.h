#ifndef CMDDRAW_H
#define CMDDRAW_H

#include "cmddisplay.h"
#include "cmdobj.h"

void draw_line              (display *d, int x1, int y1, int x2, int y2);
void draw_solid_rectangle   (display *d, int x1, int y1, int x2, int y2);
void draw_wire_rectangle    (display *d, int x1, int y1, int x2, int y2);
void draw_circumference     (display *d, int x, int y, int radius);
void draw_sprite            (display *d, char *path, int x, int y);
void draw_circumference_obj (display *d, circumference *c);
void draw_polygon           (display *d, polygon *p);

/*
* Inside cmddraw.c, you'll find:
*
* static void draw_line_c1 (display *d, int x1, int x2, float m, float n);
* static void draw_line_c2 (display *d, int y1, int y2, float m, float n);
*
* Respectively, these functions are responsible for rasterising
* straight lines with angular coefficients in the (-1, 1) and
* (-inf, -1)U(1, +inf) intervals. Lines with angular coefficients
* equal to 1 or -1 are dealt with by draw_line.
*
* static void draw_line_h (display *d, int y, int x1, int x2);
* static void draw_line_v (display *d, int x, int y1, int y2);
*
* Respectively, these functions are responsible for rasterizing
* horizontal and vertical lines.
*/

#endif
