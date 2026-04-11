1. In early systems, there was essentially no memory abstraction; the OS and one running program simply shared physical memory directly. What specific problem arose when systems moved to _multiprogramming_, and why did it make memory management suddenly much harder?

the main problem that arose was now there was the danger of different processes accessing the memory than another process was using. this made it much harder because OS devs had to come up with a way to stop this from happening while keeping the run time short and effective.

2. One early approach to time sharing was to save an entire process's memory to disk when switching to another process. Why was this approach abandoned, and what did systems do instead?

this approach was abandoned because transferring entire contents of memory was super slow. so instead the process is left in memory while switching between them.

3. In your own words, define an _address space_. What are the three primary components the chapter identifies as living inside a process's address space, and what is each used for?

its what is virtualized to a process for it to use as its own private memory

4. In the canonical address space layout, the heap and stack are placed at _opposite ends_ of the address space. Explain why this placement is intentional and what problem it solves.

this makes it so they can both grow or shrink as memory needs change and they have the space to do so.

5. If you run a C program and print out the address of a local variable with `printf("%p", &x)`, is that address virtual or physical? Explain what happens between that address and actual hardware memory.

that would be the virtual address. the OS maps that address to the actual physical location

6. What does it mean for the OS to _virtualize memory_? Specifically, from the running program's perspective, what does it believe about its own memory, and what is actually true?

it means that the program thinks it has a specific continuous address space which in reality is not the case physically where it would be some other free location off in the hardware

7. Explain the _principle of isolation_. How does memory isolation relate to OS reliability, and what is a _microkernel_ design's approach to taking isolation even further?

this means that processes should not effect each other if something goes wrong (they should act independently). the microkernel allows pieces of the OS to be walled off from each other so the processes cant effect each other

8. Consider the claim: _"Code is placed at the top of the address space because it is static."_ What does "static" mean in this context, and why does being static make code easier to place in memory than the heap or stack?

static in this context means that it will not change throughout the processes run. so you can know that it wont grow or shrink like a heap or stack while the process is running.