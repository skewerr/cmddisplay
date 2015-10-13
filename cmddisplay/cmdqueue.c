#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cmdqueue.h"

#define true    1
#define false   0


/* Operation functions. */


void
v_queue_create (v_queue *q, int size)
{
    q->size     = size;
    q->length   = 0;
    q->start    = 0;
    q->end      = 0;
    q->content  = (pos*) malloc(size * sizeof(pos));
}


void
v_queue_resize (v_queue *q, int size)
{
    v_queue r;
    v_queue_create(&r, size);

    while (!v_queue_is_empty(q) && !v_queue_is_full(&r))
        v_queue_enqueue(&r, v_queue_dequeue(q));

    v_queue_destroy(q);

    *q = r;
}


void
v_queue_enqueue (v_queue *q, pos data)
{
    if (v_queue_is_full(q))
    {
        printf("ERROR: Full queue. (enqueue %d,%d)\n", data.x, data.y);
        return;
    }

    q->content[q->end] = data;
    q->end = ++q->end % q->size;
    q->length++;
}


pos
v_queue_dequeue (v_queue *q)
{
    if (v_queue_is_empty(q))
    {
        printf("ERROR: Empty queue. (dequeue)\n");
        return position(0,0);
    }

    pos e = v_queue_start(q); q->length--;
    q->start = ++q->start % q->size;
    return e;
}


void
v_queue_destroy (v_queue *q)
{
    free(q->content);
}


void
v_queue_empty (v_queue *q)
{
    while (!v_queue_is_empty(q))
        v_queue_dequeue(q);
}


void
v_queue_fill (v_queue *q)
{
    static int seeded = false;

    if (!seeded)
    {
        srand(time(NULL));
        seeded = true;
    }

    while (!v_queue_is_full(q))
    {
        pos p;
        p.x = rand() % 100;
        p.y = rand() % 100;
        v_queue_enqueue(q, p);
    }
}


void
v_queue_invert (v_queue *q)
{
    if (v_queue_is_empty(q))
        return;

    pos c = v_queue_dequeue(q);
    v_queue_invert(q);
    v_queue_enqueue(q, c);
}


void
v_queue_copy (v_queue *q, v_queue *r)
{
    int c;

    v_queue_destroy(q);
    v_queue_create(q, r->size);

    for (c = 0; c < r->length; c++)
    {
        pos e = v_queue_dequeue(r);
        v_queue_enqueue(q, e);
        v_queue_enqueue(r, e);
    }
}


void
v_queue_join (v_queue *q, v_queue *r)
{
    int c;

    if (q->size < q->length + r->length)
        v_queue_resize(q, q->length + r->length);

    for (c = 0; c < r->length; c++)
    {
        pos e = v_queue_dequeue(r);
        v_queue_enqueue(q, e);
        v_queue_enqueue(r, e);
    }
}


/* Verification functions. */


int
v_queue_is_empty (v_queue *q)
{
    return !(q->length);
}


int
v_queue_is_full (v_queue *q)
{
    return q->length == q->size;
}


/* Other functions. */


pos
v_queue_start (v_queue *q)
{
    if (v_queue_is_empty(q))
    {
        printf("ERROR: Empty queue. (start)\n");
        return position(0,0);
    }

    return q->content[q->start];
}


int
v_queue_size (v_queue *q)
{
    return q->size;
}


int
v_queue_length (v_queue *q)
{
    return q->length;
}


void
v_queue_print (v_queue *q)
{
    int c;

    for (c = 0; c < q->length; c++)
    {
        printf(
            "%d,%d -> ",
            v_queue_start(q).x,
            v_queue_start(q).y
        );
        v_queue_enqueue(q, v_queue_dequeue(q));
    }

    printf("End of queue.\n");
}


pos
position (double x, double y)
{
    pos p;
    p.x = x; p.y = y;
    return p;
}
