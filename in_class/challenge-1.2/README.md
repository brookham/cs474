1. Compute the response time and turnaround time when running three jobs of length 200 with the SJF and FIFO schedulers.

`python scheduler.py -l 200,200,200 -p SJF`
Try to predict the times, then run again adding the -c switch to check your answer.

job 0 response = 0 turnaround = 200
job 1 response = 200 turnaround = 400
job 2 response = 400 turnaround = 600

2. Now do the same but with jobs of different lengths: 100, 200, and 300.

job 0 response = 0 turnaround = 100
job 1 response = 100 turnaround = 300
job 2 response = 300 turnaround = 600

3. Now do the same, but also with the RR scheduler and a time-slice of 1.

job 0 response = 0 turnaround = 298
job 1 response = 1 turnaround = 499
job 2 response = 2 turnaround = 600

4. For what types of workloads does SJF deliver the same turnaround times as FIFO?

when the jobs are qued in the SJF order

5. For what types of workloads and quantum lengths does SJF deliver the same response times as RR?

when the job run time is set to the time intervals of RR

6. What happens to response time with SJF as job lengths increase? Can you use the simulator to demonstrate the trend?

it gets longer and longer

7. What happens to response time with RR as quantum lengths increase? Can you write an equation that gives the worst-case response time, given N jobs? Hint: run the simulation a number of times with jobs of the same length and a variety of quanta and see if you can find the pattern. (Or consider: where does a job have to be to have to wait the longest?)

response = N - 1