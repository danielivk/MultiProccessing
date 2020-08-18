
CC = gcc
CFLAGS  = -Wall

all: mystrdiff multistrdiff

mystrdiff:  mystrdiff.o mystrlib.o
	$(CC) $(CFLAGS) -o mystrdiff mystrdiff.o mystrlib.o

multistrdiff:  multistrdiff.o mystrlib.o
	$(CC) $(CFLAGS) -o multistrdiff multistrdiff.o mystrlib.o

mystrdiff.o:  mystrdiff.c mystrlib.h
	$(CC) $(CFLAGS) -c mystrdiff.c

mystrlib.o:  mystrlib.c mystrlib.h 
	$(CC) $(CFLAGS) -c mystrlib.c

zip:
	zip strdiff.zip makefile mystrlib.[ch] mystrdiff.c multistrdiff.c

clean: 
	rm -f mystrdiff multistrdiff *.o


