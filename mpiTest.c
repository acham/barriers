#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "mpi.h"
#include "mpiBroadcastBarr.h"

int main(int argc, char **argv)
{
  int myrank;
  int i, j;
  long x;
  int my_final_var;
  //Error checking
  if (argc != 2){
      fprintf(stderr, "Error. Usage: ompTest [barrier-type]\n"
                      " [barrier-type]: 0 = no barrier, 1 = broadcast barrier, "
                      "2 = tournament barrier\n");
      exit(1);
  }
  int barrType = atoi(argv[1]);
  if (barrType < 0 || barrType > 2){
      fprintf(stderr, "Error: barrier type out of range.\n");
      exit(1);
  }

  /*seed random number - only used for testing whether barrier works, 
  not for performance test*/
  srand(time(NULL));
  
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  /*check if number of procs is a power of two when tournament barrier is selected
  if not: error and exit */
  int nprocs;
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
  int nrounds = isPowerOfTwo(nprocs);
  if (nrounds < 0 && barrType){//not a power of two: error
    fprintf(stderr, "error: tournament barrier selected with num procs not a power of 2.\n");
    exit(1);
  }
  
  //create index for work loop
  int maxInd = (rand() % 3 + 1) * myrank * 100;
  printf("random quantity work loop starting for thread %d...\n", myrank);
  //start work
  for (i = 1; i <= maxInd; ++i)
  {
    long y = 1;
    for (j= 0; j < maxInd; j++)
    {
        y = y * 40000;
        y = y / 40000;
        y++;
    }
    x += i;
  } //end work
  my_final_var = get_final_var();
  printf("[%d]: work completed, with my_final_var = %d\n", myrank, my_final_var);

  //First, call the barrier, with type defined by user as command-line argument
  if (barrType == 1)
      mpiBcastBarrier();
  else if (barrType == 2)
      mpiTournBarrier();
  //else: no barrier
  //Print the final value of the shared variable, according to each thread
  my_final_var = get_final_var();
  
  printf("[%d]: post-barrier value of my_final_var: %d\n", myrank, my_final_var);

  MPI_Finalize();
  return 0;
}

