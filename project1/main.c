#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>

#include "fish.h"
#include "sequential.h"
#include "omp_parallel_for.h"
#include "omp_parallel_for_schedule.h"

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

    // Run static code
    start = omp_get_wtime();

    srand(time(NULL));
    Fish* fishArray2 = initializeFish();
    char *staticParallel = (char *)malloc(strlen("STATIC") + 1);
    strcpy(staticParallel, "STATIC");
    parallelForSchedule(fishArray2, staticParallel);
    // Remember to free
    free(fishArray2);
    free(staticParallel);
    end = omp_get_wtime();
    timeElapsed = end - start;
    printf("Total time for static_parallel_for elapsed: %10.6f\n",timeElapsed );

    // Run dynamic code
    start = omp_get_wtime();

    srand(time(NULL));
    Fish* fishArray3 = initializeFish();
    char *dynamicParallel = (char *)malloc(strlen("DYNAMIC") + 1);
    strcpy(dynamicParallel, "DYNAMIC");
    parallelForSchedule(fishArray3, dynamicParallel);
    // Remember to free
    free(fishArray3);
    free(dynamicParallel);
    end = omp_get_wtime();
    timeElapsed = end - start;
    printf("Total time for dynamic_parallel_for elapsed: %10.6f\n",timeElapsed );

    // Run guided code
    start = omp_get_wtime();

    srand(time(NULL));
    Fish* fishArray4 = initializeFish();
    char *guidedParallel = (char *)malloc(strlen("GUIDED") + 1);
    strcpy(guidedParallel, "GUIDED");
    parallelForSchedule(fishArray4, guidedParallel);
    // Remember to free
    free(fishArray4);
    free(guidedParallel);
    end = omp_get_wtime();
    timeElapsed = end - start;
    printf("Total time for guided_parallel_for elapsed: %10.6f\n",timeElapsed );


}