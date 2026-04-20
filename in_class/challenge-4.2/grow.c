#include <stdio.h>
#include <stdlib.h>


int grow(int grows){

    if (grows <= 0){
        return 1;
    }

    int stack;
    int *heap = malloc(sizeof(*heap));

    printf("%d\n", grows);

    printf("pointing to adddress %p\n", (void*)&stack);
    printf("pointing to adddress %p\n", (void*)heap);

    return grow(grows - 1);

}

int main(){
    grow(5);
}