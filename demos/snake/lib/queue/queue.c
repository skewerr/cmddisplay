#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "queue.h"

#define true    1
#define false   0


/* Operation functions. */


void
queue_create (queue *q, int size)
{
    q->size     = size;
    q->length   = 0;
    q->start    = 0;
    q->end      = 0;
    q->content  = (pos*) malloc(size * sizeof(pos));
}


void
queue_resize (queue *q, int size)
{
    queue r;
    queue_create(&r, size);

    while (!queue_is_empty(q) && !queue_is_full(&r))
        queue_enqueue(&r, queue_dequeue(q));

    queue_destroy(q);

    *q = r;
}


void
queue_enqueue (queue *q, pos data)
{
    if (queue_is_full(q))
    {
        printf("ERROR: Full queue. (enqueue %d,%d)\n", data.x, data.y);
        return;
    }

    q->content[q->end] = data;
    q->end = ++q->end % q->size;
    q->length++;
}


pos
queue_dequeue (queue *q)
{
    if (queue_is_empty(q))
    {
        printf("ERROR: Empty queue. (dequeue)\n");
        return position(0,0);
    }

    pos e = queue_start(q); q->length--;
    q->start = ++q->start % q->size;
    return e;
}


void
queue_destroy (queue *q)
{
    free(q->content);
}


void
queue_empty (queue *q)
{
    while (!queue_is_empty(q))
        queue_dequeue(q);
}


void
queue_fill (queue *q)
{
    static bool seeded = false;

    if (!seeded)
    {
        srand(time(NULL));
        seeded = true;
    }

    while (!queue_is_full(q))
    {
        pos p;
        p.x = rand() % 100;
        p.y = rand() % 100;
        queue_enqueue(q, p);
    }
}


void
queue_invert (queue *q)
{
    if (queue_is_empty(q))
        return;

    pos c = queue_dequeue(q);
    queue_invert(q);
    queue_enqueue(q, c);
}


void
queue_copy (queue *q, queue *r)
{
    int c;

    queue_destroy(q);
    queue_create(q, r->size);

    for (c = 0; c < r->length; c++)
    {
        pos e = queue_dequeue(r);
        queue_enqueue(q, e);
        queue_enqueue(r, e);
    }
}


void
queue_join (queue *q, queue *r)
{
    int c;

    if (q->size < q->length + r->length)
        queue_resize(q, q->length + r->length);

    for (c = 0; c < r->length; c++)
    {
        pos e = queue_dequeue(r);
        queue_enqueue(q, e);
        queue_enqueue(r, e);
    }
}


/* Verification functions. */


int
queue_is_empty (queue *q)
{
    return !(q->length);
}


int
queue_is_full (queue *q)
{
    return q->length == q->size;
}


/* Other functions. */


pos
queue_start (queue *q)
{
    if (queue_is_empty(q))
    {
        printf("ERROR: Empty queue. (start)\n");
        return position(0,0);
    }

    return q->content[q->start];
}


int
queue_size (queue *q)
{
    return q->size;
}


int
queue_length (queue *q)
{
    return q->length;
}


void
queue_print (queue *q)
{
    int c;

    for (c = 0; c < q->length; c++)
    {
        printf(
            "%d,%d -> ",
            queue_start(q).x,
            queue_start(q).y
        );
        queue_enqueue(q, queue_dequeue(q));
    }

    printf("End of queue.\n");
}


pos
position (int x, int y)
{
    pos p;
    p.x = x; p.y = y;
    return p;
}
