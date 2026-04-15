1. The chapter distinguishes between external and internal fragmentation. Define each, and explain why a user-level `malloc` implementation is primarily concerned with external fragmentation rather than internal.
    
2. The chapter states that a `malloc` library cannot compact free space the way an OS might compact physical memory under segmentation. Why not? What property of C programs makes this impossible?
    
3. Describe the splitting mechanism. Under what condition does an allocator perform a split, and what does the free list look like before and after the split occurs?
    
4. What problem does coalescing solve, and when does it occur? What happens to the free list if an allocator fails to coalesce after several frees?
    
5. The `free(ptr)` interface takes no size argument. How does the allocator know how many bytes to reclaim? Be specific about what information is stored and how it is located at runtime.
    
6. How is the free list itself stored? Why can't the allocator just call `malloc()` to allocate new free-list nodes, and what does it do instead?
    
7. Compare best fit and first fit in terms of fragmentation behavior and search cost. Under what circumstances might first fit produce results identical to worst fit?
    
8. What specific problem with first fit does the next fit strategy address, and how does it address it? What does next fit trade away to achieve this?