#ifndef MCA_FUNCTION_LENGTH_H
#define MCA_FUNCTION_LENGTH_H

#include <stdio.h>

#include "../vector.h"
#include "../queue.h"
#include "../mca.h"

typedef struct {
    vector *pVisited;
    int length;
} functionInfo,*pFunctionInfo;

pFunctionInfo getFunctionLength(char *buffer, enum supported_architecture arch);

#endif //MCA_FUNCTION_LENGTH_H
