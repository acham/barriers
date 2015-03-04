#include <stdio.h>
#include "mpi.h"
#include "mpiTournamentBarr.h"

#define DEBUG 1

//we are only letting sense be 1 or 2
//sense will correspond to the message being sent during a certain phase by all procs, and then be switched
static int numtasks, numrounds, rank;
static int final_var = 0;
static int sense = 0;
static int numrounds;

//static func declaration
static void initialize_tourn_barr();

//func definitions
void mpiTournBarrier()
{
    initialize_tourn_barr();
    

    return;
}

static void initialize_tourn_barr()
{
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    final_var = 0;
#ifdef DEBUG
    printf("[%d] initialized barrier\n", rank);
#endif
    numrounds = isPowerOfTwo(numtasks);
    return;
}

int get_final_var()
{
    return final_var;
}

int isPowerOfTwo (int x)
{
    int count = 0;
    while (x > 1 && (x % 2) == 0){
        x = x/2;
        count++;
    }
    if (x == 1) return count;
    else return -1;
}

int get_final_var()
{
    return final_var;
}

