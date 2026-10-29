// SUMMARY
//
// This minimal x86-64 Linux assembly example issues a sequence of direct
// system calls to create a memory-mapped region and then keep the process
// running while observing its behavior.
//
// COMPILE:
//   make
//
// RUN:
//   ./prog

        .section .rodata
hell:   .byte  47, 101, 116,  99
        .byte  47, 111, 115,  45
        .byte 114, 101, 108, 101
        .byte  97, 115, 101,   0
        .byte  73,  83,  69,  76
        .byte  67,  76+ 6&7, 067

        .section .bss
	.align 4096
dead:   .space 4096

        .text
        .globl _start
_start:
        movq $-100, %rdi
        leaq hell(%rip), %rsi
        xorq %rdx, %rdx
        movq $257, %rax
        syscall

        movq %rax, %r15

        movq %r15, %rdi
        xorq %rsi, %rsi
        xorq %rdx, %rdx
        movq $292, %rax
        syscall

        movq %r15, %rdi
        movq $3, %rax
        syscall

        xorq %rdi, %rdi
        leaq dead(%rip), %rsi
        movq $4096, %rdx
        movq $0, %rax
        syscall

        movq $1, %rdi
        leaq dead(%rip), %rsi
        movq %rax, %rdx
        movq $1, %rax
        syscall

stall:
	movq $34, %rax
	syscall
	jmp stall

        xorq %rdi, %rdi
        movq $60, %rax
        syscall

        .end
