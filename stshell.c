#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>
typedef struct command
{
    char **argv;
    int isWriteTo;
    int isAppendTo;
    char *outputFile;
} command;

int containsWriteTo(char *cmd)
{
    if (strstr(cmd, ">"))
    {
        return 1;
    }
    return 0;
}

int containsAppendTo(char *cmd)
{
    if (strstr(cmd, ">>"))
    {
        return 1;
    }
    return 0;
}

char **getCommandAndFile(char *cmdToParse, const char *operation)
{
    char *cmd;
    char *fileName;
    char **cmdAndFile;
    char *token;
    int i, j;
    cmd = (char *)malloc(sizeof(char) * 1024);
    fileName = (char *)malloc(sizeof(char) * 1024);
    if (!cmd)
    {
        perror("command alocation faild in getCommandAndFile");
        exit(EXIT_FAILURE);
    }
    if (!fileName)
    {
        perror("file name alocation faild in getCommandAndFile");
        exit(EXIT_FAILURE);
    }

    token = strtok(cmdToParse, operation);

    // copy the first token (command) into currentCommand
    strncpy(cmd, token, 1024);
    // get the second token (file name)
    token = strtok(NULL, operation);
    // remove leading and trailing whitespace from the second token
    i = 0;
    while (isspace(token[i]))
    {
        i++;
    }
    j = strlen(token) - 1;
    while (isspace(token[j]))
    {
        j--;
    }
    token[j + 1] = '\0';
    strncpy(fileName, &token[i], 1024);

    cmdAndFile = (char **)malloc(sizeof(char *) * 2);
    if (!cmdAndFile)
    {
        perror("cmdAndFile alocation faild in getCommandAndFile");
        exit(EXIT_FAILURE);
    }
    cmdAndFile[0] = cmd;
    cmdAndFile[1] = fileName;
    return cmdAndFile;
}

char **generateCommandArgs(char *cmdToParse)
{
    int argCount = 1; // at least one argument (the command itself)
    char *p = cmdToParse;
    while (*p != '\0')
    {
        if (*p == ' ')
        {
            argCount++;
        }
        p++;
    }
    char **args = calloc(argCount + 1, sizeof(char *));// add one for NULL terminator
    if (args == NULL)
    {
        perror("Error: memory allocation failed\n");
        exit(1);
    }
    int i = 0;
    p = strtok(cmdToParse, " ");
    while (p != NULL)
    {
        args[i++] = p;
        p = strtok(NULL, " ");
    }
    args[argCount] = NULL; // terminate the array with NULL

    return args;
}

command *generateCommand(char *cmdToParse)
{
    char **cmdAndFile;
    command *cmd;
    int isWriteTo = 0;
    int isAppendTo = containsAppendTo(cmdToParse);
    if (!isAppendTo)
    {
        isWriteTo = containsWriteTo(cmdToParse);
    }
    cmd = (command *)malloc(sizeof(command));
    if (cmd == NULL)
    {
        perror("cmd allocation error in generate command");
    }
    cmd->isAppendTo = isAppendTo;
    cmd->isWriteTo = isWriteTo;
    if (!isWriteTo && !isAppendTo)
    {
        cmd->argv = generateCommandArgs(cmdToParse);
    }
    else if (isWriteTo)
    {
        cmdAndFile = getCommandAndFile(cmdToParse, ">");
        cmd->argv = generateCommandArgs(cmdAndFile[0]);
        cmd->outputFile = cmdAndFile[1];
    }
    else
    {
        cmdAndFile = getCommandAndFile(cmdToParse, ">>");
        cmd->argv = generateCommandArgs(cmdAndFile[0]);
        cmd->outputFile = cmdAndFile[1];
    }
    return cmd;
}

