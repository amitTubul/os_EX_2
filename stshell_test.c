#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int containsWriteTo


int main()
{
    char *command;
    char **commands;
    int size, i;
    while(1) {
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
        if(strcmp("exit", command)==0){
            break;
        }


    // Split the command string by "|"
    int num_commands = 1;
    for (i = 0; i < strlen(command); i++) {
        if (command[i] == '|') {
            num_commands++;
        }
    }
    commands = (char**)malloc(num_commands * sizeof(char*));
    if (commands == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    char *token = strtok(command, "|");
    i = 0;
    while (token != NULL) {
        commands[i] = (char*)malloc((strlen(token) + 1) * sizeof(char));
        if (commands[i] == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }
        strcpy(commands[i], token);
        token = strtok(NULL, "|");
        i++;
    }

    // Print the commands
    printf("The commands are:\n");
        pipe()
    for (i = 0; i < num_commands; i++) {
        fork()
        dup2(pipefd[1], STDOUT_FILENO)
        read(pipfd[0])
        execute



    }

    // Free the memory
    for (i = 0; i < num_commands; i++) {
        free(commands[i]);
    }
    free(commands);
    free(command);

    return 0;

}
