#ifndef CMDOBJ_H
#define CMDOBJ_H

#include "cmddisplay.h"
#include "cmdqueue.h"

typedef struct {
	v_queue ver;
	int filled;
} polygon;

void obj_pol_create         (polygon *p, int faces);
void obj_pol_destroy        (polygon *p);

void obj_pol_add_vertex	    (polygon *p, int x, int y);

#endif
