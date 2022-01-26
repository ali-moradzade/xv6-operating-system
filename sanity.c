#include "types.h"
#include "user.h"

#define PROC_COUNT 5       // number of processes
#define PRINT_COUNT 5      // number of prints for each process

int main(int argc, char *argv[]) {

    int policy = 0; // Default: 0
    int i, j;		                                                                // temp variables
	int pid, waiting_time, running_time, sleeping_time, priority, times[PROC_COUNT][3];		// processes variables

    for (i = 0; i < PROC_COUNT; i++)
		for (j = 0; j < 3; j++)
			times[i][j] = 0;


    // Select CPU scheduling policy - Default: 0
    if (argc == 2)
        policy = atoi(argv[1]);        

    switch (policy) {            
        case 0:
            printf(1, "+ Policy: None selected. Default: 0 - Round-Robin\n");            
            break;
        case 1:
            printf(1, "+ Policy: 1 - Non-preemptive priority\n"); 
            break;
        case 2:
            printf(1, "+ Policy: 2 - SML\n");
            break;
        case 3:
            printf(1, "+ Policy: 3 - DML\n");
            break;
    }
    change_policy(policy); // Set policy


	// create child processes and assign tasks to them
	for (i = 0; i < PROC_COUNT; i++) {
		pid = fork();
		
		// use only chile processes, consume CPU time and exit
		if (pid == 0) {

            // Policy: Priority
            if (policy == 1) {
                // priority = (i / GROUP_COUNT) + 1;
                if (i % 2 == 0)
                    priority = 2;
                else
                    priority = 1;
                set_prio(priority);
                // printf(1, "* MODIFY process(%d) - priority %d.\n", getpid(), priority);
                // yield();                // Skip one round to apply priority lvl
            }            
            for (int j = 0; j < PRINT_COUNT; j++) {
			    // printf(1, "* PID %d(%d) : %d\n", getpid(), priority, j);
                // sleep(10);
                work(getpid(), priority, j);
            }
			exit();
		}
		continue;	// keep father busy spawning children
	}

	// Calculate timing of each process
    sleep(100);
    printf(1, "\n+ Individual Times\n");
	for (i = 0; i < PROC_COUNT; i++) {

        // wait for the process to exit, then return properties
		pid = wait2(&waiting_time, &running_time, &sleeping_time, &priority);
        
        times[i][0] += sleeping_time;       // sleeping time
        times[i][1] += waiting_time;        // waiting time
        times[i][2] += running_time;        // running time

        printf(1, "- PID: %d)\tpriority: %d,\twaiting: %d,\trunning: %d,\tsleeping: %d,\tturnaround: %d\n", pid, priority, waiting_time, running_time, sleeping_time, waiting_time + running_time + sleeping_time);        
	}

    // Calculate average of each timing
    sleep(100);
    int avg_times[3];
    for (j = 0; j < 3; j++) {
	    for (i = 0; i < PROC_COUNT; i++)
            avg_times[j] += times[i][j];

        avg_times[j] /= PROC_COUNT;      // average
    }
    printf(1, "\n+ Average Times\n- Waiting Time: %d,\tRunning Time: %d,\tSleeping Time: %d,\tTurnaround Time: %d\n\n", avg_times[1], avg_times[2], avg_times[0], avg_times[1] + avg_times[2]);
	exit();
}