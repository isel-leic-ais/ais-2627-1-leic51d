.PHONY: all clean

all: prog

prog: prog.o
	ld -o prog prog.o

prog.o: prog.s
	as -o prog.o prog.s

clean:
	rm -f prog.o prog

