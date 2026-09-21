#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

// SUMMARY
//
// Demonstrates how the shell executes a command line like:
//   ls -l /dev | grep sd
//
// Notes:
//   - the pipe is created by the initial process;
//   - two descriptors are used:
//      ~ one for writing into the pipe
//      ~ another for reading from the pipe
//   - the main process forks twice, creating two others processes
//   - the first child sets the pipe descriptor for writing as its
//     standard output; then executes "ls -l /dev"
//   - the second child sets the pipe descriptor for reading as its
//     standard input; then executes "grep sd"
//   - the main process then waits for both children to finish
//   - closing uneeded descriptors for the pipe is essential; why?

// COMPILE:
//   gcc -o prog06 prog06-pipe.c
//
// RUN:
//   ./prog06

int main() {
	puts("prog06 running");

	int pipefd[2];

	// Creates the pipe; gets two file descriptors.
	pipe(pipefd);

	pid_t pid1 = fork();
	if (pid1 == 0) {
		dup2(pipefd[1], 1);

		close(pipefd[0]);
		close(pipefd[1]);

		execlp("ls", "ls", "-l", "/dev", NULL);
		
		perror("FAILED to exec ls");
		exit(1);
	} else {
		pid_t pid2 = fork();
		if (pid2 == 0) {
			dup2(pipefd[0], 0);

			close(pipefd[0]);
			close(pipefd[1]);

			execlp("grep", "grep", "sd", NULL);
			
			perror("FAILED to exec grep");
			exit(1);
		} else {
			close(pipefd[0]);
			close(pipefd[1]);
			wait(NULL);
			wait(NULL);
		}
	}
	puts("THE END");
	return 0;
}		
