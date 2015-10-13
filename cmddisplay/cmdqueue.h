#ifndef CMDQUEUE_H
#define CMDQUEUE_H

typedef struct {
    double x, y;
} pos;

typedef struct {
    int start, end;
    int size, length;
    pos *content;
} v_queue;

void v_queue_create   (v_queue *q, int size);
void v_queue_resize   (v_queue *q, int size);
void v_queue_enqueue  (v_queue *q, pos data);
pos  v_queue_dequeue  (v_queue *q);

void v_queue_copy     (v_queue *q, v_queue *r);
void v_queue_join     (v_queue *q, v_queue *r);
void v_queue_destroy  (v_queue *q);
void v_queue_invert   (v_queue *q);
void v_queue_empty    (v_queue *q);
void v_queue_fill     (v_queue *q);

pos  v_queue_start    (v_queue *q);
int  v_queue_size     (v_queue *q);
int  v_queue_length   (v_queue *q);

int  v_queue_is_empty (v_queue *q);
int  v_queue_is_full  (v_queue *q);

pos  position         (double x, double y);

#endif
