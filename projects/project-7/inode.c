#include <stdio.h>
#include "block.h"
#include "free.h"

//allocate a previously-free inode in the inode map
int ialloc(void){
    unsigned char block[4096];

    unsigned char *inode_block = bread(1, block);

    int free_bit = find_free(inode_block);

    if (free_bit == -1){
        return -1;
    }

    set_free(inode_block, free_bit, 1);

    bwrite(1, inode_block);

    return free_bit;

}