#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, const char * argv[]) {
	if (argc != 2) {
		fprintf(stderr, "use: %s fifo_name\n", argv[0]);
		exit(1);
	} 

	const char * fifo_name = argv[1];
	
	int f = open(fifo_name, O_RDONLY);
	
	char data[16];
	for (;;) {
		int n = read(f, data, 16);
		if (n == 0) break;
		
		write(1, data, n);
	}
	
	puts("========");
	puts("DONE");
	return 0;
}