int spawn_proc(int in, int out, struct command *cmd)
{
    pid_t pid;
    if ((pid = fork()) == 0)
    {
        signal(SIGINT,SIG_DFL);
        if (in != 0)
        {
            dup2(in, 0);
            close(in);
        }
        if (out != 1)
        {
            dup2(out, 1);
            close(out);
        }

        return execvp(cmd->argv[0], (char *const *)cmd->argv);
    }

    return pid;
}
void fork_pipes(int n, command **cmds)
{
    int i;
    int in, fd[2], outputFd;
    FILE *file;

    /* The first process should get its input from the original file descriptor 0.  */
    in = 0;

    /* Note the loop bound, we spawn here all, but the last stage of the pipeline.  */
    for (i = 0; i < n; ++i)
    {
        pipe(fd);

        if (i == n - 1){
            if (!cmds[i]->outputFile) {
                spawn_proc(in, 1, cmds[i]);
                close(fd[1]);
            }else if(cmds[i]->isAppendTo){
                file = fopen(cmds[i]->outputFile,"a");
                outputFd = fileno(file);
                spawn_proc(in, outputFd, cmds[i]);
                close(outputFd);
            }else{
                file = fopen(cmds[i]->outputFile,"w");
                outputFd = fileno(file);
                spawn_proc(in, outputFd, cmds[i]);
                close(outputFd);
            }
        }
        else
        {
            if (!cmds[i]->outputFile) {
                spawn_proc(in, fd[1], cmds[i]);
                /* No need for the write end of the pipe, the child will write here.  */
                close(fd[1]);
                in = fd[0];
            }else if(cmds[i]->isAppendTo){
                file = fopen(cmds[i]->outputFile,"a");
                outputFd = fileno(file);
                spawn_proc(in, outputFd, cmds[i]);
                close(outputFd);
                in = 0;
            }else {
                file = fopen(cmds[i]->outputFile,"w");
                outputFd = fileno(file);
                spawn_proc(in, outputFd, cmds[i]);
                close(outputFd);
                in = 0;
            }
        }
        /* Keep the read end of the pipe, the next child will read from there.  */
        wait(NULL);
    }
    return;
}

int getNumberOfCommands(char *cmd)
{
    int counter = 1;
    for (size_t i = 0; i < strlen(cmd); i++)
    {
        if (cmd[i] == '|')
        {
            counter++;
        }
    }
    return counter;
}



int main()
{
    while (1)
    {
        signal(SIGINT,SIG_IGN);
        char input[1024];
        command *currentCommand;
        char *pipe_cmd;
        char **commandsStr;
        printf("stshell>> ");
        fgets(input, sizeof(input), stdin); // read input command
        input[strlen(input) - 1] = '\0';    // removing \n
        if (strcmp(input, "exit") == 0)
        {
            break;
        }
        int num_cmds = getNumberOfCommands(input);
        commandsStr = (char **)malloc(sizeof(char *) * num_cmds);
        command **cmds = malloc(sizeof(struct command) * num_cmds + 1); // allocate memory for cmds

        int cmd_idx = 0;
        pipe_cmd = strtok(input, "|"); // split input into commands
        while (pipe_cmd != NULL)
        {
            char *arg;
            arg = (char *)malloc(sizeof(char) * 1024);
            strcpy(arg, pipe_cmd); // split command into arguments
            // printf("%s\n", arg);
            commandsStr[cmd_idx++] = arg;
            pipe_cmd = strtok(NULL, "|");
        }
        for (int i = 0; i < cmd_idx; i++)
        {
            currentCommand = (command *)malloc(sizeof(command));
            currentCommand = generateCommand(commandsStr[i]);
            cmds[i] = currentCommand;
        }
        fork_pipes(cmd_idx, cmds);
        wait(NULL);
        for (int i = 0; i < num_cmds; i++)
        {
            if (cmds[i]->outputFile)
            {
                free(cmds[i]->outputFile);
            }


            free(cmds[i]->argv);
            free(cmds[i]);
        }

        // free command strings in commandsStr array
        for (int i = 0; i < num_cmds; i++)
        {
            free(commandsStr[i]);
        }

        // free commandsStr and cmds arrays
        free(commandsStr);
        free(cmds);
    }
    return 0;
}