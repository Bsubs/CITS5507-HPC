#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#include "fish.h"
#include "sequential.h"
#include "omp_parallel_for.h"

int main(int argc, char *argv[]) {
    // Run sequential code
    double start = omp_get_wtime();

    srand(time(NULL));
    Fish* fishArray = initializeFish();
    sequential(fishArray);
    // Remember to free
    free(fishArray);
    
    double end = omp_get_wtime();
    double timeElapsed = end - start;
    printf("Total time for sequential elapsed: %10.6f\n",timeElapsed );

    // Run parallel for code
    start = omp_get_wtime();

    srand(time(NULL));
    Fish* fishArray1 = initializeFish();
    parallelFor(fishArray1);
    // Remember to free
    free(fishArray1);
    
    end = omp_get_wtime();
    timeElapsed = end - start;
    printf("Total time for parallel_for elapsed: %10.6f\n",timeElapsed );
}