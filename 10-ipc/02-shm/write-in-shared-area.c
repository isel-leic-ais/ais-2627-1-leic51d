#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>

/* Shared memory areas require some form of synchronization, as
   they're meant to be accessed concurrently.
   This example is UNSYNCHRONIZED. DO NOT USE AS A REFERENCE!
*/

#define SMA_SIZE 4096

int main(int argc, const char * argv[]) {
	if (argc != 2) {
		fprintf(stderr, "use: %s shared_area_name\n", argv[0]);
		exit(1);
	} 
	
	const char * shared_area_name = argv[1];
	
	int shfd = shm_open(
		shared_area_name,
		O_RDWR,
		0
	);
	if (shfd == -1) {
		perror("shm_open failed");
		exit(1);
	}

	puts("OPEN");

	void * psha = 
		mmap(NULL, SMA_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, shfd, 0);
	if (psha == NULL) {
		perror("mmap failed");
		exit(1);
	}
	
	puts("MMAPPED");

	char line[256];
	for (;;) {
		char * s = fgets(line, 255, stdin);
		if (s == NULL) break;
		memset(psha, 0, 4096);
		memcpy(psha, line, 256);
	}
	
	puts("BYE");
	return 0;
}
