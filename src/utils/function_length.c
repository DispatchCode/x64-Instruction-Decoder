#include "function_length.h"


vector* instrFlowLength(char *pMemory, const enum supported_architecture arch)
{
    int bytes_len = 0;
    uint64_t addr = (uint64_t)pMemory;

    queue *future_paths = queue_init();
    vector *visited = vector_init();

    char *tmp_addr = pMemory;
    while(true)
    {
        struct instruction instr;
        x64id_decode(&instr, arch, tmp_addr, 0);
/*
        for (int i = 0; i < instr.length; i++) {
            printf("%X ", instr.instr[i]);
        }
        printf("\n");
*/
        if(instr.op == 0xc3 || instr.op == 0xCC) // RET or INT3
        {
            vector_push_back(visited, addr);
            if(queue_empty(future_paths))
            {
                queue_free(future_paths);
                return visited;
            }

            uint64_t next_addr = queue_dequeue(future_paths);
            tmp_addr = (char *)next_addr;
            addr = next_addr;
            continue;
        }

        if(vector_find(visited, addr))
        {
            if(queue_empty(future_paths))
            {
                queue_free(future_paths);
                return visited;
            }

            uint64_t next_addr = queue_dequeue(future_paths);
            tmp_addr = (char *)next_addr;
            addr = next_addr;
            continue;
        }

        vector_push_back(visited, addr);
        bytes_len += instr.length;
        addr += instr.length;
        tmp_addr += instr.length;

        if (instr.jcc_type == JCC_FAR || instr.jcc_type == JCC_SHORT)
        {
            if (!queue_find(future_paths, instr.label))
            {
                queue_enqueue(future_paths, instr.label);
            }
        }

        if (instr.jcc_type == JMP_FAR || instr.jcc_type == JMP_SHORT)
        {
            addr = instr.label;
            tmp_addr = (char *)addr;
        }
    }
}

int compare(const void * n1, const void * n2)
{
    return *(uint64_t*)n1 - *(uint64_t*)n2;
}

pFunctionInfo getFunctionLength(char *buffer, enum supported_architecture arch)
{
    pFunctionInfo f_info = calloc(1,sizeof(functionInfo));
    vector *visited = instrFlowLength(buffer, arch);

    qsort(visited->vect, visited->tos, sizeof(uint64_t), compare);

    uint64_t min = visited->vect[0];
    uint64_t max = visited->vect[visited->tos-1];

    f_info->pVisited = visited;
    f_info->length = (int)(max-min);

    return f_info;
}