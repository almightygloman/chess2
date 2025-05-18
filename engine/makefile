CC = gcc
CFLAGS = -Wall -g

main: main.o
	$(CC) $(CFLAGS) -o main main.o

main.o: main
	$(CC) $(CFLAGS) -c main.c

test: test.o
	$(CC) $(CFLAGS) -o test test.o

test.o: test
	$(CC) $(CFLAGS) -c test.c

clean:
	rm -rf main main.o test test.o