#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
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
		O_RDWR|O_CREAT|O_EXCL,
		0644
	);
	if (shfd == -1) {
		perror("shm_open failed");
		exit(1);
	}

	int tres = ftruncate(shfd, SMA_SIZE);
	if (tres == -1) {
		perror("ftruncate failed");
		exit(1);
	}

	puts("CREATED");
	
	void * psha = mmap(NULL, SMA_SIZE, PROT_READ, MAP_SHARED, shfd, 0);
	if (psha == NULL) {
		perror("mmap failed");
		exit(1);
	}
	
	puts("MMAPPED");

	for (;;) {
		sleep(5);
		puts("================");
		puts((const char *)psha);
	}

	return 0;
}
