#ifndef x64ID_QUEUE_H
#define x64ID_QUEUE_H

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define QUEUE_INIT  20

typedef struct {
    uint64_t*queue;
    int size;
    int tos;
} queue;

queue* queue_init();
void queue_enqueue(queue *q, uint64_t value);
uint64_t queue_dequeue(queue *q);
void queue_free(queue *q);
int queue_empty(queue *q);
int queue_find(queue *q, uint64_t value);
int queue_size(queue *q);

#endif //x64ID_QUEUE_H
