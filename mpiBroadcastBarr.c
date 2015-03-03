#include <stdio.h>
#include "mpi.h"
#include "mpiBroadcastBarr.h"

#define DEBUG 1

//we are only letting sense be 1 or 2
//sense will correspond to the message being sent during a certain phase by all procs, and then be switched
int numtasks, rank;
int final_var = 0;

//static func declaration
static void initialize_bcast_barr();

void mpiBcastBarrier()
{
    initialize_bcast_barr();
    //send buffer: message value based on rank
    int msg;
    int i;
    //rcv data buffer
    int rcv_msg = 0;
    //broadcast msg
    for (i=0; i<numtasks; i++){
        msg = rank*100;
        MPI_Bcast(&msg, 1, MPI_INT, i, MPI_COMM_WORLD);
#ifdef DEBUG
        printf("[%d]: after Bcast from rank %d, my buffer has value: %d\n", rank, i, msg);
#endif
    }
    //below is used for testing that the barrier has been reached by all procs
    final_var = 1;
    return;
}

static void initialize_bcast_barr()
{
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    final_var = 0;
#ifdef DEBUG
    printf("process rank: %d initialized barrier\n", rank);
#endif
    return;
}

int get_final_var()
{
    return final_var;
}


