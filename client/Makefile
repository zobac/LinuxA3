# make for assignment3

CC=gcc
CFLAGS=-Wall -W -pedantic -pthread

all: client.o wrappers.o clientMain.o
	$(CC) $(CFLAGS) client.o clientMain.o wrappers.o -o client

clean:
	rm *.o client
