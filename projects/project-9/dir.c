#include <stdio.h>
#include "dir.h"
#include "inode.h"
#include <stdlib.h>


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