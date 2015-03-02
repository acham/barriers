#ifndef __OMPSENSEBARR_H
#define __OMPSENSEBARR_H

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

extern int sense;
extern int next_sense_target;
extern int count;
extern int num_threads;

void senseBarrier();

#endif
