#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// SUMMARY
//
// Every process has its own file descriptor table (in kernel space).
// File descriptors are positive integer values, that are indices to this table.
// Entries 0, 1, 2 refer to standard input, standard output, and standard error, respectively.
// Opening a file occupies another entry.

// COMPILE:
//   gcc -o prog01 prog01-files.c
//
// RUN:
//   ./prog01 output.txt

int main(int argc, const char * argv[]) {
	puts("prog01 running");

	if (argc != 2) {
		// In C, we could use fprintf(stderr, ...), from the
		// C standard library, where fprintf would end up calling
		// write(2, ...) internally.
		// But here we execute a direct system call to the kernel,
		// for demonstration purposes.
		write(2, "missing file name\n", 18);
		exit(1);
	}
	
	// fd will likely be 3, the first available entry
	int fd = open(argv[1], O_CREAT | O_RDWR, 0644);

	printf("fd: %d\n", fd);
	
	// If fd really has the value 3, this should write a message
	// into the file. THIS IS NOT SOMETHING YOU SHOULD USUALLY DO!
	write(3, "Hello, ISEL LEIC!\n", 18);
	
	// This will write a message into the file referred by fd.
	write(fd, "Hello, AIS LEIC51D!\n", 20);

	close(3);

	close(fd);

	return 0;
}
