#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// SUMMARY
//
// waitpid can be used to obtain the termination status of a child process.
// Several standard macros allow for obtaining specific items of information
// from the status code.

// COMPILE:
//   gcc -o prog03 prog03-waitpid.c
//
// RUN:
//   ./prog03

int main() {
	puts("prog03 running");

	printf("PROCESS: pid=%d ; ppid=%d\n", 
		getpid(), getppid()
	);

	pid_t pid = fork();
	if (pid == 0) {
		printf("CHILD: pid=%d ; ppid=%d\n", 
			getpid(), getppid()
		);
		//*(char*)(NULL) = '0'; // uncomment to cause a segmentation fault in the child!
		return 123;
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
