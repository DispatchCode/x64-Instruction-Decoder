#ifndef MCA_QUEUE_H
#define MCA_QUEUE_H

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define QUEUE_INIT  20

typedef struct {
    uint32_t *queue;
    int size;
    int tos;
} queue;

queue* queue_init();
void queue_enqueue(queue *q, uint32_t value);
uint32_t queue_dequeue(queue *q);
void queue_free(queue *q);
int queue_empty(queue *q);
int queue_find(queue *q, uint32_t value);

#endif //MCA_QUEUE_H
