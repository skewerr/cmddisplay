#ifndef CMDTRF_H
#define CMDTRF_H

#include "cmdobj.h"

void pol_scale      (polygon *p, int ex, int ey, int fx, int fy);
void pol_rotate     (polygon *p, float deg, int fx, int fy);
void pol_translate  (polygon *p, int tx, int ty);

#endif
