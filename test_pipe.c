////
//// Created by itamarq on 4/28/23.
////
//#include <stdio.h>
//#include <unistd.h>
//#include <sys/types.h>
//#include <sys/wait.h>
//
//int main()
//{
//    int pipefd[2];
//    pid_t pid;
//
//    // create pipe
//    if (pipe(pipefd) == -1) {
//        perror("pipe");
//        return 1;
//    }
//
//    // create child process
//    pid = fork();
//    if (pid == -1) {
//        perror("fork");
//        return 1;
//    }
//
//    if (pid == 0) { // child process
//        // close read end of pipe
//        close(pipefd[0]);
//
//        // redirect stdout to write end of pipe
//        dup2(pipefd[1], STDOUT_FILENO);
//
//        // execute command1
//        execlp("ls", "ls", NULL);
//        perror("execlp");
//        return 1;
//    } else { // parent process
//        // close write end of pipe
//        close(pipefd[1]);
//
//        // redirect stdin to read end of pipe
//        dup2(pipefd[0], STDIN_FILENO);
//
//        // execute command2
//        execlp("grep", "grep", "example", NULL);
//        perror("execlp");
//        return 1;
//    }
//
//    // close pipe ends and wait for child process to finish
//    close(pipefd[0]);
//    close(pipefd[1]);
//    wait(NULL);
//
//    return 0;
//}
