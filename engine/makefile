CC = gcc
CFLAGS = -Wall -g

main: main.o
	$(CC) $(CFLAGS) -o main main.o

main.o: main
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -rf main test main.o