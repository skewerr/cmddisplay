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

#endif
