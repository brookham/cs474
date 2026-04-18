- How did instructions on the VAX specify the segment?

using the explicit approach where you chop up the address space into segments based on the top few bits of the virtual address
  
- What advantages does the segmented memory scheme have over vanilla base/bound?

segmented memory is much less wasteful and makes it easier to run a program when the address space doesn't fit into memory

- What kinds of problems does fragmentation cause?

it primarily causes memory to be wasted in  a few different ways