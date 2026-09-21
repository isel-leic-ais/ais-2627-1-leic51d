#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

// SUMMARY
//
// The file descriptor table is copied during a fork.
// We may force file descriptor 1 in the child process
// to refer to a file, instead of its original value.
// This is usually called a redirection of the standard
// output and it can also be done for any other descriptor.

// COMPILE:
//   gcc -o prog05 prog05-redir.c
//
// RUN:
//   ./prog05

int main() {
	puts("prog05 running");

	printf("PROCESS: pid=%d ; ppid=%d\n", 
		getpid(), getppid()
	);

	pid_t pid = fork();
	if (pid == 0) {
		printf("CHILD: pid=%d ; ppid=%d\n", 
			getpid(), getppid()
		);

		int fdout = open("output.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
		dup2(fdout, 1);
		close(fdout);

		puts("CHILD: exec...");
		execlp("ls", "ls", "-l", "/dev", NULL); // this will not return on success!

		perror(
			"=======================\n"
			"EXEC FAILED\n"
			"-----------------------\n"
		);
		exit(1);
	} else {
		printf("PARENT: pid=%d ; ppid=%d\n", 
			getpid(), getppid()
		);
		int res = 0;
		waitpid(pid, &res, 0);
		if (WIFEXITED(res)) {
			printf("PARENT: child returned %d\n", 
				WEXITSTATUS(res)
			);
		} else {
			printf("PARENT: child terminated\n"); 
		}
	}

	puts("THE END");
	return 0;
}		
