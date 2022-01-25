#include "types.h"
#include "user.h"

#define n 10

int main(int argc, char *argv[]) {

	printf(1, "Running sanity check for RoundRibin...");
    sleep(1);

	int i, j;		// variables
	int pid, retime, rutime, stime, sums[3][3];		// processes variables
	// for (i = 0; i < 3; i++)
	// 	for (j = 0; j < 3; j++)
	// 		sums[i][j] = 0;

	// create child processes and assign tasks to them
	for (i = 0; i < n; i++) {
		pid = fork();
		
		// only use child process for the simulation
		if (pid == 0) {
            
            for (int j = 0; j < 10; j++) {
			    printf(1, "PID\t%d : %d\n", getpid(), j);
                sleep(10);
            }
			exit();		// exit child process
		}
		continue;	// keep father busy spawning children
	}

	// // print results for indivisual children running tasks
	// for (i = 0; i < n; i++) {
	// 	pid = wait2(&retime, &rutime, &stime);
	// 	int res = (pid - 4) % 3; // correlates to j in the dispatching loop

	// 	switch(res) {
	// 		case 0: // CPU bound processes
	// 			// printf(1, "CPU-bound, pid: %d, ready: %d, running: %d, sleeping: %d, turnaround: %d\n", pid, retime, rutime, stime, retime + rutime + stime);
	// 			sums[0][0] += retime;
	// 			sums[0][1] += rutime;
	// 			sums[0][2] += stime;
	// 			break;
	// 		case 1: // short-tasked CPU bound processes
	// 			// printf(1, "CPU-S bound, pid: %d, ready: %d, running: %d, sleeping: %d, turnaround: %d\n", pid, retime, rutime, stime, retime + rutime + stime);
	// 			sums[1][0] += retime;
	// 			sums[1][1] += rutime;
	// 			sums[1][2] += stime;
	// 			break;
	// 		case 2: // I/O bound processes
	// 			// printf(1, "I/O bound, pid: %d, ready: %d, running: %d, sleeping: %d, turnaround: %d\n", pid, retime, rutime, stime, retime + rutime + stime);
	// 			sums[2][0] += retime;
	// 			sums[2][1] += rutime;
	// 			sums[2][2] += stime;
	// 			break;
	// 	}
	// }

	// // print results for average performance
	// for (i = 0; i < 3; i++)
	// 	for (j = 0; j < 3; j++)
	// 		sums[i][j] /= n;		// calculate average

	// printf(1, "\n\nCPU bound:\nAverage ready time: %d\nAverage running time: %d\nAverage sleeping time: %d\nAverage turnaround time: %d\n\n\n", sums[0][0], sums[0][1], sums[0][2], sums[0][0] + sums[0][1] + sums[0][2]);
	// printf(1, "CPU-S bound:\nAverage ready time: %d\nAverage running time: %d\nAverage sleeping time: %d\nAverage turnaround time: %d\n\n\n", sums[1][0], sums[1][1], sums[1][2], sums[1][0] + sums[1][1] + sums[1][2]);
	// printf(1, "I/O bound:\nAverage ready time: %d\nAverage running time: %d\nAverage sleeping time: %d\nAverage turnaround time: %d\n\n\n", sums[2][0], sums[2][1], sums[2][2], sums[2][0] + sums[2][1] + sums[2][2]);
	exit();
}