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
 * Average time will be taken over 5 runs
 * Threads: 4
 * Num steps: 5000, 10000, 15000, 20000, 40000, 60000, 80000, 100000
 * Num fish:  10,000
*/
int main(int argc, char *argv[]) {
    int numfish = 10000;
    int numStepsArray[] = {5000, 10000, 15000, 20000, 40000, 60000, 80000, 100000};
    srand(time(NULL));
    for(int i = 0; i < 8; i++){
        double totalTime = 0;
        for(int j = 0; j < 5; j++){
            // Run parallel for code
            double start = omp_get_wtime();

            Fish* fishArray1 = initializeFish(numfish);
            parallelReductionOld(fishArray1, numfish, numStepsArray[i]);
            // Remember to free
            free(fishArray1);
            double end = omp_get_wtime();
            double timeElapsed = end - start;
            totalTime += timeElapsed;

        }
        totalTime = totalTime / 5; 
        printf("Average time for %d steps elapsed: %10.6f\n",numStepsArray[i], totalTime );
    }
}