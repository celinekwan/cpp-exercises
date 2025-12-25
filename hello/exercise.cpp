#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h> /* for string compare */
#include <unistd.h> /* for fork */
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */
#include <fcntl.h> /* for f_cntl */
using namespace std;

int main() {
    // cout << "Hello World";

    int p[2];
    char buf[1024];
    pipe(p);

    pid_t pid=fork();
    if (pid==0) { // child process runs this 
        static char *argv[]={NULL};
        close(p[0]);
        dup2(p[1],STDOUT_FILENO);  
        execv("hello",argv); 
    } else { // parent process runs this
        close(p[1]); 
        // fcntl(p[0], F_SETFL, fcntl(p[0], F_GETFL, NULL ) | O_NONBLOCK );

        // input
        while (read(p[0],buf,1024) > 0) {
            printf("%s",buf); 
        }
        
        waitpid(pid,0,0); // wait for process to terminate successfully 
        printf("pid=%d\n",pid); 

        // compare against desired output
        char* expected = "Hello, World!";
        if (strcmp(expected,buf)==0) {
            printf("Matches");
        } else {
            printf("Doesn't match\n");
        }

    }

    // TODO: expand into reusable tests for labs

    return 0; 
}
