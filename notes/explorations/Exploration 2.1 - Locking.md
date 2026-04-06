1. What is the key problem with a spinlock implementation that uses a plain load (read) followed by a store (write) without using atomics? Show how this can fail with two threads.

the main problem is that if the lock is not atomic than while one thread is reading, another thread that was spinning will be able to write while or before the other thread is able to read
   
2. `TestAndSet` returns the _old_ value and sets the new value to 1. Why is returning the old value essential to the correctness of the lock?
because the whole point is to test the value at the old pointer while setting the value at that location to a new value so it can be either locked or unlocked
   
3. A spinlock built on `TestAndSet` is _correct_ but has poor performance on a single-core processor. Explain why, and what the OS scheduler must do to make any progress at all.

because the CPU will have to spin every thread for the duration of the time slice before giving up the CPU to the next thread, so there are a bunch of waisted cycles
   
4. `CompareAndSwap(current, expected, new)` only writes if the `current` value equals `expected`. What capabilities does this buy you over test-and-set? (You might have to search online a bit.)

because test n set modifies the info at a memory location and returns the old value atomically, while compare and swap compares the contents at a memory location and modifies the contents only if they are the same atomically. so it is more precise and more conditions are checked while still being atomic and more or less doing the same thing
   
5. What is a _fetch-and-add_-based ticket lock, and how does it guarantee **fairness** in a way that a simple `TestAndSet` spinlock does not?

it is a lock that uses a turn based system in order to schedule access to critical sections, it makes the process more fair by guaranteeing that if a thread has a ticket, it will be scheduled at some point in the future, which is not guaranteed with `TestAndSet`

6. Explain the **yield** approach to reducing CPU waste in a spinlock. What problem does it solve?

this allows a thread to yield its CPU time to another thread which means instead of spinning to wait on a lock to be released, a thread can yield the CPU and allow the running thread to finish so CPU cycles are not wasted

7. Why does spinning in a lock loop not waste CPU cycles on a multiprocessor the same way it does on a uniprocessor? Under what multiprocessor condition does spinning actually become a reasonable strategy?

because one CPU can spin for the waiting threads, while another CPU can use its cycles for the running thread, it works really well when there are the same amount of threads as there are CPU's

8. A thread calls `lock()`, acquires it, and then gets preempted mid-critical-section. What happens to all other threads trying to acquire the same spinlock? What does this imply about spinlock suitability in preemptive vs. non-preemptive kernels?

the scheduler can then run every other thread, all of which will try to acquire the lock and waste a bunch of CPU cycles, that spin locks only work on uniprocessor systems when it has a preemptive scheduler but at the same time have a lot of overhead so are not very suitable

9. The "park/unpark" (Solaris) or `futex` (Linux) approach combines spinning with sleeping. Describe the **two-phase** strategy: when does a thread spin, and when does it sleep? What is the _wakeup race_ and how is it typically addressed?

in the first phase the caller spins while trying to acquire the lock, if it is not acquired the caller is put to sleep  and woken up when the lock becomes free later. the wakeup race happens when a thread is about to park thinking it should sleep and then a it switches to another thread, the the new thread releases the lock, the subsequent park can cause the first thread to sleep forever, this is solved by adding a third system call that announces when a thread is about to park which makes a park get returned instead of a sleep

10. The book notes that hardware support was _necessary_ to build correct locks. Explain why a purely software solution (like a naive flag variable in memory) fails on modern hardware, referencing at least one of: compiler reordering, CPU out-of-order execution, or cache coherence.

just using software doesn't work in a case like using a naive flag variable because modern compilers often use compiler reordering inn order to optimize the compiler which can mess up cause data to attempt to be modified within a critical section before a flag is read as locked or unlocked, which can cause so obvious mistakes