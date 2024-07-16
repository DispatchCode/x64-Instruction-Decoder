/*
 * Queue (FIFO)
 *
 */

#include "queue.h"

queue* queue_init()
{
    queue *q = calloc(1, sizeof(queue));
    q->queue = calloc(QUEUE_INIT, sizeof(uint64_t));
    q->size = QUEUE_INIT;
    q->tos = 0;

    return q;
}

void queue_enqueue(queue *q, uint64_t value)
{
    if(q->tos == q->size)
    {
        q->size <<= 1;
        q->queue = realloc(q->queue, sizeof(uint64_t)*q->size);
    }

    q->queue[q->tos++] = value;
}

uint64_t queue_dequeue(queue *q)
{
    uint64_t value = q->queue[0];
    q->tos--;
    memcpy(q->queue, q->queue+1, sizeof(uint64_t)*q->tos);
    return value;
}

int queue_empty(queue *q)
{
    return q->tos == 0;
}

int queue_size(queue *q) {
    return q->tos;
}

int queue_find(queue *q, uint64_t value)
{
    for(int i=0; i<q->tos; i++)
        if(q->queue[i] == value)
            return 1;
    return 0;
}

void queue_free(queue *q)
{
    if(q)
    {
        if (q->queue)
            free(q->queue);
        free(q);
    }
}