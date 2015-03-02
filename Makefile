CC=gcc
CFLAGS=-I.  -Wall -g
OMPFLAGS = -fopenmp
OMPLIBS = -lgomp
OMP_DEPS = ompSenseBarr.h ompTreeBarr.h

ompSenseBarr.o: ompSenseBarr.c
	$(CC) -c $(CFLAGS) $< -o $@

ompTest: ompSenseBarr.o ompTest.c
	gcc -o $@ $^ $(CFLAGS) $(OMPFLAGS) $(OMPLIBS)

all: ompSenseBarr.o ompTest

.PHONY: clean

clean :
	rm *.o 
