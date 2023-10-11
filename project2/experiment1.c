#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#include <mpi.h>
#include <stddef.h>
#include "fish.h"
#include <time.h>

/**
 * Experiment 1: Sequential Code with MPI
 * This experiment expands on the best sequential function from project 1
 * Uses MPI to divide the fishArray among the processes
*/
int main(int argc, char* argv[]) {
    // Initialize params
    int numfish = 1000000;
    int numsteps = 1000;
    Fish *fishArray;
    int rank, size;
    srand(time(NULL));

    // Initialize MPI
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Create the MPI_FISH type for sending fish
    MPI_Datatype MPI_FISH = create_mpi_fish_datatype();

    // Start timer
    double start;
    if (rank == 0){
        start = omp_get_wtime();
    }

    // Initialize fishArray in master
    if(rank == 0){
        // When do we scatter and gather
        fishArray = initializeFish(numfish);
    }

    // Prepare division & array for scatter in loop
    int fish_per_process = numfish / size;
    Fish* localFishArray = malloc(fish_per_process * sizeof(Fish));

    // Loop for number of steps
    for(int i = 0; i < numsteps; i++){
        double maxDiff = 0;
        double localMaxDiff = 0;
        double sumOfProduct = 0;
        double sumOfDistance = 0;

        // Initial scatter
        MPI_Scatter(fishArray, fish_per_process, MPI_FISH, localFishArray, fish_per_process, MPI_FISH, 0, MPI_COMM_WORLD);

        // Loops through local fish array chunk and finds maxDiff in the current round
        for(int j = 0; j < fish_per_process; j++) {
            double dist = distance(localFishArray[j].x_c, localFishArray[j].y_c) - localFishArray[j].euclDist;
            if(dist > localMaxDiff) {localMaxDiff = dist;}
        }

        // Use global reduction to get max diff
        MPI_Allreduce(&localMaxDiff, &maxDiff, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);

        // Loops through local fish array chunk and performs eat & swim operations
        for(int j = 0; j < fish_per_process; j++){
            eat(&localFishArray[j], maxDiff, i);
            swim(&localFishArray[j]);
        }

        // Loops through local fish array chunk and accumulates variables for barycentre
        double localSumOfProduct = 0;
        double localSumOfDistance = 0;
        for(int j = 0; j < fish_per_process; j++){
            localSumOfProduct += localFishArray[j].euclDist * localFishArray[j].weight_p;
            localSumOfDistance += localFishArray[j].euclDist;
        }

        // Compute global sumOfProduct and sumOfDistance
        MPI_Allreduce(&localSumOfProduct, &sumOfProduct, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
        MPI_Allreduce(&localSumOfDistance, &sumOfDistance, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

        // Gather fish back
        MPI_Gather(localFishArray, fish_per_process, MPI_FISH, fishArray, fish_per_process, MPI_FISH, 0, MPI_COMM_WORLD);

        // Compute barycentre in master
        if(rank == 0) {
            double barycentre = sumOfProduct / sumOfDistance;
        }
    }

    // Get time, free arrays, free MPI_FISH
    if (rank == 0){
        free(fishArray);
        free(localFishArray);
        free(MPI_FISH);
        double end = omp_get_wtime();
        double timeElapsed = end - start;
        printf("Average time for MPI elapsed: %10.6f\n",timeElapsed );
    }

    MPI_Finalize();
    return 0;
}