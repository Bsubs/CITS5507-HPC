#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>

#include "fish.h"
#include "sequential.h"
#include "parallel_functions.h"

/**
 * This will investigate the results of changing the number of threads on performance
 * Average time will be taken over 10 runs
 * Threads: 1 , 2, 4, 8, 16, 32
 * Num steps: 10,000
 * Num fish:  10,000
*/
int main(int argc, char *argv[]) {
    int numfish = 10000;
    int numsteps = 10000;
    double totalTime = 0;
    for(int i = 0; i < 10; i++){
        // Run parallel for code
        double start = omp_get_wtime();

        srand(time(NULL));
        Fish* fishArray1 = initializeFish(numfish);
        parallelForReduction(fishArray1, numfish, numsteps);
        // Remember to free
        free(fishArray1);
        double end = omp_get_wtime();
        double timeElapsed = end - start;
        totalTime += timeElapsed;

    }
    totalTime = totalTime / 10; 
    printf("Average time for parallel_for elapsed: %10.6f\n",totalTime );
}