#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

int main(int argc, char *argv[]){
	int status;
	printf("Process start to fork\n");	
	pid_t pid = fork();
	

	if (pid == -1) {
		perror("fork");
		exit(1);
	}
	else {
		if (pid == 0) {
			printf("I'm the child process, my pid = %d\n", getpid());
			
			int i;
			char *arg[argc];
			for (i = 0; i < argc - 1; i++) {
				arg[i] = argv[i+1];
			}
			arg[argc-1] = NULL;

			printf("Child process start to excute test program:\n");
			execve(arg[0], arg, NULL);

			printf("Aoh, continue to run original child process!\n");

			perror("execve");
			exit(EXIT_FAILURE);
		}

		else {
			printf("I'm the parent process, my pid = %d\n", getpid());

			wait(&status);
			if (WIFEXITED(status)) {
				printf("Normal termination with EXIT STATUS = %d\n", WEXITSTATUS(status));
			}
			else if (WIFSIGNALED(status)) {
				printf("Child excution failed, the parent receive : %d", WTERMSIG(status));
			}
			else if (WIFSTOPPED(status)) {
				printf("Child excution stopped, the parent receive : %d", WSTOPSIG(status));
			}
			else {
				printf("Child process continued\n");
			}
			exit(0);
		}
	}
	/* fork a child process */
	
	/* execute test program */ 
	
	/* wait for child process terminates */
	
	/* check child process'  termination status */
	
	
}
