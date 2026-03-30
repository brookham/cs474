## Schedulers
- figure out which process to run next.
	- could run the process with highest priority
	- the low priority one might be running now
		- the high priority one cant start
		- have small time slices to avoid this
	- the high priority one might _starve_ the low priority one

	- what if all the processes are equal priority?
		- least-recently run runs next
		- _round Robin_  

## Project 1: Round Robin