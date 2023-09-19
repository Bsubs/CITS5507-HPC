#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>

#include "fish.h"
#include "sequential.h"
#include "parallel_functions.h"

/**
 * This will investigate the results of changing the number of steps on performance
 * Average time will be taken over 10 runs
 * Threads: 16
 * Num steps: 10,000
 * Num fish:  10,000
*/
int main(int argc, char *argv[]) {
    int numfish = 10000;
    int numsteps = 10000;
    srand(time(NULL));

    char* scheduleType[] = {"STATIC", "DYNAMIC", "GUIDED"};

    for(int i =0; i < 3; i++) {
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