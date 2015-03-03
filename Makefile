CC=gcc
CFLAGS=-I.  -Wall -g
OMPFLAGS = -fopenmp
OMPLIBS = -lgomp
OMP_DEPS = ompSenseBarr.h ompTreeBarr.h

ompSenseBarr.o: ompSenseBarr.c
	$(CC) -c $(CFLAGS) $(OMPFLAGS) $< -o $@

mpiBroadcastBarr.o: mpiBroadcastBarr.c
	mpicc -c $(CFLAGS) $< -o $@

ompTest: ompSenseBarr.o ompTest.c
	gcc -o $@ $^ $(CFLAGS) $(OMPFLAGS) $(OMPLIBS)

mpiTest: mpiBroadcastBarr.o mpiTest.c
	mpicc -o $@ $^ $(CFLAGS)

all: ompSenseBarr.o mpiBroadcastBarr.o ompTest mpiTest

.PHONY: clean

clean :
	rm *.o 
