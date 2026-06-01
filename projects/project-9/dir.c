#include <stdio.h>
#include "dir.h"
#include "inode.h"
#include "block.h"
#include "pack.h"
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 4096
#define INODE_NUM_SIZE 2
#define ENTRY_SIZE 32

struct directory *directory_open(int inode_num){
    struct inode *in = iget(inode_num);

    if (in == NULL){
        return NULL;
    }

    struct directory *dir = malloc(sizeof(struct directory));

    dir->inode = in;
    dir->offset = 0;

    return dir;
    
}

int directory_get(struct directory *dir, struct directory_entry *ent){

    int offset = dir->offset;

    if (offset >= (int)dir->inode->size){
        return -1;
    }

    int data_block_index = offset / BLOCK_SIZE;
    int data_block_num = dir->inode->block_ptr[data_block_index];

    unsigned char block[BLOCK_SIZE];

    unsigned char *arr = bread(data_block_num, block);

    int offset_in_block = offset % BLOCK_SIZE;

    ent->inode_num = read_u16(arr + offset_in_block);
    strcpy(ent->name, (char *)(arr + offset_in_block + INODE_NUM_SIZE));

    dir->offset += ENTRY_SIZE;

    return 0;
}

void directory_close(struct directory *d){
    struct inode *in = d->inode;
    iput(in);

    free(d);
}