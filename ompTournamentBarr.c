#include <stdio.h>
#include "omp.h"
#include "ompTournamentBarr.h"
#include <stdio.h>
#include <math.h>
#include<stdlib.h>
#include <malloc.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#define rounds_first ceil(log(numprocessors)/log(2)) 
#define rounds1 rounds_first
#define winner 0
#define loser 1
#define bye 2
#define champion 3
#define dropout 4
int NUM_THREADS, NUM_BARRIERS;
//assume the code below is executed in a parallel section
int initialized = 0;
int sense, next_sense_target, count, num_threads;
int counter = 0;
int rounds = 0;
struct round_struct {
	int role;
	int vpid;
	int tb_round;
	bool *opponent;
	bool flag;
};
typedef struct round_struct round_struct;
round_struct array[1000][100];


static void initialize_tournament_barr();


void ompTournamentBarrier()
{initialize_tournament_barr();

  int vpid=0;
		bool *sense;
		bool temp = true;

		#pragma omp critical
 {
                 vpid=1;
		vpid = omp_get_thread_num();
		sense = &temp;
}
	int round = 0;

	while(1) {

		if(array[vpid][round].role == loser){
			*( array[vpid][round] ).opponent = *sense;
			while( array[vpid][round].flag != *sense );
			break;
		}

		if( array[vpid][round].role == winner ) {
			while( array[vpid][round].flag != *sense );
		}

		if( array[vpid][round].role == champion ){
			while( array[vpid][round].flag != *sense );
			*( array[vpid][round] ).opponent = *sense;
			break;
		}

		if(round < rounds)
			round = round + 1;
		//i=1;
	}

	//wake up
	while(1) {
		if( round > 0 )
			round = round - 1;

		if( array[vpid][round].role == winner )
			*( array[vpid][round] ).opponent = *sense;

		if( array[vpid][round].role == dropout )
			break;
	}

	*sense = !*sense;

}

/* Help function */

static void initialize_tournament_barr()
{
    sense = 0;
    num_threads = omp_get_num_threads();
    rounds = ceil( log(NUM_THREADS)/log(2) );
	bool x = false;

		NUM_THREADS = 1;
		NUM_BARRIERS = 1;
	


	 counter = 0;
	 rounds = ceil( log(NUM_THREADS)/log(2) );

	int i,j,k,l;

	for(j=0;j<NUM_THREADS;j++) {
		for(k=0;k<=rounds;k++) {
			array[j][k].flag = false;
			array[j][k].role = -1;
			array[j][k].opponent = &x;
		}
	}

	i=0;
	int temp=0, temp2, g=0, comp, comp_second=0;

	for(l=0 ; l<NUM_THREADS; l++) {
		for(k=0;k<=rounds;k++) {
			temp = k;
			temp2 = l;
			comp = ceil( pow(2,k) );
			comp_second = ceil( pow(2,k-1) );

			if((k > 0) && (l%comp==0) && ((l + (comp_second))< NUM_THREADS) && (comp < NUM_THREADS)){
				array[l][k].role = winner;
			}

			if((k > 0) && (l%comp == 0) && ((l + comp_second)) >= NUM_THREADS){
				array[l][k].role = bye;
			}

			if((k > 0) && ((l%comp == comp_second))){
				array[l][k].role = loser;
			}

			if((k > 0) && (l==0) && (comp >= NUM_THREADS)){
				array[l][k].role = champion;
			}

			if(k==0) {
				array[l][k].role = dropout;
			}

			if(array[l][k].role == loser) {
				array[l][k].opponent = &array[l-comp_second][k].flag;
			}

			if(array[l][k].role == winner || array[l][k].role == champion) {
				array[l][k].opponent = &array[l+comp_second][k].flag;
			}
		}
	}

#ifdef DEBUG
    printf("thread: %d initialized barrier", omp_get_thread_num());
#endif
}
