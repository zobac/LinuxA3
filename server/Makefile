# make for assignment3

CC=gcc
CFLAGS=-Wall -W -pedantic -pthread

all: server.o wrappers.o serverMain.o
	$(CC) $(CFLAGS) server.o wrappers.o serverMain.o -o server
	
clean:
	rm *.o server
