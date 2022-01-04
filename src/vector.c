/*
 * Dynamic array
 *
 */

#include "vector.h"

vector* vector_init()
{
    vector *v = calloc(1, sizeof(vector));
    v->vect = calloc(VECTOR_INIT, sizeof(uint32_t));
    v->size = VECTOR_INIT;
    v->tos = 0;

    return v;
}

void vector_push_back(vector *v, uint32_t value)
{
    if(v->tos == v->size)
    {
        v->size <<= 1;
        v->vect = realloc(v->vect, sizeof(uint32_t)*v->size);
    }
    v->vect[v->tos++] = value;
}

int vector_find(vector *v, uint32_t value)
{
    for(int i=0; i < v->tos; i++)
        if(v->vect[i] == value)
            return 1;
    return 0;
}

void vector_free(vector *v)
{
    if(v)
    {
        if (v->vect)
            free(v->vect);
        free(v);
    }
}