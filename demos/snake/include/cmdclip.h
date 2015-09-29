#ifndef CMDCLIP_H
#define CMDCLIP_H

#include "cmddisplay.h"

/*
*   All of these return true if the clipped element is not
*   to be drawn. false otherwise.
*   
*   They receive pointers so that they can alter the values
*   of given coordinates before corresponding elements are
*   rasterized.
*/

int clip_line (             // Will clip a line segment
    display *d,             // based on an angular coef.,
    int *x1, int *x2,       // a linear coef., an initial
    int *y1, int *y2,       // point and a final one. Using
    float m, float n        // the Cohen-Sutherland algorithm.
);

int clip_line_x (           // These will act as wrappers for
    display *d,             // the clip_line function. Instead
    int *x1, int *x2,       // of giving pointers to y or x
    float m, float n        // files, these should fill in the
);                          // blanks based on m, n, and the
                            // coordinates it receives.
int clip_line_y (
    display *d,             // It then passes pointers to them
    int *y1, int *y2,       // to the clip_line function.
    float m, float n
);

#endif
