#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
using namespace std;

int main() {
    
    // declare pipe
    int p[2]; 
    char* buf[10]; 
    pipe(p);
    pid_t pid = fork(); 

    if (pid == 0) { // child process
        // launch the child process
        char *argv[] = {NULL}; 
        // declare pipe here -> write to stdout
        close(p[0]);
        dup2(p[1],STDOUT_FILENO); 
        close(p[1]);
        execv("harmonic",argv); 
        exit(1); 
    } else { // parent process
        // close(p[1]);
        close(p[1]); // close write pipe - because the read is trying to get as much data as possible as long as the write port is open
        while (read(p[0],buf,sizeof(buf)) > 0) {
            printf("%s",buf);
        }
        
        waitpid(pid,0,0); 
        
        printf("parent done\n");
        // get the output from the stdout -> declare pipe here 
        // check the output against expected values (one improvement here)
    }

    return 0; 

}







