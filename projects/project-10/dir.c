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
#define ROOT_INODE_NUM 0
#define FILE_IS_DIR_FLAG 2

struct directory *directory_open(int inode_num)
{
    struct inode *in = iget(inode_num);

    if (in == NULL)
    {
        return NULL;
    }

    struct directory *dir = malloc(sizeof(struct directory));

    dir->inode = in;
    dir->offset = 0;

    return dir;
}

int directory_get(struct directory *dir, struct directory_entry *ent)
{

    int offset = dir->offset;

    if (offset >= (int)dir->inode->size)
    {
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

void directory_close(struct directory *d)
{
    struct inode *in = d->inode;
    iput(in);

    free(d);
}

struct inode *namei(char *path)
{
    if (strcmp(path, "/") == 0)
        return iget(ROOT_INODE_NUM);

    char *name = path + 1;

    struct directory *dir = directory_open(ROOT_INODE_NUM);
    if (dir == NULL)
        return NULL;

    struct directory_entry ent;
    while (directory_get(dir, &ent) != -1)
    {
        if (strcmp(ent.name, name) == 0)
        {
            directory_close(dir);
            return iget(ent.inode_num);
        }
    }

    directory_close(dir);
    return NULL;
}

char *get_dirname(const char *path, char *dirname)
{
    strcpy(dirname, path);

    char *p = strrchr(dirname, '/');

    if (p == NULL)
    {
        strcpy(dirname, ".");
        return dirname;
    }

    if (p == dirname) // Last slash is the root /
        *(p + 1) = '\0';

    else
        *p = '\0'; // Last slash is not the root /

    return dirname;
}

char *get_basename(const char *path, char *basename)
{
    if (strcmp(path, "/") == 0)
    {
        strcpy(basename, path);
        return basename;
    }

    const char *p = strrchr(path, '/');

    if (p == NULL)
        p = path; // No slash in name, start at beginning
    else
        p++; // Start just after slash

    strcpy(basename, p);

    return basename;
}

int directory_make(char *path)
{
    if (path[0] != '/')
        return -1;

    char parent_path[256];
    char name[16];
    get_dirname(path, parent_path);
    get_basename(path, name);

    if (strcmp(name, "/") == 0 || *name == '\0')
        return -1;

    struct inode *parent = namei(parent_path);
    if (parent == NULL)
        return -1;

    struct inode *new_in = ialloc();
    if (new_in == NULL)
    {
        iput(parent);
        return -1;
    }
    int new_block_num = alloc();

    unsigned char new_block[BLOCK_SIZE];
    memset(new_block, 0, BLOCK_SIZE);

    write_u16(new_block, new_in->inode_num);
    strcpy((char *)(new_block + INODE_NUM_SIZE), ".");

    write_u16(new_block + ENTRY_SIZE, parent->inode_num);
    strcpy((char *)(new_block + ENTRY_SIZE + INODE_NUM_SIZE), "..");

    new_in->flags = FILE_IS_DIR_FLAG;
    new_in->size = ENTRY_SIZE * 2;
    new_in->block_ptr[0] = new_block_num;

    bwrite(new_block_num, new_block);

    int block_index = parent->size / BLOCK_SIZE;
    int offset_in_block = parent->size % BLOCK_SIZE;
    int parent_block_num;
    unsigned char parent_block[BLOCK_SIZE];

    if (offset_in_block == 0)
    {
        parent_block_num = alloc();
        parent->block_ptr[block_index] = parent_block_num;
        memset(parent_block, 0, BLOCK_SIZE);
    }
    else
    {
        parent_block_num = parent->block_ptr[block_index];
        bread(parent_block_num, parent_block);
    }

    write_u16(parent_block + offset_in_block, new_in->inode_num);
    strcpy((char *)(parent_block + offset_in_block + INODE_NUM_SIZE), name);

    bwrite(parent_block_num, parent_block);

    parent->size += ENTRY_SIZE;

    iput(new_in);
    iput(parent);

    return 0;
}