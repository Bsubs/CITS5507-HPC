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
 * This will investigate the impact of removing implicit barriers on parallel performance
 * Average time will be taken over 5 runs
 * Threads: 4
 * Num steps: 10,000
 * Num fish:  10,000
*/
int main(int argc, char *argv[]) {
    int numfish = 10000;
    int numsteps = 10000;
    double totalTime = 0;
    
    // Run sequentialCondensed code
    for(int i = 0; i < 5; i++){
        double start = omp_get_wtime();

        srand(time(NULL));
        Fish* fishArray1 = initializeFish(numfish);
        sequentialCondensed(fishArray1, numfish, numsteps);
        // Remember to free
        free(fishArray1);
        double end = omp_get_wtime();
        double timeElapsed = end - start;
        totalTime += timeElapsed;

    }
    totalTime = totalTime / 5; 
    printf("Average time for sequentialCondensed elapsed: %10.6f\n",totalTime );

    // Run sequential
    totalTime = 0;
    for(int i = 0; i < 5; i++){
        // Run parallel for code
        double start = omp_get_wtime();

        srand(time(NULL));
        Fish* fishArray1 = initializeFish(numfish);
        sequential(fishArray1, numfish, numsteps);
        // Remember to free
        free(fishArray1);
        double end = omp_get_wtime();
        double timeElapsed = end - start;
        totalTime += timeElapsed;

    }
    totalTime = totalTime / 5; 
    printf("Average time for sequential elapsed: %10.6f\n",totalTime );

    // Run parallelReductionOld
    totalTime = 0;
    for(int i = 0; i < 5; i++){
        // Run parallel for code
        double start = omp_get_wtime();

        srand(time(NULL));
        Fish* fishArray1 = initializeFish(numfish);
        parallelReductionOld(fishArray1, numfish, numsteps);
        // Remember to free
        free(fishArray1);
        double end = omp_get_wtime();
        double timeElapsed = end - start;
        totalTime += timeElapsed;

    }
    totalTime = totalTime / 5; 
    printf("Average time for parallelReductionOld elapsed: %10.6f\n",totalTime );

    // Run parallelReduction
    totalTime = 0;
    for(int i = 0; i < 5; i++){
        // Run parallel for code
        double start = omp_get_wtime();

        srand(time(NULL));
        Fish* fishArray1 = initializeFish(numfish);
        parallelReduction(fishArray1, numfish, numsteps);
        // Remember to free
        free(fishArray1);
        double end = omp_get_wtime();
        double timeElapsed = end - start;
        totalTime += timeElapsed;

    }
    totalTime = totalTime / 5; 
    printf("Average time for parallelReduction elapsed: %10.6f\n",totalTime );
}