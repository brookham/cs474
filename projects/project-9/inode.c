#include <stdio.h>
#include "block.h"
#include "free.h"
#include "inode.h"
#include "pack.h"

#define BLOCK_SIZE 4096
#define INODE_SIZE 64
#define INODE_FIRST_BLOCK 3

#define INODES_PER_BLOCK (BLOCK_SIZE / INODE_SIZE)

static struct inode incore[MAX_SYS_OPEN_FILES] = {0};

//allocate a previously-free inode in the inode map
struct inode *ialloc(void){
    unsigned char block[4096];

    unsigned char *inode_block = bread(1, block);
    int free_bit = find_free(inode_block);

    if (free_bit == -1){
        return NULL;
    }

    struct inode *in = iget(free_bit);
    if (in == NULL){
        return NULL;
    }

    set_free(inode_block, free_bit, 1);
    bwrite(1, inode_block);

    *in = (struct inode){0};
    in->ref_count = 1;
    in->inode_num = free_bit;

    write_inode(in, free_bit);
    return in;
}

struct inode *incore_find_free(void){
    for (int i = 0; i < MAX_SYS_OPEN_FILES; i++){
        if (incore[i].ref_count == 0){
            return &incore[i];
        }
    }
    return NULL;
}

struct inode *incore_find(unsigned int inode_num){
    for (int i = 0; i < MAX_SYS_OPEN_FILES; i++){
        if (incore[i].ref_count != 0 && incore[i].inode_num == inode_num){
            return &incore[i];
        }
    }
    return NULL;
}

void incore_free_all(void){
    for (int i = 0; i < MAX_SYS_OPEN_FILES; i++){
        incore[i].ref_count = 0;
    }
}

void read_inode(struct inode *in, int inode_num){
    int block_num = inode_num / INODES_PER_BLOCK + INODE_FIRST_BLOCK;
    int block_offset = inode_num % INODES_PER_BLOCK;
    int block_offset_bytes = block_offset * INODE_SIZE;

    unsigned char block[4096];

    unsigned char *arr = bread(block_num, block);

    struct inode read;

    read.size = read_u32(arr + block_offset_bytes);
    read.owner_id = read_u16(arr + block_offset_bytes + 4);
    read.permissions = read_u8(arr + block_offset_bytes + 6);
    read.flags = read_u8(arr + block_offset_bytes + 7);
    read.link_count = read_u8(arr + block_offset_bytes + 8);
    for (int i = 0; i < INODE_PTR_COUNT; i++){
        read.block_ptr[i] = read_u16(arr + block_offset_bytes + 10 + i*2);
    }

    *in = read;
}

void write_inode(struct inode *in, int inode_num){
    int block_num = inode_num / INODES_PER_BLOCK + INODE_FIRST_BLOCK;
    int block_offset = inode_num % INODES_PER_BLOCK;
    int block_offset_bytes = block_offset * INODE_SIZE;

    unsigned char block[4096];

    unsigned char *arr = bread(block_num, block);

    write_u32(arr + block_offset_bytes, in->size);
    write_u16(arr + block_offset_bytes + 4, in->owner_id);
    write_u8(arr + block_offset_bytes + 6, in->permissions);
    write_u8(arr + block_offset_bytes + 7, in->flags);
    write_u8(arr + block_offset_bytes + 8, in->link_count);
    for (int i = 0; i < INODE_PTR_COUNT; i++){
        write_u16(arr + block_offset_bytes + 10 + i*2, in->block_ptr[i]);
    }

    bwrite(block_num, arr);
}

struct inode *iget(int inode_num) {
    struct inode *found = incore_find(inode_num);
    if (found != NULL) {
        found->ref_count++;
        return found;
    }
    struct inode *free_in = incore_find_free();
    if (free_in == NULL) {
        return NULL;
    }
    read_inode(free_in, inode_num);
    free_in->ref_count = 1;
    free_in->inode_num = inode_num;
    return free_in;
}

void iput(struct inode *in){
    if (in->ref_count == 0){
        return;
    }
    in->ref_count--;
    write_inode(in, in->inode_num);
}