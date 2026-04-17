1. The chapter distinguishes between external and internal fragmentation. Define each, and explain why a user-level `malloc` implementation is primarily concerned with external fragmentation rather than internal.

external fragmentation happens when free space is divided into different sizes internal fragmentation happens when a chunk of memory is distributed that is bigger and what was requested so it can be wasted.. user level malloc is concerned with external fragmentation because malloc attempts to virtualize memory using segmentation which can cause thr problems present in external fragmentation
    
2. The chapter states that a `malloc` library cannot compact free space the way an OS might compact physical memory under segmentation. Why not? What property of C programs makes this impossible?
   
because the memory region will be owned by the program and cant be moved to the library until the `free()` is called.
    
3. Describe the splitting mechanism. Under what condition does an allocator perform a split, and what does the free list look like before and after the split occurs?
   
splitting happens when a free chunk of memory is found and it is split into two, one for the requested segment and then the remaining portion. the list will look more or less the same, the address of the segment after the split will just point to a different location and be of a different size   
    
4. What problem does coalescing solve, and when does it occur? What happens to the free list if an allocator fails to coalesce after several frees?
   
coalescing gathers sequential segments of free space into one segment of free space. this occurs typically after a `free()` which makes it easier to find large enough free space when traversing the list. if it fails you can end up with fragmentation
    
5. The `free(ptr)` interface takes no size argument. How does the allocator know how many bytes to reclaim? Be specific about what information is stored and how it is located at runtime.
   
the malloc library determines the size of a memory region by having an allocator store this information in a header block in memory

6. How is the free list itself stored? Why can't the allocator just call `malloc()` to allocate new free-list nodes, and what does it do instead?

the free list is embedded in the free space itself. this is done because the malloc library cant allocate free nodes. but it can do it with normal lists.
    
7. Compare best fit and first fit in terms of fragmentation behavior and search cost. Under what circumstances might first fit produce results identical to worst fit?

best fit finds nodes that are as big or bigger than the requested size, and then returns the smallest of them, this makes the search take longer and is more exhaustive but ends up returning the best fit. while first fit just returns the one that fits that it finds first which is not always the optimal choice. the two could return the same thing if the best fit is the first fit
    
8. What specific problem with first fit does the next fit strategy address, and how does it address it? What does next fit trade away to achieve this?

next fit spreads the search of free space throughout the list instead of just at the front so that the front of the list does not get splintered. it trades a small bit of memory but having an extra pointer to achieve this