#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {

    int fd = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);

    if (fd < 0) {
        perror("open failed");
        exit(1);
    }

    int rc = fork();

    if (rc < 0) {
        perror("fork failed");
        exit(1);
    }

    if (rc == 0) { // child
        for (int i = 0; i < 5; i++) {
            write(fd, "child writing\n", 14);
        }
    } else { // parent
        for (int i = 0; i < 5; i++) {
            write(fd, "parent writing\n", 15);
        }

        wait(NULL);
    }

    close(fd);
    return 0;
}