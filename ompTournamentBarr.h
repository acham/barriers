#ifndef __OMPSENSEBARR_H
#define __OMPSENSEBARR_H

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

//sense variable. can be only 0 or 1.
struct round_struct {
	int role;
	int vpid;
	int tb_round;
	bool *opponent;
	bool flag;
};
typedef struct round_struct round_struct;
round_struct array[1000][100];
extern int counter;
extern int rounds ;

//extern int sense;
//this variable indicates the next sense value that will allow a pass-through
//extern int count;
extern int num_threads;
extern int initialized;

void ompTournamentBarrier();

void initialize_tournament_barr();

#endif
