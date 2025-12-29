#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
using namespace std;

int main() {
    
    // test inputs
    char* test_in[4] = {"1\n","2\n","3\n","4\n"}; 
    
    for (int i=0; i<4; i++) {
    // declare pipe
    int p[2]; // child writes parent 
    int fd[2]; // parent writes child
    char* buf[10]; 
    pipe(p);
    pipe(fd);
    pid_t pid = fork(); 

    if (pid == 0) { // child process
        // launch the child process
        char *argv[] = {NULL}; 
        // declare pipe here -> write to stdout

        // read port
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]); 

        // write port
        close(p[0]);
        dup2(p[1],STDOUT_FILENO); // write into the pipe (std output no longer be the output -> outputs to the pipe)
        close(p[1]);

        execv("harmonic",argv); 
        exit(1); 

    } else { // parent process

        // write input to child
        close(fd[0]); 
        write(fd[1],test_in[i],2);
        close(fd[1]);  

        // write pipe 
        close(p[1]);
        close(p[1]); // close write pipe - because the read is trying to get as much data as possible as long as the write port is open
        while (read(p[0],buf,sizeof(buf)) > 0) {
            printf("%s",buf);
            fflush(stdout); // remove weird duplicates in stdout
        }

        
        printf(""); 
        waitpid(pid,0,0); 
        // get the output from the stdout -> declare pipe here 
        // check the output against expected values (one improvement here)
    }
    }

    return 0; 

}







