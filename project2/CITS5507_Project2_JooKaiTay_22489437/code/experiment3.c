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
 * This will investigate numfish on sequential code
 * Threads: 4
 * Num steps: 10000, 100000, 1000000, 10000000
 * Num fish:  2000
*/
int main(int argc, char *argv[]) {
    int numfish[] = {10000, 100000, 1000000, 10000000};
    int numsteps = 2000;
    srand(time(NULL));

    for(int i = 0; i < 4; i++){
        double start = omp_get_wtime();
        Fish* fishArray1 = initializeFish(numfish[i]);
        sequential(fishArray1, numfish[i], numsteps);
        // Remember to free
        free(fishArray1);
        double end = omp_get_wtime();
        double timeElapsed = end - start;
        
        printf("Time for Sequential with %d fish: %10.6f\n", numfish[i], timeElapsed);

    }

}