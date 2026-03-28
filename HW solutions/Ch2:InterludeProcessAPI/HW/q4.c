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
        printf("Child running ls:\n");

        execl("/bin/ls", "ls", NULL);

        // only runs if exec fails
        perror("exec failed");
        exit(1);
    } 
    else {  // parent process
        wait(NULL);
        printf("Parent: child completed\n");
    }

    return 0;
}