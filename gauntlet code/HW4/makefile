all: default

default: game.o init.o
	gcc $^ -g -o HW4
	rm -f *.o

%.o: %.c structs.h funcs.h
	gcc $< -c -g -o $@

clean:
	rm -f *.o HW4
