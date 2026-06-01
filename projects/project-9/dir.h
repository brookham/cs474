#ifndef DIR_H
#define DIR_H
#include "inode.h"

struct directory {
    struct inode *inode;
    unsigned int offset;
};

struct directory *directory_open(int inode_num);
int directory_get(struct directory *dir, struct directory_entry *ent);


#endif