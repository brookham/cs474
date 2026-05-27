#include <stdio.h>
#include <string.h>
#include "block.h"

#define BLOCK_SIZE 4096

void mkfs(void)
{

    unsigned char block[BLOCK_SIZE];
    memset(block, 0, BLOCK_SIZE);

    for (int i = 0; i < 7; i++)
    {
        if (i == 2)
        {
            continue;
        }

        bwrite(i, block);
    }

    for (int j = 0; j < 7; j++)
    {
        alloc();
    }
}