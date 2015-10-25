#ifndef _TOWER_H
#define _TOWER_H

#include <stack.h>

typedef struct {
    stack a, b, c;
} tower;

void tower_create(tower *, int);
void tower_destroy(tower *);

void tower_print(tower *);
void tower_move(stack *, stack *);

#endif
