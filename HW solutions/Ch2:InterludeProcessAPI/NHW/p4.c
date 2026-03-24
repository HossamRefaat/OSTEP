#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include <sys/stat.h>
#include<sys/wait.h>

int main (int argc, char *argv[]){
    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork(); // create a new copy of the program
    if(rc < 0){
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if(rc == 0){
        close(STDOUT_FILENO);
        open("./p4.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
        printf("hello, i am child (pid:%d)\n", (int) getpid());
        char *myargs[3];
        myargs[0] = strdup("wc");
        myargs[1] = strdup("p4.c");
        myargs[2] = NULL;
        execvp(myargs[0],myargs); // it dosne't create a new process it transform the current 
                                  //running program into a diff running program
        printf("this shouldn't print out");
    }
    else {
        int wc = wait(NULL); // the parent process will always wait the chlid process to run first
        printf("hello, i am parent of %d (wc:%d) (pid:%d)\n", rc, wc, (int) getpid());
    }
    return 0;
}