#ifndef CMDTRF_H
#define CMDTRF_H

#include "cmdobj.h"

void pol_scale      (polygon *p, double ex, double ey, double fx, double fy);
void pol_rotate     (polygon *p, double deg, double fx, double fy);
void pol_translate  (polygon *p, double tx, double ty);

#endif
