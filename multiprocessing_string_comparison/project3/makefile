
CC = gcc
CFLAGS  = -Wall

all: multistrdiff

multistrdiff:  multistrdiff.o mystrlib.o
	$(CC) $(CFLAGS) -o multistrdiff multistrdiff.o mystrlib.o


mystrlib.o:  mystrlib.c mystrlib.h 
	$(CC) $(CFLAGS) -c mystrlib.c

zip:
	zip strdiff.zip makefile mystrlib.[ch] mystrdiff.c multistrdiff.c

clean: 
	rm -f mystrdiff multistrdiff *.o


