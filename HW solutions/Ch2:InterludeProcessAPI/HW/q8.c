#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

    int pipefd[2];
    pipe(pipefd);  // create pipe

    int rc1 = fork();

    if (rc1 == 0) {  // first child (producer)

        close(pipefd[0]);  // close read end

        dup2(pipefd[1], STDOUT_FILENO);  // redirect stdout to pipe
        close(pipefd[1]);

        execlp("ls", "ls", NULL);

        perror("exec failed");
        exit(1);
    }

    int rc2 = fork();

    if (rc2 == 0) {  // second child (consumer)

        close(pipefd[1]);  // close write end

        dup2(pipefd[0], STDIN_FILENO);  // redirect stdin from pipe
        close(pipefd[0]);

        execlp("wc", "wc", "-l", NULL);

        perror("exec failed");
        exit(1);
    }

    // parent process
    close(pipefd[0]);
    close(pipefd[1]);

    wait(NULL);
    wait(NULL);

    return 0;
}