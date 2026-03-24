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
    if (rc == 0) {
        int wc = wait(NULL);
        printf("Child (pid:%d)\n", getpid());
        printf("Child wait returned: %d\n", wc); //will return -1 cause there is no children
    }
    else { // parent
        int wc = wait(NULL);   // wait for child to finish
        printf("Parent (pid:%d)\n", getpid());
        printf("wait returned: %d\n", wc);
    }

    return 0;
}