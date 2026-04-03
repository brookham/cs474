#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

#define MAX_PROG_LEN 10 // Max terms in a "program"
#define MAX_PROCS 10    // Max number of processes
#define QUANTUM 40      // Time quantum, ms
#define MAX_INSTRUCTIONS 12
#define MAX_PROGS 5

#define MIN(x, y) ((x) < (y) ? (x) : (y)) // Compute the minimum

struct process
{
    int pid;
    enum
    {
        ready,
        sleeping,
        exited
    } state;
    int sleep_time_remaining;
    int wake_time_remaining;
    int program_counter;
    int instructions[MAX_INSTRUCTIONS];
};

struct process table[MAX_PROCS];

void init_proc_table(void)
{
    for (int i = 0; i < MAX_PROCS; i++)
    {
        table[i].pid = i;
        table[i].state = ready;
        table[i].sleep_time_remaining = 0;
        table[i].wake_time_remaining = 0;
        table[i].program_counter = 0;
    }
}

void parse_command_line(int argc, char **argv)
{
    for (int i = 1; i < argc; i++)
    {
        char *process = argv[i];
        char *token;

        for (int i = 0; i < argc - 1; i++)
        {
            if ((token = strtok(process, ",")) != NULL)
                do
                {
                    table[i].instructions[table[i].program_counter] = atoi(token);
                    table[i].program_counter++;
                    
                } while ((token = strtok(NULL, ",")) != NULL);
        }
    }
}

int all_complete()
{
    for (int i = 0;i < MAX_PROCS; i++)
    {
        if (table[i].state != exited){
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
    int clock = 0;

    struct queue *q = queue_new();

    init_proc_table();

    parse_command_line(argc, argv);
    
    for (int i = 0; i < argc - 1; i++){
        queue_enqueue(q, &table[i]);
    }

    while(1)
    {
        if (all_complete() == 1){
            break;
        }

        if (queue_is_empty(q) == 0){
            clock += 40;
            int shortest_sleep = __INT_MAX__;

            for (int i = 0; i < argc - 1; i++){
                if (table[i].state == sleeping){
                    table[i].sleep_time_remaining -= 40;
                }
                

                if (table[i].sleep_time_remaining < shortest_sleep){
                    shortest_sleep = table[i].sleep_time_remaining;
                }
            }

            for (int i = 0; i < argc - 1; i++){
                table[i].sleep_time_remaining -= shortest_sleep;
                
            }
            clock += shortest_sleep;
            
        }
        printf("=== Clock %d ms ===\n", clock);

        for (int i = 0; i < argc - 1; i++){
            if (table[i].sleep_time_remaining <= 0 && table[i].state == sleeping){
                table[i].program_counter++;
                if (table[i].instructions[table[i].program_counter] == 0){
                    table[i].state = exited;
                    printf("PID %d Exiting\n", table[i].pid);
                }
                else {
                    table[i].state = ready;
                    table[i].wake_time_remaining = table[i].instructions[table[i].program_counter];

                    printf("PID %d: Waking up for %d ms\n", table[i].pid, table[i].wake_time_remaining);

                    queue_enqueue(q, &table[i]);
                }

                
            }
        }

        struct process *p = queue_dequeue(q);




        printf("PID %d: Running\n", p->pid);

        p->wake_time_remaining = table[p->pid].wake_time_remaining - MIN(QUANTUM, table[p->pid].wake_time_remaining);

        for (int i = 0; i < argc - 1; i++){
            if (table[i].state == sleeping){
                table[i].sleep_time_remaining -= p->wake_time_remaining;
            }

            if (p->wake_time_remaining > 0){
                queue_enqueue(q, &table[p->pid]);
            }else {
                p->program_counter ++;
                if (p->instructions[p->program_counter] == 0){
                    p->state = exited;
                    printf("PID %d: Exiting 2\n", p->pid);
                } else {
                    p->state = sleeping;
                    p->sleep_time_remaining = p->instructions[p->program_counter];
                    printf("PID %d: Sleeping for %d ms\n", p->sleep_time_remaining);
                }
            }
        }

        if (queue_is_empty(q)){
            continue;
        }


    }

    queue_free(q);
}
