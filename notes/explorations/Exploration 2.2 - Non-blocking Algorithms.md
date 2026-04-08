1. What is the core defining property of a non-blocking algorithm? What can it guarantee about threads that fail or block?

that the failure of one thread cannot cause the failure of another thread. this guarantees that if a thread fails or blocks, it will not effect another thread.

2. Explain the difference between _lock-free_ and _wait-free_ guarantees. Which is stronger, and why?

wait free is stronger because it guarantees systemwide throughput with starvation freedom while  lock freedom only guarantees systemwide throughput.

3. Why are non-blocking algorithms inherently safe to use in interrupt handlers, while mutex-protected data structures are not?

because mutex protected data can be interrupted because the thread that is being interrupted may be the one holding the lock, while this cannot be the case with non-blocking algorithms

4. What is the role of Compare-and-Swap (CAS) in non-blocking algorithms? Why does hardware support for this primitive matter?

CAS supplies non-blocking with atomic read-modify-write primatives. hardware support matters for this to ensure that the read-modify-write sequence happens in the correct order and automatically

5. A lock-free algorithm can still lead to individual thread starvation. Explain how this is possible given that lock-free guarantees system-wide progress.

because the progress doesn't have to be the same for all processes so a long process can make more progress than another

6. Why must non-blocking algorithms account for memory ordering, and what tools do C11/C++11 provide to address this?

to ensure that compiler reordering does not mess up synchronization, atomic variables prevent this in C/C++

7. Describe the trade-off between coarse-grained and fine-grained locking. How do non-blocking algorithms sidestep this trade-off?

coarse grained locking has less overhead but van reduce parallelism, while fine grained locking has more overhead but can be more parallel. these tradeoffs. these downsides are side stepped by not having to block so overhead is reduced and bugs are diminished.

8. Some obstruction-free algorithms use a pair of "consistency markers." Describe how this technique works and what problem it solves.

a marker is loaded with data into a buffer, and then compared to check if the markers are identical or to see if they have been interrupted by another process. this solves the issues of data corruption with obstruction free algorithms

9. The article notes that all algorithms can theoretically be implemented wait-free, yet wait-free designs were rare in practice until around 2011. What are two reasons that explain this historical scarcity?

it wasn't realized how good it could be with CAS, and the lock free queue wasn't common place either