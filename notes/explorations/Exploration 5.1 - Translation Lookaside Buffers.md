- What is the purpose of the protection bits on the TLB?

they determine the permissions for a page and how it can be accessed

- Since the mappings in the page table for one process are different from those for another, what happens to the TLB during a context switch? What are some options?

the TLB has the virtual-to-physical mapping for a process so when the process switches it has to somehow make sure the new process does not use the mapping fro the old process. some strategies of doing this are to flush the TLB on context switches, or you could add hardware support to reduce overhead like ASID

- Why would two different virtual page numbers (VPNs) in two different processes point to the same physical frame number (PFN)?

this could happen when two processes share a page

- What happens when the TLB is full and we have to put still more things in it?

it has to replace an old one

- The book poses the question of what happens when you have more than 256 processes running at a time on a MIPS R4000 processor (i.e. every possible ASID is used and you need more). What options might the OS have to handle this?

you could flish the tlb and start from scratch, or share asids