#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>

//
int containsWriteTo(char* command){
    for (int i = 0; i < strlen(command); ++i) {
        if(command[i] == '>') return 1;
    }
    return 0;
}

int getPosOfGreaterSign(char* command){
    for (int i = 0; i < strlen(command); ++i) {
        if(command[i] == '>') return i;
    }
    return 0;
}

int containsAppendTo(char* command){
    for (int i = 0; i < strlen(command) - 1; ++i) {
        if(command[i] == '>' && command[i+1] == '>') return 1;
    }
    return 0;
}


int main() {
    char *command;
    char currentCommand[100];
    char givenFIleName[100];
    char **commands;
    FILE* file;
    int size, i, pipeFlag =0, signPos,fd, pid;
    int pipefd[2];
    while (1) {
        printf("stshell: ");
        size = 10; // initial size of the command string
        command = (char *) malloc(size * sizeof(char));
        if (command == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }

        fgets(command, size, stdin);


        // Reallocate memory if necessary
        while (command[strlen(command) - 1] != '\n') {
            size += 10; // Increase the size of the command string by 10
            command = (char *) realloc(command, size * sizeof(char));
            if (command == NULL) {
                printf("Memory reallocation failed\n");
                return 1;
            }
            fgets(&command[strlen(command)], size - strlen(command), stdin);
        }

        // Remove the newline character from the end of the command string
        command[strlen(command) - 1] = '\0';
        if (strcmp("exit", command) == 0) {
            break;
        }


        // Split the command string by "|"
        int num_commands = 1;
        for (i = 0; i < strlen(command); i++) {
            if (command[i] == '|') {
                num_commands++;
            }
        }
        commands = (char **) malloc(num_commands * sizeof(char *));
        if (commands == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }

        char *token = strtok(command, "|");
        i = 0;
        while (token != NULL) {
            commands[i] = (char *) malloc((strlen(token) + 1) * sizeof(char));
            if (commands[i] == NULL) {
                printf("Memory allocation failed\n");
                return 1;
            }
            strcpy(commands[i], token);
            token = strtok(NULL, "|");
            i++;
        }
        
        pipe(pipefd);
        for (int j = 0; j < num_commands; ++j) {
            if (containsAppendTo(commands[j])) {
                token = strtok(command, ">>");

                // copy the first token (command) into currentCommand
                strncpy(currentCommand, token, 99);

                // get the second token (file name)
                token = strtok(NULL, ">>");

                // remove leading and trailing whitespace from the second token
                i = 0;
                while (isspace(token[i])) {
                    i++;
                }
                j = strlen(token) - 1;
                while (isspace(token[j])) {
                    j--;
                }
                token[j+1] = '\0';

                strncpy(givenFIleName, &token[i], 99);

                file = fopen(givenFIleName, "a");
                if (file == NULL){
                    perror("File open failed");
                    exit(1);
                }
                fd = fileno(file);
                pid = fork();
                if(pid==-1){
                    perror("fork error");
                    exit(EXIT_FAILURE);
                }
                if (pid == 0){
                    int argc = 0;
                    char* argv[10];

                    char* token = strtok(currentCommand, " ");
                    while (token != NULL) {
                        argv[argc++] = token;
                        token = strtok(NULL, " ");
                    }
                    argv[argc] = NULL;
                    dup2(fd, STDOUT_FILENO);
                    execvp(argv[0], argv);
                    fclose(file);
                    exit(EXIT_SUCCESS);

                }
                wait(NULL);
            }
            else if(containsWriteTo(commands[j])){
                signPos = getPosOfGreaterSign(commands[j]);
                token = strtok(command, ">");

                // copy the first token (command) into currentCommand
                strncpy(currentCommand, token, 99);

                // get the second token (file name)
                token = strtok(NULL, ">");

                // remove leading and trailing whitespace from the second token
                i = 0;
                while (isspace(token[i])) {
                    i++;
                }
                j = strlen(token) - 1;
                while (isspace(token[j])) {
                    j--;
                }
                token[j+1] = '\0';

                strncpy(givenFIleName, &token[i], 99);

                file = fopen(givenFIleName, "w");
                if (file == NULL){
                    perror("File open failed");
                    exit(1);
                }
                fd = fileno(file);
                pid = fork();
                if(pid==-1){
                    perror("fork error");
                    exit(EXIT_FAILURE);
                }
                if (pid == 0){
                    int argc = 0;
                    char* argv[10];

                    char* token = strtok(currentCommand, " ");
                    while (token != NULL) {
                        argv[argc++] = token;
                        token = strtok(NULL, " ");
                    }
                    argv[argc] = NULL;
                    dup2(fd, STDOUT_FILENO);
                    execvp(argv[0], argv);
                    fclose(file);
                    exit(EXIT_SUCCESS);

                }
                wait(NULL);
            }else{
                if (j == 0){
                    pid = fork();
                    if(pid==-1){
                        perror("fork error");
                        exit(EXIT_FAILURE);
                    }
                    if (pid == 0){
                        int argc = 0;
                        char* argv[10];

                        char* token = strtok(currentCommand, " ");
                        while (token != NULL) {
                            argv[argc++] = token;
                            token = strtok(NULL, " ");
                        }
                        argv[argc] = NULL;
                        if(pipeFlag){
                            close(pipefd[1]);
                            dup2(pipefd[1], STDOUT_FILENO);
                        }
                        execvp(argv[0], argv);

                        exit(EXIT_SUCCESS);

                    }
                    wait(NULL);
                }
                pid = fork();
                if(pid==-1){
                    perror("fork error");
                    exit(EXIT_FAILURE);
                }
                if (pid == 0){
                    int argc = 0;
                    char* argv[10];

                    char* token = strtok(commands[j], " ");
                    while (token != NULL) {
                        argv[argc++] = token;
                        token = strtok(NULL, " ");
                    }
                    argv[argc] = NULL;
                    //TODO: add output redirection to pipe if the flag is true.
                    execvp(argv[0], argv);
                    exit(EXIT_SUCCESS);
                }
                wait(NULL);
            }

        }

        // Free the memory
        for (i = 0; i < num_commands; i++) {
            free(commands[i]);
        }
        free(commands);
        free(command);

        return 0;

    }
}