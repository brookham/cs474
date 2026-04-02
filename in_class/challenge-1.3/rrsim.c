#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

#define MAX_PROCS 10 // Max number of processes
#define QUANTUM 40 // Time quantum, ms
#define MIN(x,y) ((x)<(y)?(x):(y)) // Compute the minimum

int clock;

/**
 * Process information.
 */
struct process {
    int pid;
    int time_awake_remaining;
};

/**
 * The process table.
 */
struct process table[MAX_PROCS];

/**
 * Initialize the process table.
 */
void init_proc_table(void)
{
    for (int i = 0; i < MAX_PROCS; i++) {
        table[i].pid = i;
        table[i].time_awake_remaining = 0;
    }
}

/**
 * Parse the command line.
 */
void parse_command_line(int argc, char **argv)
{
    for (int i = 0; i < argc - 1; i++){
        table[i].time_awake_remaining = atoi(argv[i + 1]);
    }
}

int done(){
    for (int i = 0; i < MAX_PROCS; i ++){
        if (table[i].time_awake_remaining > 0){
            return 0;
        }
    }

    return 1;
}

/**
 * Main.
 */
int main(int argc, char **argv)
{
    struct queue *q = queue_new();

    init_proc_table();

    parse_command_line(argc, argv);

    for (int i = 0; i < argc - 1; i ++){
        queue_enqueue(q, table + i);
    }

    while(1){
        if (done()){
            exit(0);
        }
        struct process *p = queue_dequeue(q);

        printf("=== Clock %d ms ===\n", clock);
        printf("pid %d: Running\n", p->pid);
        
        int time_remaining = table[p->pid].time_awake_remaining - MIN(QUANTUM, table[p->pid].time_awake_remaining);
        p->time_awake_remaining = time_remaining;


        if (time_remaining > 40){
            printf("PID %d: Ran for 40 ms\n", p->pid);
            clock += 40;
        }

        if (time_remaining <= 40){
            printf("PID %d: Ran for %d ms\n", p->pid, time_remaining);
            clock += time_remaining;
        }
        if (time_remaining > 0){
            queue_enqueue(q, p);
        }

    }

    queue_free(q);
}
