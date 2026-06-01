#define CTEST_ENABLE
#include "ctest.h"
#include "image.h"
#include "block.h"
#include "free.h"
#include "inode.h"
#include "pack.h"
#include "dir.h"
#include <string.h>


void test_bread_bwrite(void) {
    unsigned char w_buf[4096];
    unsigned char r_buf[4096];

    // fill write buffer with a pattern
    memset(w_buf, 1, sizeof(w_buf));

    // write then read back block 2
    bwrite(2, w_buf);
    unsigned char *ret = bread(2, r_buf);

    // verify bread returned a buffer and contents match
    CTEST_ASSERT(ret != NULL, "bread returned NULL");
    CTEST_ASSERT(memcmp(r_buf, w_buf, sizeof(w_buf)) == 0, "read buffer equals written buffer");
}

void test_set_and_find_free(void){
    unsigned char block[4096];
    // start with all bits clear (0 == free)
    memset(block, 0, sizeof(block));

    // first free bit should be 0
    int free_bit = find_free(block);
    CTEST_ASSERT(free_bit == 0, "first free bit is 0");

    // mark bit 0 as used
    set_free(block, 0, 1);
    free_bit = find_free(block);
    CTEST_ASSERT(free_bit == 1, "next free bit is 1");

    // clear bit 1 and ensure it's found again
    set_free(block, 1, 0);
    free_bit = find_free(block);
    CTEST_ASSERT(free_bit == 1, "cleared bit becomes free again");
}

void test_alloc(void){
    struct inode *in = ialloc();
    CTEST_ASSERT(in != NULL, "ialloc returns an inode");
    CTEST_ASSERT(in->inode_num == 0, "ialloc returns inode number 0");

    struct inode *in2 = ialloc();
    CTEST_ASSERT(in2 != NULL, "ialloc returns a second inode");
    CTEST_ASSERT(in2->inode_num == 1, "ialloc returns inode number 1");

}

void test_incore_find_and_free_all(void){
    struct inode *free_inode = incore_find_free();
    CTEST_ASSERT(free_inode != NULL, "found free incore inode");
    free_inode->ref_count = 1;
    free_inode->inode_num = 42;

    struct inode *found_inode = incore_find(42);
    CTEST_ASSERT(found_inode == free_inode, "found same incore inode by number");

    incore_free_all();
    found_inode = incore_find(42);
    CTEST_ASSERT(found_inode == NULL, "no incore inodes found after free_all");
}

void test_read_write_inode(void){
    struct inode in = {0};
    in.size = 1234;
    in.owner_id = 5678;
    in.permissions = 0xAB;
    in.flags = 0xCD;
    in.link_count = 3;
    for (int i = 0; i < INODE_PTR_COUNT; i++){
        in.block_ptr[i] = i + 1;
    }

    // write to block 3 (first inode block)
    write_inode(&in, 0);

    // read back into a different struct
    struct inode in2 = {0};
    read_inode(&in2, 0);

    // verify fields match
    CTEST_ASSERT(in2.size == in.size, "inode size matches");
    CTEST_ASSERT(in2.owner_id == in.owner_id, "inode owner_id matches");
    CTEST_ASSERT(in2.permissions == in.permissions, "inode permissions match");
    CTEST_ASSERT(in2.flags == in.flags, "inode flags match");
    CTEST_ASSERT(in2.link_count == in.link_count, "inode link_count matches");
    for (int i = 0; i < INODE_PTR_COUNT; i++){
        CTEST_ASSERT(in2.block_ptr[i] == in.block_ptr[i], "inode block_ptr matches");
    }
}

void test_iget_iput(void){
    struct inode in = {0};
    in.inode_num = 42;
    in.ref_count = 0;

    // iget should find free incore inode and read from disk
    struct inode *iget_in = iget(in.inode_num);
    CTEST_ASSERT(iget_in != NULL, "iget returns an inode");
    CTEST_ASSERT(iget_in->inode_num == 42, "iget reads correct inode number");
    CTEST_ASSERT(iget_in->ref_count == 1, "iget sets ref_count to 1");

    // iput should decrement ref_count
    iput(iget_in);
    CTEST_ASSERT(iget_in->ref_count == 0, "iput decrements ref_count");
}

void test_open_directory(void){
    struct directory *dir = directory_open(0);
    CTEST_ASSERT(dir != NULL, "directory_open returns a directory");
    CTEST_ASSERT(dir->inode != NULL, "directory has an inode");
    CTEST_ASSERT(dir->offset == 0, "directory offset starts at 0");
}

int main(void) {
    image_open("test.img", 1);
    test_bread_bwrite();
    test_set_and_find_free();
    test_open_directory();
    image_close();
    image_open("test.img", 1);
    test_alloc();
    test_incore_find_and_free_all();
    test_read_write_inode();
    test_iget_iput();
    CTEST_RESULTS();
    image_close();
    CTEST_EXIT();
}