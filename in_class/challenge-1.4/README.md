1. i think its gonna stay in each queue for 10 ms

2. 
  example 1: python3 ./mlfq.py -n 3 -j 1 -m 200 -M 0 -S 10 -a 10 -c
  example 2: python3 ./mlfq.py -l 0,200,0:100,20,0 -S 10 -c
  example 3: python3 ./mlfq.py -l 0,1200,0:50,150,1 -S -I -i 5 -c

3. python3 ./mlfq.py -l 0,200,0:0,200,0:0,200,0 -S -I -i 5 -c

4. python3 ./mlfq.py -l 0,100,0:10,100,9 -q 10 -I -S -i 1 -c

5. B = 200

6. this flag seems better when the workload is larger