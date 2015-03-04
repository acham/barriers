#include <stdio.h>
#include "mpi.h"
#include "mpiBroadcastBarr.h"

#define DEBUG 1

//we are only letting sense be 1 or 2
//sense will correspond to the message being sent during a certain phase by all procs, and then be switched
static int numtasks, rank;
static int final_var = 0;
static int sense = 0;

//static func declaration
static void initialize_bcast_barr();

//func definitions
void mpiBcastBarrier()
{
    initialize_bcast_barr();
    //send buffer: message value based on rank
    int msg = 1;
    int i;
    //rcv data buffer
    int rcvBuff[numtasks];
    //set my rcv message value to -1
    rcvBuff[rank] = -1;
    MPI_Request snd_rqst;
    MPI_Status rcv_status;
    //broadcast msg
    for (i=0; i<numtasks; i++){
        if (i == rank) continue;
        msg = rank*100;
        /*non-blocking sends on all other procs
        use SENSE as TAG */
        int res = MPI_Isend(&msg, 1, MPI_INT, i, sense, MPI_COMM_WORLD, &snd_rqst);
        //error-checking?
    }
#ifdef DEBUG
    printf("[%d]: all non-blocking sends completed\n", rank);
#endif
    //blocking receives from all procs
    for (i=0; i<numtasks; i++){
        if (i == rank) continue;
        MPI_Recv(&rcvBuff[i], 1, MPI_INT, i, sense, MPI_COMM_WORLD, &rcv_status);
    }
#ifdef DEBUG
    int l;
    printf("[%d]: all blocking receives completed\n", rank);
    printf("[%d]: contents of rcv buff: ", rank);
    for(l=0; l<numtasks; l++) printf("%d ", rcvBuff[l]);
    printf("\n");
#endif
    /* reverse sense variable */
    if (sense == 1) sense = 0;
    else sense = 1;
    final_var = 1;
    //below is used for testing that the barrier has been reached by all procs
    return;
}

static void initialize_bcast_barr()
{
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    final_var = 0;
#ifdef DEBUG
    printf("[%d] initialized barrier\n", rank);
#endif
    return;
}

int get_final_var()
{
    return final_var;
}


