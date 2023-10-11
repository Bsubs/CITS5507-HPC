#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#include <mpi.h>
#include <stddef.h>
#include "fish.h"
#include <time.h>

int main(int argc, char* argv[]) {
    int numfish = 1000000;
    int numsteps = 1000;
    Fish *fishArray;
    int rank, size;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    srand(time(NULL));

    double start;
    if (rank == 0){
        start = omp_get_wtime();
    }

    // Create Fish MPI struct, do it here?
    MPI_Datatype MPI_FISH;
    MPI_Datatype types[NUMFIELDS] = {MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE};
    int blocklengths[NUMFIELDS] = {1, 1, 1, 1, 1};
    MPI_Aint offsets[NUMFIELDS];

    offsets[0] = offsetof(Fish, euclDist);
    offsets[1] = offsetof(Fish, x_c);
    offsets[2] = offsetof(Fish, y_c);
    offsets[3] = offsetof(Fish, weight_c);
    offsets[4] = offsetof(Fish, weight_p);

    MPI_Type_create_struct(NUMFIELDS, blocklengths, offsets, types, &MPI_FISH);
   	MPI_Type_commit(&MPI_FISH);


    if(rank == 0){
        // When do we scatter and gather
        fishArray = initializeFish(numfish);
    }


    int fish_per_process = numfish / size;
    Fish* localFishArray = malloc(fish_per_process * sizeof(Fish));


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

        if(rank == 0) {
            double barycentre = sumOfProduct / sumOfDistance;
        }
    }

    if (rank == 0){
        double end = omp_get_wtime();
        double timeElapsed = end - start;
        printf("Average time for MPI elapsed: %10.6f\n",timeElapsed );
    }

    MPI_Finalize();
    return 0;
}