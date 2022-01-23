#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{   char input[2048];
    char *new_argv[128];
    char *token;
    int i = 0;

    printf("baleria$ ");
    fgets(input, sizeof input, stdin);
    printf("%s\n", input);

    if ((token = strtok(input, " \t\n\r")) != NULL) {
        do {
            new_argv[i++] = token;
            printf("Token: \"%s\"\n", token);
        } while ((token = strtok(NULL, " \t\n\r")) != NULL);
    }
    new_argv[i] = NULL;

    if (strcmp(new_argv[0], "cd") == 0) {
        if(chdir(new_argv[1]) == -1)
			perror("Error triggered");
	} 

    else if (strcmp(new_argv[0], "exit") == 0) {
			exit(0);
	}

    else {
		pid_t pid = fork();
		if(pid == 0) {
			execvp(new_argv[0], new_argv);
			perror("exec");
			exit(1);
		}
    }

        wait(NULL);
}