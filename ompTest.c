#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "ompSenseBarr.h"

int main(int argc, char **argv)
{
  senseBarrier();
  int i, j;
  long x = 1;
  omp_set_dynamic(0);
  //Error checking and set num threads from cmd line argument
  if (argc != 3){
      fprintf(stderr, "Error. Usage: ompTest [num-threads] [barrier-type]\n");
      exit(1);
  }
  int numT = atoi(argv[1]);
  if (numT < 1 || numT > 200){
      fprintf(stderr, "Error: number of threads must be between 1 and 200.\n");
      exit(1);
  }
  omp_set_num_threads(numT);
  //seed random number
  srand(time(NULL));

#pragma omp parallel shared(x) private(i,j) 
  {
  int tid = omp_get_thread_num();
  int maxInd = rand() % 3 * tid * 100;
  printf("random quantity work loop starting for thread %d...\n", tid);
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
#pragma omp atomic
    x += i;
    if (omp_get_thread_num() == 0 && i == 1)
        printf("Number of threads = %d\n", omp_get_num_threads());
  } //end work
  printf("Work completed for thread: %d\n", tid);
  //Print the final value of the shared variable, according to each thread
  long fin_val;
#pragma omp critical
  fin_val = x;
  printf("final value of shared variable x according to thread %d: %ld\n", tid, fin_val);
  }

  printf("final value of shared variable x: %ld\n", x);
  return 0;
}

