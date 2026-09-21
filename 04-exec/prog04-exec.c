#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// SUMMARY
//
// exec rebuilds the address space of the current process for
// a new execution of a specified program.
// Current execution is abruptly eliminated and the same process
// begins execution at the start of the specified program. 
// When combined with fork, it allows for creating a new process
// running some chosen program, while fork alone always creates
// a new process for the same program that called it.
//
// Type "man exec" to see the documentation for the several
// variants of exec. Note that exec can have:
//   - 'l' (list of args) or 'v' (vector of args)
//   - 'p' (look for program in PATH)
//   - 'e' (define environment variables)

// COMPILE:
//   gcc -o prog04 prog04-exec.c
//
// RUN:
//   ./prog04

int main() {
	puts("prog04 running");

	printf("PROCESS: pid=%d ; ppid=%d\n", 
		getpid(), getppid()
	);

	pid_t pid = fork();
	if (pid == 0) {
		printf("CHILD: pid=%d ; ppid=%d\n", 
			getpid(), getppid()
		);
		
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
