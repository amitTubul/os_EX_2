#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    int fd[2]; // file descriptors for the read and write ends of the pipe
    pid_t pid1, pid2;
    char buffer[20];

    // create the pipe
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // fork the first child process
    pid1 = fork();

    if (pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) { // first child process
        close(fd[1]); // close the write end of the pipe
        read(fd[0], buffer, sizeof(buffer)); // read from the read end of the pipe
        printf("First child process received: %s\n", buffer);

        close(fd[0]); // close the read end of the pipe
        write(fd[1], "Hello, second child process!", 28); // write to the write end of the pipe
        close(fd[1]); // close the write end of the pipe

        exit(EXIT_SUCCESS);
    } else { // parent process
        // fork the second child process
        pid2 = fork();

        if (pid2 == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid2 == 0) { // second child process
            close(fd[1]); // close the write end of the pipe
            read(fd[0], buffer, sizeof(buffer)); // read from the read end of the pipe
            printf("Second child process received: %s\n", buffer);
            close(fd[0]); // close the read end of the pipe
            exit(EXIT_SUCCESS);
        } else { // parent process
            close(fd[0]); // close the read end of the pipe
            write(fd[1], "Hello, first child process!", 27); // write to the write end of the pipe
            close(fd[1]); // close the write end of the pipe
            wait(NULL); // wait for the first child process to exit
            wait(NULL); // wait for the second child process to exit
            exit(EXIT_SUCCESS);
        }
    }
}
