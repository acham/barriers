CC=gcc
CFLAGS=-I.  -Wall -g
OMPFLAGS = -fopenmp
OMPLIBS = -lgomp
OMP_DEPS = ompSenseBarr.h ompTreeBarr.h ompTournamentBarr.h
LIBS = -lm

ompSenseBarr.o: ompSenseBarr.c
	$(CC) -c $(CFLAGS) $(OMPFLAGS) $< -o $@

ompTournamentBarr.o: ompTournamentBarr.c
	$(CC) -c $(CFLAGS) $(OMPFLAGS) $< -o $@ $(LIBS)

mpiBroadcastBarr.o: mpiBroadcastBarr.c
	mpicc -c $(CFLAGS) $< -o $@

ompTest: ompSenseBarr.o  ompTournamentBarr.o ompTest.c
	gcc -o $@ $^ $(CFLAGS) $(OMPFLAGS) $(OMPLIBS)

mpiTest: mpiBroadcastBarr.o mpiTest.c
	mpicc -o $@ $^ $(CFLAGS)

all: ompSenseBarr.o  ompTournamentBarr.o mpiBroadcastBarr.o ompTest mpiTest

.PHONY: clean

clean :
	rm *.o 
