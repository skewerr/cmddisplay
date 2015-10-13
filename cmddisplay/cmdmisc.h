#ifndef MISC_H
#define MISC_H

void switch_value   (int *a, int *b);
void set_cursor     (int x, int y);

/* These functions are inline! */

static inline int round_d (double r)
{
    return (long) (r + ((r > 0) ? 0.5:-0.5));
}
static inline int round_f (float r)
{
    return (long) (r + ((r > 0) ? 0.5:-0.5));
}

#endif
