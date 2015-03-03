#ifndef __OMPSENSEBARR_H
#define __OMPSENSEBARR_H

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

//sense variable. can be only 0 or 1.
extern int sense;
//this variable indicates the next sense value that will allow a pass-through
extern int count;
extern int num_threads;
extern int initialized;

void ompSenseBarrier();
static void initialize_sense_barr();


#endif
