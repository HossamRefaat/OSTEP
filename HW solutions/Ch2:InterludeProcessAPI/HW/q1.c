#include <stdio.h>
#include <stdlib.h> // exit
#include <sys/wait.h>
#include <unistd.h> // fork

int main (int argc, char *argv[]){
    int x = 100;
    int rc = fork();
    if(rc < 0){
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if(rc == 0){
        //x = 101;
        printf("child (x:%d)\n", x);
    }
    else {
        //x = 102;
        printf("parent (x:%d)\n", x);
        wait(NULL);
    }
    return 0;
}