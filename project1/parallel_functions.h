#ifndef PARALLEL_FUNC
#define PARALLEL_FUNC
#include "fish.h"

/**
 * Author: Joo Kai TAY (22489437)
*/

void parallelReduction(Fish* fishArray, int numfish, int numsteps);
void parallelReductionCondensed(Fish* fishArray, int numfish, int numsteps);
void parallelSchedule(Fish* fishArray, char* scheduleType, int numfish, int numsteps);
void parallelTaskloop(Fish* fishArray, int numfish, int numsteps);
void parallelTasks(Fish* fishArray, int numfish, int numsteps);
void parallelSections(Fish* fishArray, int numfish, int numsteps);

#endif