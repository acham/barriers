#ifndef __MPIBROADCASTBARR_H
#define __MPIBROADCASTBARR_H

#include <stdio.h>
#include <stdlib.h>

extern int numtasks;
extern int rank;
//the variable below can be used by the application to determine whether barrier as been reached
extern int final_var;
extern int sense;

void mpiBcastBarrier();
int get_final_var();

#endif
