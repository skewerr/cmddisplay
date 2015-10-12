#ifndef CMDOBJ_H
#define CMDOBJ_H

#include "cmddisplay.h"
#include "cmdqueue.h"

/* Polygons. */

typedef struct {
	v_queue ver;
	int filled;
} polygon;

void pol_create         (polygon *p, int faces);
void pol_destroy        (polygon *p);

void pol_add_vertex	    (polygon *p, int x, int y);

/* Circumferences. */

typedef struct {
    int rad;
    pos center;
	int filled;
} circumference;

void circ_create        (circumference *c, int x, int y, int rad);

void circ_set_center    (circumference *c, int x, int y);
void circ_set_radius    (circumference *c, int rad);

#endif
