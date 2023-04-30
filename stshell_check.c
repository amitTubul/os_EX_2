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
}command;

void freeCommand(command* cmd){
  int i=0, j=0;
  while (cmd->argv[i] !=  NULL)
  {
      free(cmd->argv[i]); 
    i++;
  }
  free(cmd->argv);
  free(cmd->outputFile);  
}

int containsWriteTo(char *cmd){
	if(strstr(cmd, ">")){
		return 1;
	}
	return 0;
}

int containsAppendTo(char* cmd){
	if (strstr(cmd, ">>")){
		return 1;
	}
	return 0;
}

char ** getCommandAndFile(char *cmdToParse,const char* operation){
	char* cmd, fileName;
	char ** cmdAndFile;
	char * token;
	int i, j;
	cmd = (char *) malloc(sizeof(char) * 1024);
	fileName = (char* ) malloc(sizeof(char) * 1024);
	if (!cmd){
		perror("command alocation faild in getCommandAndFile");
		exit(EXIT_FAILURE);
	}
	if (!fileName){
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
    while (isspace(token[i])) {
        i++;
    }
    j = strlen(token) - 1;
    while (isspace(token[j])) {
        j--;
    }
    token[j+1] = '\0';
    strncpy(fileName, &token[i], 1024);

	cmdAndFile = (char **) malloc (sizeof(char *) * 2);
	if (!cmdAndFile){
		perror("cmdAndFile alocation faild in getCommandAndFile");
		exit(EXIT_FAILURE);
	}
	cmdAndFile[0] = cmd;
	cmdAndFile[1] = fileName;
	return cmdAndFile;
}

char** generateCommandArgs(char* cmdToParse) {
    int argCount = 1; // at least one argument (the command itself)
    char* p = cmdToParse;
    while (*p != '\0') {
        if (*p == ' ') {
            argCount++;
        }
        p++;
    }
    char** args = malloc((argCount + 1) * sizeof(char*)); // add one for NULL terminator
    if (args == NULL) {
        perror("Error: memory allocation failed\n");
        exit(1);
    }
    int i = 0;
    p = strtok(cmdToParse, " ");
    while (p != NULL) {
        args[i++] = p;
        p = strtok(NULL, " ");
    }
    args[i] = NULL; // terminate the array with NULL

    return args;
}

command* generateCommand(char* cmdToParse){
	char ** cmdAndFile, args;
	command* cmd;
	int isWriteTo = 0;
	int isAppendTo = containsAppendTo(cmdToParse);
	if (!isAppendTo){
		isWriteTo = containsWriteTo(cmdToParse);
	}
	cmd = (command *) malloc (sizeof(command ));
	if(cmd == NULL){
		perror("cmd allocation error in generate command");
	}
	cmd->isAppendTo = isAppendTo;
	cmd->isWriteTo = isWriteTo;
	if(!isWriteTo && !isAppendTo){
		cmd->argv = generateCommandArgs(cmdToParse);
	}
	else if(isWriteTo){
		cmdAndFile = getCommandAndFile(cmdToParse, ">");
		cmd->argv = generateCommandArgs(cmdAndFile[0]);
		cmd->outputFile = cmdAndFile[1];
	}else{
		cmdAndFile = getCommandAndFile(cmdToParse, ">>");
		cmd->argv = generateCommandArgs(cmdAndFile[0]);
		cmd->outputFile = cmdAndFile[1];
	}
	return cmd;
}

void printCommand(command* cmd){
  int i = 0;
  printf("Command is:\n");
  printf("Arguments: \n");
  while(cmd->argv[i] != NULL){
    printf("%s, ", cmd->argv[i]);
    i++;
  }
  printf("isWrite: %d", cmd->isWriteTo);
  printf("isAppend: %d", cmd->isAppendTo);
  if(cmd->outputFile != NULL){
    printf("Output File: %s", cmd->outputFile);
  }else{
    printf("Output File: do not exist");
  }
}

int
spawn_proc (int in, int out, struct command *cmd)
{
  pid_t pid;

  if ((pid = fork ()) == 0)
    {
      if (in != 0)
        {
          dup2 (in, 0);
          close (in);
        }

      if (out != 1)
        {
          dup2 (out, 1);
          close (out);
        }

      return execvp (cmd->argv [0], (char * const *)cmd->argv);
    }

  return pid;
}
int
fork_pipes (int n, command *cmd)
{
  int i;
  pid_t pid;
  int in, fd [2];

  /* The first process should get its input from the original file descriptor 0.  */
  in = 0;

  /* Note the loop bound, we spawn here all, but the last stage of the pipeline.  */
  for (i = 0; i < n - 1; ++i)
    {
      pipe (fd);

      /* f [1] is the write end of the pipe, we carry `in` from the prev iteration.  */
      spawn_proc (in, fd [1], cmd + i);

      /* No need for the write end of the pipe, the child will write here.  */
      close (fd [1]);

      /* Keep the read end of the pipe, the next child will read from there.  */
      in = fd [0];
    }

  /* Last stage of the pipeline - set stdin be the read end of the previous pipe
     and output to the original file descriptor 1. */  
  if (in != 0)
    dup2 (in, 0);

  /* Execute the last stage with the current process. */
  return execvp (cmd [i].argv [0], (char * const *)cmd [i].argv);
}

int getNumberOfCommands(char* cmd){
  int counter = 1;
  for (size_t i = 0; i < strlen(cmd); i++)
  {
    if(cmd[i] == '|'){
      counter++;
    }
  }
  return counter;
}

int
main ()
{
    char input[1024];
    command* currentCommand;
    fgets(input, sizeof(input), stdin);  // read input command

    int num_cmds = getNumberOfCommands(input);

    command **cmds = malloc(sizeof(struct command) * num_cmds + 1);  // allocate memory for cmds

    char *pipe_cmd;
    int cmd_idx = 0;
    pipe_cmd = strtok(input, "|");  // split input into commands
    while (pipe_cmd != NULL) {
        char *arg;
        strcpy(arg, pipe_cmd);  // split command into arguments
        currentCommand = (command *) malloc(sizeof(command));
        currentCommand = generateCommand(arg);
        printCommand(currentCommand);
        cmds[cmd_idx++] = currentCommand;
        pipe_cmd = strtok(NULL, "|");
    }
  // return fork_pipes (2, cmds);

  for (size_t i = 0; i < num_cmds; i++)
  {
    freeCommand(cmds[i]);
  }
  free(cmds);
  
  return 0;
}