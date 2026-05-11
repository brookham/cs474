#include <stdio.h>

#define BITS_PER_BYTE 8

unsigned char bitmap[4096];

void print_byte(unsigned char b)
{
    if (b <= 1)
        printf("%d", b);

    else {
        print_byte(b >> 1);
        printf("%d", b & 1);
    }
}

void print_byte_n(unsigned char b)
{
    print_byte(b);
    putchar('\n');
}

int get_bit(int index)
{
    unsigned char byte = index/8;

    int val = bitmap[byte];

    unsigned char offset = index%8;

    int bit = val >> offset;

    bit = bit & 0b00000001;

    return bit;

}

void set_bit(int index, int value)
{
    unsigned char byte = index/8;

    int val = bitmap[byte];

    unsigned char offset = index%8;

    if (value > 0){
        bitmap[byte] = val | 1 << offset;
    } else {
        bitmap[byte] = val & ~(1 << offset);
    }   
    
}

int main(void)
{
    set_bit(0,1);
    set_bit(2,1);
    set_bit(3,1);
    set_bit(4,1);
    set_bit(7,1);
    set_bit(8,1);

    print_byte_n(bitmap[0]);
    print_byte_n(bitmap[1]);

    for (int i = 0; i <= 9; i++) {
        printf("%d: %d\n", i, get_bit(i));
    }
}