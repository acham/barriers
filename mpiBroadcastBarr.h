#ifndef __OMPSENSEBARR_H
#define __OMPSENSEBARR_H

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

extern int numtasks;
extern int rank;
//the variable below can be used by the application to determine whether barrier as been reached
extern int final_var;

void ompSenseBarrier();
int get_final_var();

#endif
