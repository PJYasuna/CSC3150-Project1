#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int status;
	printf("Process start to fork\n");
	pid_t pid = fork();

	if (pid == -1) {
		perror("fork");
		exit(1);
	} else {
		if (pid == 0) {
			printf("I'm the child process, my pid = %d\n",
			       getpid());

			int i;
			char *arg[argc];
			for (i = 0; i < argc - 1; i++) {
				arg[i] = argv[i + 1];
			}
			arg[argc - 1] = NULL;

			printf("Child process start to excute test program:\n");
			execve(arg[0], arg, NULL);

			printf("continue to run original child process!\n");

			perror("execve");
			exit(EXIT_FAILURE);
		}

		else {
			printf("I'm the parent process, my pid = %d\n",
			       getpid());

			waitpid(pid, &status, WUNTRACED);

			printf("Parent process receives SIGCHLD signal\n");

			if (WIFEXITED(status)) {
				printf("Normal termination with EXIT STATUS = %d\n",
				       WEXITSTATUS(status));
			} else if (WIFSIGNALED(status)) {
				int num = WTERMSIG(status);
				switch (num) {
				case 6: // SIGABRT
					printf("child process get SIGABRT signal\n");
					break;
				case 14: // SIGALRM
					printf("child process get SIGALRM signal\n");
					break;
				case 7: // SIGBUS
					printf("child process get SIGBUS signal\n");
					break;
				case 8: // SIGFPE
					printf("child process get SIGFPE signal\n");
					break;
				case 1: // SIGHUP
					printf("child process get SIGHUP signal\n");
					break;
				case 4: // SIGILL
					printf("child process get SIGILL signal\n");
					break;
				case 2: // SIGINT
					printf("child process get SIGINT signal\n");
					break;
				case 9: // SIGKILL
					printf("child process get SIGKILL signal\n");
					break;
				case 13: // SIGPIPE
					printf("child process get SIGPIPE signal\n");
					break;
				case 3: // SIGQUIT
					printf("child process get SIGQUIT signal\n");
					break;
				case 11: // SIGSEGV
					printf("child process get SIGSEGV signal\n");
					break;
				case 15: // SIGTERM
					printf("child process get SIGTERM signal\n");
					break;
				case 5: // SIGTRAP
					printf("child process get SIGTRAP signal\n");
					break;
				}
			} else if (WIFSTOPPED(status)) {
				printf("child process get SIGSTOP signal\n");
			} else {
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
