#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>

#include "fish.h"
#include "sequential.h"
#include "parallel_functions.h"

/**
 * This will investigate the results of changing the number of fish on performance
 * Average time will be taken over 10 runs
 * Threads: 16
 * Num steps: 10,000
 * Num fish:  5000, 10000, 15000, 20000, 40000, 60000, 80000, 100000
*/
int main(int argc, char *argv[]) {
    int numsteps = 10000;
    int numFishArray[] = {5000, 10000, 15000, 20000, 40000, 60000, 80000, 100000};
    srand(time(NULL));
    for(int i = 0; i < 8; i++){
        double totalTime = 0;
        for(int j = 0; j < 3; j++){
            // Run parallel for code
            double start = omp_get_wtime();

            Fish* fishArray1 = initializeFish(numFishArray[i]);
            parallelReduction(fishArray1, numFishArray[i], numsteps);
            // Remember to free
            free(fishArray1);
            double end = omp_get_wtime();
            double timeElapsed = end - start;
            totalTime += timeElapsed;

        }
        totalTime = totalTime / 3; 
        printf("Average time for %d fish elapsed: %10.6f\n",numFishArray[i], totalTime );
    }
}