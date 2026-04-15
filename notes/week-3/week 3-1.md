## Memory Maps
```
------------------------- High Addresses (2^64-1)
Stack  (local variables, alloca())
-------------------------
     VV

   [avaliable memory]

     ^^
-------------------------
Heap   (dynamic memory, malloc(), mmap(), brk())
-------------------------
BSS    (preinitialized data)
-------------------------
Text   (program Code)
------------------------- Low Addresses (0)
```

## Virtual Addressing
- two kinds of addresses (index into memory of where a byte is)
	- virtual (what processes see)
	- physical (the actual RAM on your computer)

## Memory API
- `void *p = malloc(int size)`
- `free(void *p)`

```
char *s = malloc(128);

strcpy(s, "Hello!");
puts(s);

free(s);
```

## Addressing in C
- Pointer arithmetic
	- you can add or subtract to or from a pointer
	- this gets you a pointer to the next or previous thing in memory
	  ```c
	  int a[10] = {1, 2, 3, 4, 5};
	  int *p = a;
	  
	  printf("%d\n", *p); //1
	  printf("%d\n", *(p+1)); //2
	  
	  -----------------------------
	  int a[10] = "Hi There";
	  int *p = a;
	  
	  printf("%d\n", *p); // H
	  printf("%d\n", *(p+1)); // i
	  ```

- Casting
```c
char a[128];
char *p = a;

*p = 'H';

printf("%d\n" *p) // H

int i = 12;
int *ip = (int *)a;

*ip = i;
```