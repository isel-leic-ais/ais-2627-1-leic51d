// SUMMARY
//
// This example demonstrates how the process heap and runtime-loaded shared
// libraries appear in memory. It pauses between allocations so you can inspect
// the process state and map layout from another terminal.
//
// COMPILE:
//   gcc -o prog prog.c -ldl
//
// RUN:
//   ./prog

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <dlfcn.h>

int main() {
	printf("PID: %u\n", getpid());

	const long PAGE_SIZE = sysconf(_SC_PAGE_SIZE);
	printf("PAGE_SIZE: %ld\n", PAGE_SIZE);

	printf("#1 (press ENTER to continue)"); getchar();
	
	puts("> malloc(320)");
	void * ptr1 = malloc(320);
	printf("ptr1: %p\n", ptr1);

	printf("#2 (press ENTER to continue)"); getchar();
	
	puts("> malloc(1024*1024)");
	void * ptr2 = malloc(1024*1024);
	printf("ptr2: %p\n", ptr2);

	printf("#3 (press ENTER to continue)"); getchar();
	
	puts("> dlopen(\"libcurl.so\")");
	void * ptr3 = dlopen("libcurl.so.4", RTLD_NOW | RTLD_LOCAL);
	printf("ptr3: %p\n", ptr3);

	printf("#4 (press ENTER to continue)"); getchar();
	if (dlclose(ptr3) != 0) {
		fprintf(stderr, "dlclose failed: %s\n", dlerror());
	}

	printf("(press ENTER to terminate)"); getchar();
	return 0;
}
