#ifndef PARALLEL_FUNC
#define PARALLEL_FUNC
#include "fish.h"
#define CHUNKSIZE 5

void parallelForReduction(Fish* fishArray, int numfish, int numsteps);
void parallelForSchedule(Fish* fishArray, char* scheduleType, int numfish, int numsteps);

#endif