#include <stdio.h>
#include "omp.h"
#include "ompSenseBarr.h"

//assume the code below is executed in a parallel section
int initialized = 0;
int sense, next_sense_target, count, num_threads;

void ompSenseBarrier()
{
    if (initialized == 0)
        initialize_sense_barr();
    int local_sense = sense;
#pragma omp atomic
    count--;
    if (count == 0) {//reverse sense
#pragma omp critical
        if (local_sense == 1)
            sense = 0;
        else sense = 1;
    }
    else {//wait on sense reversal
        while (local_sense == sense);
    }
    return;    
    //num_threads = omp_get_num_threads();
    //count = num_threads;
}

/* Help function */

void initialize_sense_barr()
{
    sense = 0;
    num_threads = omp_get_num_threads();
    count = num_threads;
    initialized = 1;
#ifdef DEBUG
    printf("thread: %d initialized barrier", omp_get_thread_num());
#endif
}
