#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "image.h"
#include "block.h"
#include "free.h"

#define BLOCK_SIZE 4096

// reads block data to buffer. returns pointer to buffer
unsigned char *bread(int block_num, unsigned char *block){

    int offset = BLOCK_SIZE * block_num;

    lseek(image_fd, offset, SEEK_SET);

    read(image_fd, block, BLOCK_SIZE);

    return block;
}

// writes to block
void bwrite(int block_num, unsigned char *block){
    int offset = BLOCK_SIZE * block_num;

    lseek(image_fd, offset, SEEK_SET);

    write(image_fd, block, BLOCK_SIZE);
}

//allocate a previously-free data block from the block map.
int alloc(void){
    unsigned char block[4096];

    unsigned char *inode_block = bread(2, block);

    int free_bit = find_free(inode_block);

    if (free_bit == -1){
        return -1;
    }

    set_free(inode_block, free_bit, 1);

    bwrite(2, inode_block);

    return free_bit;
  
}