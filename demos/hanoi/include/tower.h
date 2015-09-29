#ifndef TOWER_H
#define TOWER_H

#include <stack.h>

typedef struct {
    stack a, b, c;
} tower;

void tower_create   (tower *t, int size);
void tower_destroy  (tower *t);

void tower_move     (stack *s, stack *t);

#endif
