#ifndef x64ID_FUNCTION_LENGTH_H
#define x64ID_FUNCTION_LENGTH_H

#include <stdio.h>

#include "../vector.h"
#include "../queue.h"
#include "../x64id.h"

typedef struct {
    vector *pVisited;
    int length;
} functionInfo,*pFunctionInfo;

pFunctionInfo getFunctionLength(char *buffer, enum supported_architecture arch);

#endif //x64ID_FUNCTION_LENGTH_H
