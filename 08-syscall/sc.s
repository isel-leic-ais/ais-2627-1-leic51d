// SUMMARY
//
// This tiny assembly program shows how a Linux process can make direct
// system calls without libc. It writes a string to standard output and then
// exits with status 0.
//
// COMPILE:
//   gcc -nostdlib -no-pie -o sc sc.s
//
// RUN:
//   ./sc

	.text
	.global _start
	
_start:
	# write(1, msg, 14);
	movq $14, %rdx         # msg.length
	leaq msg(%rip), %rsi   # msg
	movq $1, %rdi          # stdout
	movq $1, %rax          # system call: write
	syscall

	# exit(0);
	movq $0,  %rdi         # exit code
	movq $60, %rax         # system call: exit
	syscall


msg: .ascii "Hello, world!\n"

	.end
