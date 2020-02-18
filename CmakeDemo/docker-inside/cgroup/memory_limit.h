//
// Created by peter on 2020/2/18.
//

#ifndef CMAKEDEMO_MEMORY_LIMIT_H
#define CMAKEDEMO_MEMORY_LIMIT_H

#include <malloc.h>
#include <string.h>
#include <unistd.h>

void test()
{
    int size = 0;
    int chunk_size = 4 * 128;
    int n = 128;

    while (1)
    {
        int *p = (int*)malloc(n * sizeof(int));
        if (p == NULL)
        {
            printf("out of memory!!\n");
            break;
        }
        memset(p, 1, chunk_size);
        size += chunk_size;
        printf("[%d] - memory is allocated [%8d] bytes \n", getpid(), size);
        sleep(1);
    }
}

#endif //CMAKEDEMO_MEMORY_LIMIT_H
