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
#define winner 0
#define loser 1
#define champion 2

static int NUM_THREADS;

static bool sense;
static bool initialized = 0;

static int rounds = 0;

typedef struct _round_struct {
	int role;
	int vpid;
	//int tb_round;
	//bool opponent;
	//int opponent;
	bool flag;
} round_struct;

static round_struct array[32][5];

static void initialize_tournament_barr();

void ompTournamentBarrier()
{
    if (initialized == 0) 
        initialize_tournament_barr();
    
    int vpid= omp_get_thread_num();
        
	int round = 0;
	int com, com_second=0;
	for ( round = 0 ; round < rounds; round++ )
	{
		com = ceil( pow(2,round) );
	        com_second = ceil( pow(2,round-1) );
		if(array[vpid][round].role == loser){
			( array[vpid+com_second][round] ).flag = sense;
			while( array[vpid][round].flag != sense );
			
			break;
		}

		if( array[vpid][round].role == winner ) {
			while( array[vpid][round].flag != sense );
			
		}

		if( array[vpid][round].role == champion ){
                        
			while( array[vpid][round].flag != sense );
		         array[vpid+com_second][round].flag = sense;
			break;
		}

		//i=1;
	}

	//wake up
	for (round = rounds - 1; round >= 0; round--)
	{
		

		if( array[vpid][round].role == winner )
			( array[vpid+round][round] ).flag = sense;
			break;
		
	}

	sense = !sense;
    
}

/* Help function */

 static void initialize_tournament_barr()
{ 
   //vpid = omp_get_thread_num();
    sense = true;

    NUM_THREADS = omp_get_num_threads();
    
    rounds = ceil( log2(NUM_THREADS) );
	//array = malloc(rounds * sizeof(*round_struct));
    //int k;
    //for (k=0; k < rounds; k++){
    //    array[k] = malloc(rounds * sizeof(round_struct))
    
    //array[2][
	
	int j,k,l;
	for(j=0;j<NUM_THREADS;j++) {
		for(k=0;k<=rounds;k++) {
			array[j][k].flag = false;
			array[j][k].role = -1;
			//array[j][k].opponent = -1;
            //array[j][k].opponent = false;
		}
	}

	int comp, comp_second=0;

	for( l=0 ; l<NUM_THREADS; l++) {
		for(k=0;k<=rounds;k++) {
			comp = ceil( pow(2,k) );
			comp_second = ceil( pow(2,k-1) );

			if((k > 0) && (l%comp==0) && (comp < NUM_THREADS)){
				array[l][k].role = winner;
			}


			if((k > 0) && ((l%comp == comp_second))){
				array[l][k].role = loser;
			}

           
			if((k > 0) && (l==0) && (comp >= NUM_THREADS)){
				array[l][k].role = champion;
			}

		}
	}

  initialized = 1;
#ifdef DEBUG
    printf("thread: %d initialized barrier", omp_get_thread_num());
#endif
}
