#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "stdio.h"
#include "errno.h"
#include "stdlib.h"
#include "unistd.h"
#include <string.h>

int main() {
	int argc;
	char *argv[10];
	char command[1024];
	char *token;
    signal(SIGINT,SIG_IGN);
	while (1) {
        int status;
	    printf("stshell: ");
	    fgets(command, 1024, stdin);
	    command[strlen(command) - 1] = '\0'; // replace \n with \0

	    /* parse command line */
        argc = 0;
	    token = strtok (command," ");
	    while (token != NULL)
	    {
		    argv[argc] = token;
		    token = strtok (NULL, " ");
            argc++;
	    }
	    argv[argc] = NULL;

	    /* Is command empty */
	    if (argv[0] == NULL)
		continue;

        if(strcmp(argv[0],"exit")==0) return 0;

	    /* for commands not part of the shell command language */
        int pid=fork();

        if(pid==-1){
            perror("fork error");
            exit(EXIT_FAILURE);
        }

	    if (pid == 0) {
            signal(SIGINT,SIG_DFL);
            execvp(argv[0], argv);
            exit(EXIT_SUCCESS);
	    }

        else {
            wait(&status);
        }
	}
}
