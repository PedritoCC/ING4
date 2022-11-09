#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {

    int pipefd[2];
    pid_t cpid;
    char buf;

    if (argc != 2) {fprintf(stderr, "Usage: %s <string>\n", argv[0]); exit(EXIT_FAILURE);}
    
    //Creation of the pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    cpid = fork(); 
    if(cpid == -1) {
        perror("fork"); 
        exit(EXIT_FAILURE);
    }

    if (cpid == 0) { 
        // Child process

        // Closing the pipe write end
        close(pipefd[1]);
        // Making the standard input to be the read end
        dup2(pipefd[0], STDIN_FILENO);
        // Executing "more"
        system("more");
        // Closing the pipe read end
        close(pipefd[0]);
        exit(EXIT_SUCCESS);
    } 
    else { 
        // Parent process

        // Closing the pipe read end
        close(pipefd[0]); 
        //Changing the standard output 
        dup2(pipefd[1], STDOUT_FILENO);
        //Execute "ps aux"
        system("ps aux");
        //Closing the pipe write end
        close(pipefd[1]);
        // Wait for child 
        wait(NULL); 
        exit(EXIT_SUCCESS);
    }
}
