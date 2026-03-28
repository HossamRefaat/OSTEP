#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sched.h>
#include <stdlib.h>

#define ITERATIONS 100000

//measure the cost of context switch
int main() {
    int pipe1[2], pipe2[2];
    pipe(pipe1);
    pipe(pipe2);

    pid_t pid = fork();

    // Bind both processes to same CPU (CPU 0)
    cpu_set_t set; // A list of CPUs the process is allowed to run on
    CPU_ZERO(&set); // This clears the set
    CPU_SET(0, &set); //This adds CPU 0 to the set
    sched_setaffinity(0, sizeof(set), &set); //Bind THIS process → to CPU 0 only

    char buf = 'x';

    if (pid == 0) {
        // Child process
        for (int i = 0; i < ITERATIONS; i++) {
            read(pipe1[0], &buf, 1);
            write(pipe2[1], &buf, 1);
        }
    } else {
        // Parent process
        struct timeval start, end;

        gettimeofday(&start, NULL);

        for (int i = 0; i < ITERATIONS; i++) {
            write(pipe1[1], &buf, 1);
            read(pipe2[0], &buf, 1);
        }

        gettimeofday(&end, NULL);

        long seconds = end.tv_sec - start.tv_sec;
        long micros = end.tv_usec - start.tv_usec;

        double total = seconds + micros * 1e-6;

        // Each iteration = 2 context switches
        double avg = total / (ITERATIONS * 2);

        printf("Context switch time: %f microseconds\n", avg * 1e6);
    }

    return 0;
}