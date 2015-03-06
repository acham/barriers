CC=gcc
CFLAGS=-I.  -Wall -g
OMPFLAGS = -fopenmp
OMPLIBS = -lgomp
OMP_DEPS = ompSenseBarr.h ompTournamentBarr.h


ompSenseBarr.o: ompSenseBarr.c
	$(CC) -c $(CFLAGS) $(OMPFLAGS) $< -o $@

ompTournamentBarr.o: ompTournamentBarr.c
	$(CC) -c $(CFLAGS) $(OMPFLAGS) $< -o $@ 

#mpiBroadcastBarr.o: mpiBroadcastBarr.c
#	mpicc -c $(CFLAGS) $< -o $@

ompTest: ompSenseBarr.o  ompTournamentBarr.o ompTest.c
	gcc -o $@ $^ $(CFLAGS) $(OMPFLAGS) $(OMPLIBS)     -lm

#mpiTest: mpiBroadcastBarr.o mpiTest.c
#	mpicc -o $@ $^ $(CFLAGS)             

all: ompSenseBarr.o  ompTournamentBarr.o ompTest 
#mpiTest

.PHONY: clean

clean :
	rm *.o 
