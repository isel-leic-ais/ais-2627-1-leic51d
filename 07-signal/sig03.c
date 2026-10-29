#include <unistd.h>
#include <stdio.h>
#include <signal.h>

// SUMMARY
//
// The disposition for each signal can be changed using the function
// signal.
//
// This simple demo configures SIGINT, SIGTERM, and SIGALRM to be
// ignored.  Use SIGKILL to stop the program, with:
//    kill -9 process_id
//
// See more details about signals using:
//    man 7 signal

// COMPILE:
//   gcc -o sig03 sig03.c
//
// RUN:
//   ./sig03

int main() {

	signal(SIGINT,  SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGALRM, SIG_IGN);

	alarm(10);
	
	puts("");
	puts("Hit CTRL-C to send SIGINT  [IGNORED]");
	puts("  or");
	printf("Run \"kill %d\" in another terminal to send SIGTERM  [IGNORED]\n", getpid());
	puts("  or");
	puts("Wait 10 seconds for SIGALRM  [IGNORED]");
	puts("");

	printf("Run \"kill -USR1 %d\" in another terminal to send SIGUSR1\n", getpid());
	puts("");
	
	pause();

	return 0;
}