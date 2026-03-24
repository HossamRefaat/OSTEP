#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

    int rc = fork();

    if (rc < 0) {
        perror("fork failed");
        exit(1);
    }

    if (rc == 0) {  // child
        close(STDOUT_FILENO);   // close standard output

        printf("Child: this should not appear\n");
    }
    else {  // parent
        printf("Parent: hello from parent\n");
    }

    return 0;
}