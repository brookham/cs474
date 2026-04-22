#include <stdio.h>
#include <stdlib.h>

int merge_nums(unsigned a, unsigned b)
{
    unsigned int merged;

    merged = a << 8;

    merged = merged | b;

    return merged;

}

int main(int argc, char * argv[]){

    if (argc <= 1){
        return 1;
    }

    int page = atoi(argv[1]);

    int offset = atoi(argv[2]);

    int addr = merge_nums(page, offset);

    printf("Page: %d, Offset: %d, Address: %d\n", page, offset, addr);

}