#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

    int rc = fork();

    if (rc < 0) {
        perror("fork failed");
        exit(1);
    }

    if (rc == 0) { // child
        printf("hello\n");
    } 
    else { // parent
        sleep(1);   // delay parent
        printf("goodbye\n");
    }

    return 0;
}