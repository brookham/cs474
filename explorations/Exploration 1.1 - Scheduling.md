 - What is the main goal of the scheduler?
   to figure out how to schedule jobs for execution
   
- What factors have to be considered when designing or selecting a scheduler?
  what metrics are being used to measure success, what is being assumed about each job when it is arriving to the scheduler
  
- What kind of wrench does I/O throw in the works for a scheduler?
  there are two different things happening when I/O happens which are CPU and disk so you have to keep track of both of them and try to maximize the performance on both even though they might be start/finish executing at different times
  
- What is turnaround time, and how is it calculated?
  time job completes - time job arrived in the system
  
- How does First-In, First-Out (FIFO) scheduling work, and what is the "convoy effect"?
  it works just like how it sounds, the first jobs are executed on a first come first serve basis, the convoy effect is when the smaller jobs arrive after a large job and a get stuck waiting for it to complete 
  
- Why does Shortest Job First (SJF) often achieve better average turnaround time than FIFO?
  because it ensures that the convoy effect doesn't take place (given all jobs arrive at the same time) so if job A takes 100 seconds and job B takes 10 seconds the average turnaround time would be 55 seconds instead of 105 seconds for FIFO
  
- What key assumption does Shortest Time-to-Completion First (STCF) make compared to SJF?
  SJF assumes that all jobs must runt o completion, STCF does not
  
- What is response time, and why is it especially important for interactive workloads?
  response time = jobs first run - time job arrived, this is very important in interactive workloads because it makes it so there is an almost immediate response from when you send a job to the scheduler to when it is ran
  
- How does Round Robin (RR) scheduling attempt to improve response time?
  it has everything run for a given amount of time no matter how big the job is so everything responds after a short amount of time
  
- How does the length of the time quantum in Round Robin affect performance and overhead?
  it can make the performance very bad if the time slice because it can cause short jobs to take a long time to finish as they have to wait for their turn again