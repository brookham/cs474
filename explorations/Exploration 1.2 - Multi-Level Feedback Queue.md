- What is the advantage of the MLFQ over vanilla Round-Robin scheduling?
it minimizes response time but also optimizes turnaround time

- What happens to a job’s priority if it uses up its entire time slice at a given queue level?
it gets moved down a priority level

- What is the purpose of priority boosting in MLFQ, and how does it help prevent starvation?
to boost the priority of all jobs in a system so that jobs don't starve and that CPU bound jobs become interactive

- What are the ways that the MLFQ prevents _gaming_ of the scheduler?
reducing the priority of every job that uses up its time despite how much it has given up the CPU

- Why is it dangerous to have a scheduler that can be gamed?
because a process can issues an I/O before its allotment ends and stay at the same priority level for longer than it was originally supposed to

- What problem is solved by Rule 4, above?
gaming

- What problem is solved by Rule 5, above?
job starving

- Search online--what is the name of the scheduler that Linux uses? That OS X uses?
Linux: completely fair scheduler (CFS)
OS X: launchd
