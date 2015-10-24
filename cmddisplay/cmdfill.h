#ifndef CMDFILL_H
#define CMDFILL_H

#include "cmddisplay.h"
#include "cmdobj.h"

void fill_boundary_fill (display *d, int x, int y);
void fill_scan_line     (display *d, polygon *p);

#endif
