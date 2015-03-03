CC=gcc
CFLAGS=-I.  -Wall -g
OMPFLAGS = -fopenmp
OMPLIBS = -lgomp
OMP_DEPS = ompSenseBarr.h ompTreeBarr.h

%Barr.o: %Barr.c
	$(CC) -c $(CFLAGS) $(OMPFLAGS) $< -o $@

ompTest: ompSenseBarr.o ompTest.c
	gcc -o $@ $^ $(CFLAGS) $(OMPFLAGS) $(OMPLIBS)

all: ompSenseBarr.o ompTest

.PHONY: clean

clean :
	rm *.o 
