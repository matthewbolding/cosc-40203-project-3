## Matthew Bolding
## Operating Systems 40203 Spring 2022

CC = gcc
RM = /bin/rm
RMFLAGS = -f
PTHREAD = -lpthread
GDB = -g
MATH = -lm

all: cfwin.o cfwin numbers.o numbers threadarray.o threadarray

# cfwin
cfwin.o: cfwin.c
	$(CC) -o cfwin.o -c $< $(GDB)

cfwin: cfwin.o
	$(CC) -o cfwin $< $(PTHREAD) $(GDB)

# numbers
numbers.o: numbers.c
	$(CC) -o numbers.o -c $< $(GDB)

numbers: numbers.o
	$(CC) -o numbers $< $(PTHREAD) $(MATH) $(GDB)

# threadarray
threadarray.o: threadarray.c
	$(CC) -o threadarray.o -c $< $(GDB)

threadarray: threadarray.o
	$(CC) -o threadarray $< $(PTHREAD) $(GDB)

# clean
clean:
	$(RM) $(RMFLAGS) *.o cfwin numbers threadarray