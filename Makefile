CC=gcc
CFLAGS=-Iinclude -Wall -pthread

all: main

main: src/main.c src/rtos.c
	$(CC) $(CFLAGS) src/main.c src/rtos.c -o main

clean:
	rm -f main
