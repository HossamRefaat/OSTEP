#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>

//Measuring the cost of a system call
int main() {
    struct timeval start, end;

    int fd = open("/dev/null", O_RDONLY);

    char buffer[1];

    gettimeofday(&start, NULL);

    for(int i = 0; i < 1000000; i++){
        read(fd, buffer, 0); // minimal syscall
    }

    gettimeofday(&end, NULL);

    long seconds = end.tv_sec - start.tv_sec;
    long micros = end.tv_usec - start.tv_usec;

    double totalTime = seconds + micros * 1e-6;
    double avg = totalTime / 1000000;

    printf("Time per syscall: %.12f seconds\n", avg);

    close(fd);
    return 0;
}