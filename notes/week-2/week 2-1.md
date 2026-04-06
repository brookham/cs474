## Locking and the OS
- there are a lot of shared resources so you have to lock it when running multiple threads to avoid clashes

## A Naive Spinlock
```c
#include <stdio.h>

int locked = 0;

void lock(void)
{
	 while (locked) {};
	 
	 //------------- could get interupted here; multiple threads could hold lock
	 
	 locked = 1;
}

void unlock(void)
{
	locked = 0;
}

int main(void)
{
	lock();
	printf("hello");
	unlock();
}

```


## Test and Set
```c
#include <stdio.h>

atomic int locked = 0;

void lock(void)
{
	while(TAS(&locked, 1));
	
}

void unlock(void)
{
	locked = 0;
}

int main(void)
{
	lock();
	printf("hello");
	unlock();
}

```