#include <stdio.h>
#include <stdlib.h>

int get_high_8(unsigned a)
{
    unsigned int high_8;

    high_8 = a >> (8);

    return high_8;

}

int get_low_8(unsigned a)
{
    unsigned int low_8;

    low_8 = a & (0b0011111111);

    return low_8;

}

int main(int argc, char *argv[]){

    if (argc <= 1){
        return 1;
    }

    int addr = atoi(argv[1]);

    int page = get_high_8(addr);

    int offset = get_low_8(addr);

    printf("Address: %d, Page: %d, Offset: %d\n", addr, page, offset);



}

