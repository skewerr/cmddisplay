#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

typedef struct {
    int x, y;
} pos;

typedef struct {
    int start, end;
    int size, length;
    pos *content;
} queue;

void queue_create   (queue *q, int size);
void queue_resize   (queue *q, int size);
void queue_enqueue  (queue *q, pos data);
pos  queue_dequeue  (queue *q);

void queue_copy     (queue *q, queue *r);
void queue_join     (queue *q, queue *r);
void queue_destroy  (queue *q);
void queue_invert   (queue *q);
void queue_empty    (queue *q);
void queue_fill     (queue *q);

pos  queue_start    (queue *q);
int  queue_size     (queue *q);
int  queue_length   (queue *q);

bool queue_is_empty (queue *q);
bool queue_is_full  (queue *q);

pos position        (int x, int y);

#endif
