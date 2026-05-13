#define CTEST_ENABLE
#include "ctest.h"
#include "image.h"
#include "block.h"
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

int main(void) {
    image_open("test.img", 1);
    test_bread_bwrite();
    CTEST_RESULTS();
    image_close();
    CTEST_EXIT();
}