#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>

// SUMMARY
//
// This demo begins a shutdown procedure once SIGTERM is detected.
// We'll use alarm(1) to print a shutdown progress message every second.
//
// See more details about signals using:
//    man 7 signal

// COMPILE:
//   gcc -o sig05 sig05.c
//
// RUN:
//   ./sig05

// volatile tells the compiler's optimizer not to
// eliminate reads or writes from/to this variable,
// as it is changed asynchronously.
volatile bool done = false;

bool term = false;
int tcnt = 5;

void sigIntHandler(int signum) {
	puts(" SIGINT ignored");
}

void sigTermHandler(int signum) {
	puts("SIGTERM detected");
	if (!term) {
		term = true;
		puts("Terminating...");
		alarm(1);
	}
}

void sigAlrmHandler(int signum) {
	puts("SIGALRM detected");
	if (tcnt > 0) {
		printf(":: %d ::\n", tcnt);
		tcnt--;
		alarm(1);
	} else {
		done = true;
	}
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
	
	puts("");
	puts("Hit CTRL-C to send SIGINT  [IGNORED]");
	puts("  or");
	printf("Run \"kill %d\" in another terminal to send SIGTERM  [START SHUTDOWN]\n", getpid());
	puts("");

	printf("Run \"kill -USR1 %d\" in another terminal to send SIGUSR1\n", getpid());
	puts("");
	
	while (!done) {
		pause();
	}

	return 0;
}










