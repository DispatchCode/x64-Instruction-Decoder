#ifndef x64ID_VECTOR_H
#define x64ID_VECTOR_H

#include <stdlib.h>
#include <stdint.h>

#define VECTOR_INIT  20

typedef struct  {
    uint64_t*vect;
    int size;
    int tos;
} vector;

vector* vector_init();
void vector_push_back(vector *v, uint64_t value);
void vector_free(vector *v);
int vector_find(vector *v, uint64_t value);

#endif //x64ID_VECTOR_H
