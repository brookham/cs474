#include <stdio.h>
#include <string.h>
#include "block.h"
#include "inode.h"
#include "pack.h"

#define BLOCK_SIZE 4096
#define ENTRY_SIZE 32
#define INODE_NUM_LEN 2
#define FILE_NAME_LEN 16
#define RESERVED_LEN 14

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

    //Creating root directory
    struct inode *root_in = ialloc();
    int root_block_num = alloc();

    root_in->flags = 2;
    root_in->size = ENTRY_SIZE * 2;
    root_in->block_ptr[0] = root_block_num;

    unsigned char root_block[BLOCK_SIZE];

    unsigned char *arr = bread(root_block_num, root_block);

    write_u16(arr + 0, root_in->inode_num);
    strcpy((char *)(arr + INODE_NUM_LEN), ".");

    write_u16(arr + ENTRY_SIZE, root_in->inode_num);
    strcpy((char *)(arr + ENTRY_SIZE + INODE_NUM_LEN), "..");

    bwrite(root_block_num, root_block);

    iput(root_in);
}