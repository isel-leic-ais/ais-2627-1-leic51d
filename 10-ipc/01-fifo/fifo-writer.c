#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>

int main(int argc, const char * argv[]) {
	if (argc != 2) {
		fprintf(stderr, "use: %s fifo_name\n", argv[0]);
		exit(1);
	} 
	
	const char * fifo_name = argv[1];
	
	int f = open(fifo_name, O_RDWR);

	char line[256];
	for (;;) {
		char * s = fgets(line, 255, stdin);
		if (s == NULL) break;
		size_t l = strlen(line);
		write(f, line, l);
	}
	close(f);
	
	puts("========");
	puts("DONE");
	return 0;
}
