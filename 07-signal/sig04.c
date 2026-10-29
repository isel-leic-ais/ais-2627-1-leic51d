#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>

// SUMMARY
//
// The disposition for each signal can also be set to a specific 
// signal handling function. Use sigaction (not signal) for that.
//
// This simple demo configures SIGINT, SIGTERM, and SIGALRM to be
// ignored.  Use SIGKILL or SIGUSR1 to stop the program, with:
//    kill -9 process_id
// or
//    kill -USR1 process_id
//
// See more details about signals using:
//    man 7 signal

// COMPILE:
//   gcc -o sig04 sig04.c
//
// RUN:
//   ./sig04

void sigIntHandler(int signum) {
	puts(" SIGINT ignored");
}

void sigTermHandler(int signum) {
	puts("SIGTERM ignored");
}

void sigAlrmHandler(int signum) {
	puts("SIGALRM ignored");
}

int main() {

	struct sigaction actionInt;
	memset(&actionInt, 0, sizeof(struct sigaction));
	actionInt.sa_handler = sigIntHandler;
	sigaction(SIGINT, &actionInt, NULL);

	struct sigaction actionTerm;
	memset(&actionTerm, 0, sizeof(struct sigaction));
	actionTerm.sa_handler = sigTermHandler;
	sigaction(SIGTERM, &actionTerm, NULL);

	struct sigaction actionAlarm;
	memset(&actionAlarm, 0, sizeof(struct sigaction));
	actionAlarm.sa_handler = sigAlrmHandler;
	sigaction(SIGALRM, &actionAlarm, NULL);

	signal(SIGKILL, SIG_IGN);

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
	
	for (;;) {
		pause();  // Will exit each time a signal is handled
	}

	return 0;
}