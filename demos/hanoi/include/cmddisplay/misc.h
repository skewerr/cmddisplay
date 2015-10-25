#ifndef _CMDMISC_H
#define _CMDMISC_H

void misc_clear_scr(void);
void misc_set_cursor(int, int);
void misc_switch_val(int *, int *);

/*
 * These are inline functions(for speed, I guess?) used
 * in other compilation units. They are as follows:
 *
 * round_d - rounds a double to int.
 * round_f - rounds a float to int.
 */

static inline int
round_d(double d)
{
    return (long) (d + ((d >= 0) ? 0.5 : -0.5));
}

static inline int
round_f(float f)
{
    return (long) (f + ((f >= 0) ? 0.5f : -0.5f));
}

#endif
