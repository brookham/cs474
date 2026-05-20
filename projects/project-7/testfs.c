#define CTEST_ENABLE
#include "ctest.h"
#include "image.h"
#include "block.h"
#include "free.h"
#include "inode.h"
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
    unsigned char block[4096];
    memset(block, 0, sizeof(block));

    // initialize inode/data bitmap blocks in the image as all-free.
    bwrite(1, block);
    bwrite(2, block);

    //allocate inode block in block map
    int inode_block_num = ialloc();
    CTEST_ASSERT(inode_block_num == 0, "first inode bit allocated");

    int free_data_num = alloc();
    CTEST_ASSERT(free_data_num == 0, "first data bit allocated");

}

int main(void) {
    image_open("test.img", 1);
    test_bread_bwrite();
    test_set_and_find_free();
    image_close();
    image_open("test.img", 1);
    test_alloc();
    CTEST_RESULTS();
    image_close();
    CTEST_EXIT();
}