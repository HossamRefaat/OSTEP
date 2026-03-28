#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

    int rc = fork();

    if (rc < 0) {
        perror("fork failed");
        exit(1);
    }

    if (rc == 0) {  // child process
        printf("Child (pid:%d)\n", getpid());
        exit(0);
    } 
    else {  // parent process
        int status;
        int wc = waitpid(rc, &status, 0);  // wait for specific child

        printf("Parent (pid:%d)\n", getpid());
        printf("waitpid returned: %d\n", wc);
    }

    return 0;
}