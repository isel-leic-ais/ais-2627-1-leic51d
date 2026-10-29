#include <unistd.h>
#include <stdio.h>

// SUMMARY
//
// Signals allow delivering asynchronously notifications to processes.
// This mechanism has noticeable similarities with interrupt signals on
// CPUs.
//
// Signals are numbered (numbers 1..31 are typically used) and each
// signal has a predefined meaning. There is also a default behaviour
// (called "disposition") for each signal. A few signals are ignored by
// default, but most of them will terminate the process.
//
// This demo shows a program that invites you to terminate it using 
// CTRL-C, which delivers an INTerrupt signal (SIGINT), or using an
// explicit kill command, which sends a TERMinate signal (SIGTERM) by
// default.
//
// The program halts its execution using the pause() function, that
// blocks execution until a signal is delivered to the process.
//
// See more details about signals using:
//    man 7 signal

// COMPILE:
//   gcc -o sig01 sig01.c
//
// RUN:
//   ./sig01

int main() {

	puts("");
	puts("Hit CTRL-C to send SIGINT");
	puts("  or");
	printf("Run \"kill %d\" in another terminal to send SIGTERM\n", getpid());
	puts("");
	
	pause();

	return 0;
}