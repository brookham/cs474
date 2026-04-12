1. A function allocates a local `int` on the stack and returns a pointer to it. What happens to that memory after the function returns, and why is the pointer now dangerous to use?

the memory is now deallocated, using this pointer is now dangerous because it can point to memory that is not what you think it is
    
2. Given the following code, what value does `sizeof(x)` print on a 64-bit machine, and why doesn't it print `40`?
    ```c
    int *x = malloc(10 * sizeof(int));
    printf("%d\n", sizeof(x));
    ```

8

3. Why is `malloc(strlen(s))` wrong when allocating space to copy a string, and what is the correct idiom? What specific memory error can result?

because it does not account for the end of line character.  `malloc(strlen(s + 1))` would be the correct way, doing it the other way can result in a buffer overflow.
    
4. A classmate says "every call to `malloc()` makes a system call into the OS." Is this accurate? Explain the relationship between `malloc()`, `free()`, and the underlying OS calls like `brk()`.

this is not accurate, because `malloc()` and `free()` are library calls not system calls, although `brk()` is an example of a system call.
    
5. You call `malloc()` correctly but never write to the allocated memory before reading it. The program runs without crashing. Does that mean the program is correct? What is the risk?

no this does not mean the program is correct, if you allocate the memory but do not write to it it will remain allocated and will still need to be freed
    
6. A short command-line utility leaks 50 bytes of heap memory and then exits. Is this a real problem? Now consider the same leak in a database server that runs for months. How does the severity differ, and why?

it is not a huge problem on a small scale but if it where to leak for months, it can cause you to run out of memory and you will need to restart.
    
7. What is a double free, and why does calling `free()` twice on the same pointer produce undefined behavior rather than a clean error? What makes this class of bug particularly hard to diagnose?

this causes undefined behavior because the memory allocation library gets confused and possible crash. this is hard to diagnose because of the confusion of the memory library and the inability to define the behavior.
    
8. Describe a scenario where freeing memory before you're done using it (a _dangling pointer_) could corrupt data in a program, rather than simply crashing it.

if you `free()` the memory and then `malloc()` again for something else. this can cause the memory to get recycled and written over
    
9. What does `calloc()` do differently from `malloc()`, and in what situation would you specifically prefer it? What common bug does it help prevent?

it both allocates and zeros the memory before returning

10. The chapter notes that even garbage-collected languages can have memory leaks. How is this possible if the GC automatically frees unreferenced memory? Give a brief example scenario.

if you still have a reference to something like a global variable will not get collected by the gc