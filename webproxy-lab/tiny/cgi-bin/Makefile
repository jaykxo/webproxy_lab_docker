CC = gcc
CFLAGS = -O2 -Wall -I ..

all: adder

adder: adder.c ../csapp.c
	$(CC) $(CFLAGS) -o adder adder.c ../csapp.c

clean:
	rm -f adder *~
