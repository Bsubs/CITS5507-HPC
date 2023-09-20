#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>

#include "fish.h"
#include "sequential.h"
#include "parallel_functions.h"

/**
 * This will investigate the results of using tasks, taskloop and sections
 * Average time will be taken over 10 runs
 * Threads: 16
 * Num steps: 10,000
 * Num fish:  10,000
*/
int main(int argc, char *argv[]) {
    int numfish = 10000;
    int numsteps = 10000;
    srand(time(NULL));

    // Using taskloop
    double totalTime = 0;
    for(int j = 0; j < 3; j++){
        double start = omp_get_wtime();
        Fish* fishArray1 = initializeFish(numfish);

        parallelTaskloop(fishArray1, numfish, numsteps);
        free(fishArray1);
        double end = omp_get_wtime();
        double timeElapsed = end - start;
        totalTime += timeElapsed;
    }
    totalTime = totalTime / 3; 
    printf("Average time for taskloop: %10.6f\n", totalTime );
    
    // Using tasks
    totalTime = 0;
    for(int j = 0; j < 3; j++){
        double start = omp_get_wtime();
        Fish* fishArray1 = initializeFish(numfish);

        parallelTasks(fishArray1, numfish, numsteps);
        free(fishArray1);
        double end = omp_get_wtime();
        double timeElapsed = end - start;
        totalTime += timeElapsed;
    }
    totalTime = totalTime / 3; 
    printf("Average time for tasks: %10.6f\n", totalTime );

    // Using sections
    totalTime = 0;
    for(int j = 0; j < 3; j++){
        double start = omp_get_wtime();
        Fish* fishArray1 = initializeFish(numfish);

        parallelSections(fishArray1, numfish, numsteps);
        free(fishArray1);
        double end = omp_get_wtime();
        double timeElapsed = end - start;
        totalTime += timeElapsed;
    }
    totalTime = totalTime / 3; 
    printf("Average time for sections: %10.6f\n", totalTime );
    
}