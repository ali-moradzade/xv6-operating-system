#include "types.h"
#include "user.h"

#define PROC_COUNT 10       // number of processes
#define PRINT_COUNT 10      // number of prints for each process
#define GROUP_COUNT 5       // number of processes in each group

int main(int argc, char *argv[]) {

	printf(1, "Running sanity check for Priority...\n");
    sleep(100);

	int i, j;                                                            // temp variables
	int pid, waiting_time, running_time, sleeping_time, priority, times[PROC_COUNT][3];		// processes variables

    for (i = 0; i < PROC_COUNT; i++)
		for (j = 0; j < 3; j++)
			times[i][j] = 0;

	// create child processes and assign tasks to them
	for (i = 0; i < PROC_COUNT; i++) {
		pid = fork();        
		
		// use only chile processes, consume CPU time and exit
		if (pid == 0) {

			// Update priority based on group count
			// priority = (i / GROUP_COUNT) + 1;
			if (i % 2 == 0)
				priority = 1;
			else
				priority = 2;
			set_prio(priority);
			// printf(1, "PID %d - Priority %d\n", getpid(), priority);
			// yield();

            for (int j = 0; j < PRINT_COUNT; j++)
			    printf(1, "PID\t%d : %d\n", getpid(), j);
			exit();
		}
		continue;	// keep father busy spawning children
	}

	// print timing properties for each process
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

    // Calculate averages
    int avg_times[3];
    for (j = 0; j < 3; j++) {
	    for (i = 0; i < PROC_COUNT; i++)
            avg_times[j] += times[i][j];

        avg_times[j] /= PROC_COUNT;      // average
    }

    printf(1, "\n+ Average Times\n- Waiting Time: %d,\tRunning Time: %d,\tSleeping Time: %d,\tTurnaround Time: %d\n", avg_times[1], avg_times[2], avg_times[0], avg_times[1] + avg_times[2]);
	exit();
}