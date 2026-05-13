#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "image.h"
#include "block.h"

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