#include <stdio.h>
#include <stdlib.h>

int global;


int main(){
    int p;
    int *x = malloc(sizeof(*x));
    
    printf("pointing to adddress %p\n", (void*)&p);

    printf("pointing to adddress %p\n", (void*)x);

    printf("pointing to adddress %p\n", (int*)&global);

    printf("pointing to adddress %p\n", (void*)main);


}