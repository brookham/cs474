#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

const int SIZE=1024;  // bytes

struct firework {
    int shell_caliber;
    float lift_charge;
    float burst_charge;
    int fuse_delay_ms;
};

int main(void)
{
    // Allocate some space from the OS
    void *heap = mmap(NULL, SIZE, PROT_READ|PROT_WRITE,
                      MAP_ANON|MAP_PRIVATE, -1, 0);

    // Challenge: Store your favorite letter at the byte `heap` points
    // to, then print it with `%c` and also with `%d`.
    char *p = heap;
    *p = 'B';

    printf("%c at %d\n", *(char *)p, *p);

    // Challenge: Store a string at the byte `heap` points to, then
    // print it.
    strcpy((char *)heap, "hi there");

    printf("%s\n", (char *)heap);

    // Challenge: Store an integer at the byte `heap` points to, then
    // print it.
    int *i = heap;

    *i = 69;

    printf("%d\n", *i);

    // Challenge: Store a float right *after* the int you just stored.
    // Print them both.
    float *f = (float*)((char*)heap + sizeof(int));

    *f = 100;

    printf("%d, %f\n", *i, *f);

    // Challenge: Store a short (a smallish integer) at byte offset 512
    // in the `heap` area. Then print it with `%d`, along with the int
    // and float you already stored.
    int *small_int = (int*)((char*)heap + 512);

    *small_int = 4;
    printf("%d, %d, %f\n", *small_int, *i, *f);

    // Challenge: Store a struct firework at byte offset 48 in the
    // `heap` area. Make a `struct firework *` initialized to the right
    // position, then fill it with data (with the `->` operator). Then
    // print out the data, and also print out the int, float, and short
    // from above.
    struct firework *firework1 = (struct firework*)((char*)heap + 48);

    firework1->shell_caliber = 50;
    firework1->lift_charge = 20.4456;
    firework1->burst_charge = 56.78;
    firework1->fuse_delay_ms = 300;

    printf("shell caliber: %d, lift charge: %f, burst charge: %f, fuse delay: %d, small int: %d\n", firework1->shell_caliber, firework1->lift_charge, firework1->burst_charge, firework1->fuse_delay_ms, *small_int);

    // Challenge: Store a second struct firework directly after the
    // first one. Initialize and print.
    struct firework *firework2 = (struct firework*)((char*)heap + 48 + sizeof(*firework1));
    firework2->shell_caliber = 20;
    firework2->lift_charge = 10.11;
    firework2->burst_charge = 30.56;
    firework2->fuse_delay_ms = 100;

    printf("shell caliber: %d, lift charge: %f, burst charge: %f, fuse delay: %d\n", firework2->shell_caliber, firework2->lift_charge, firework2->burst_charge, firework2->fuse_delay_ms);
}