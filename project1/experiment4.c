/**
 * Author: Joo Kai TAY (22489437)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>

#include "fish.h"
#include "sequential.h"
#include "parallel_functions.h"

/**
 * This will investigate the results of changing the schedule type on performance
 * Average time will be taken over 5 runs
 * Threads: 4
 * Num steps: 10,000
 * Num fish:  10,000
*/
int main(int argc, char *argv[]) {
    int numfish = 10000;
    int numsteps = 10000;
    srand(time(NULL));

    char* scheduleType[] = {"STATIC", "DYNAMIC", "GUIDED", "RUNTIME"};

    for(int i =0; i < 4; i++) {
        double totalTime = 0;
        for(int j = 0; j < 5; j++){
            double start = omp_get_wtime();
            Fish* fishArray1 = initializeFish(numfish);

            parallelSchedule(fishArray1, scheduleType[i], numfish, numsteps);
            free(fishArray1);
            double end = omp_get_wtime();
            double timeElapsed = end - start;
            totalTime += timeElapsed;
        }
        totalTime = totalTime / 5; 
        printf("Average time for %s schedule: %10.6f\n", scheduleType[i], totalTime );
    }
}