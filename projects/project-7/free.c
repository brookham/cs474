#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "image.h"
#include "block.h"
#include "free.h"

int find_low_clear_bit(unsigned char x)
{
    for (int i = 0; i < 8; i++)
        if (!(x & (1 << i)))
            return i;
    
    return -1;
}

void set_free(unsigned char *block, int num, int set){
    int byte_num = num / 8;
    int bit_num = num % 8;

    unsigned char index = block[byte_num];

    if (set > 0){
        block[byte_num] = index | 1 << bit_num;
    } else {
        block[byte_num] = index & ~ (1 << bit_num);
    }

}

int find_free(unsigned char *block){

    for (int i = 0; i < 4096; i++){
        int block_num = block[i];
        int bit = find_low_clear_bit(block_num);

        if (bit != -1){
            return i * 8 + bit;
        }
    }
    return -1;

}