#include <unistd.h>
#include <stdio.h>

// SUMMARY
//
// Some system functions start asynchronous operations, that may
// notify results using signals.
//
// One of those functions is alarm(t), that will cause a SIGALRM signal
// to be delivered t seconds later.
//
// The default disposition for SIGALRM is Term, hence the program will
// terminate at most 20 seconds after starting.
//
// See more details about signals using:
//    man 7 signal

// COMPILE:
//   gcc -o sig02 sig02.c
//
// RUN:
//   ./sig02

int main() {

	alarm(10);
	
	puts("");
	puts("Hit CTRL-C to send SIGINT");
	puts("  or");
	printf("Run \"kill %d\" in another terminal to send SIGTERM\n", getpid());
	puts("  or");
	puts("Wait 10 seconds for SIGALRM");
	puts("");
	
	pause();

	return 0;
}