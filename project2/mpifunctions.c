/**
 * Author: Joo Kai TAY (22489437)
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#include <mpi.h>
#include <stddef.h>
#include "fish.h"
#include "mpifunctions.h"

void mpiParallel(Fish* fishArray, int numfish, int numsteps) {
    int rank, size;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

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


    int fish_per_process = numfish / size;
    int start = rank * fish_per_process;
    int end = start + fish_per_process;
    Fish* localFishArray = malloc(fish_per_process * sizeof(Fish));


    for(int i = 0; i < numsteps; i++){
        double maxDiff = 0;
        double localMaxDiff = 0;
        double sumOfProduct = 0;
        double sumOfDistance = 0;

        if(rank == 0){
            // When do we scatter and gather
            MPI_Scatter(fishArray, fish_per_process, MPI_FISH, localFishArray, fish_per_process, MPI_FISH, 0, MPI_COMM_WORLD);
        }

        // Loops through local fish array chunk and finds maxDiff in the current round
        for(int j = start; j < end; j++) {
            double dist = distance(fishArray[j].x_c, fishArray[j].y_c) - fishArray[j].euclDist;
            if(dist > localMaxDiff) {localMaxDiff = dist;}
        }

        //  Compute global maxDiff using MPI_Allreduce
        MPI_Allreduce(&localMaxDiff, &maxDiff, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);

        // Loops through local fish array chunk and performs eat & swim operations
        for(int j = start; j < end; j++){
            eat(&fishArray[j], maxDiff, i);
            swim(&fishArray[j]);
        }

        // Loops through local fish array chunk and accumulates variables for barycentre
        double localSumOfProduct = 0;
        double localSumOfDistance = 0;
        for(int j = start; j < end; j++){
            localSumOfProduct += fishArray[j].euclDist * fishArray[j].weight_p;
            localSumOfDistance += fishArray[j].euclDist;
        }

        // Compute global sumOfProduct and sumOfDistance
        MPI_Allreduce(&localSumOfProduct, &sumOfProduct, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
        MPI_Allreduce(&localSumOfDistance, &sumOfDistance, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

        if(rank == 0) {
            MPI_Gather(localFishArray, fish_per_process, MPI_FISH, fishArray, fish_per_process, MPI_FISH, 0, MPI_COMM_WORLD);
            double barycentre = sumOfProduct / sumOfDistance;
        }
    }

    MPI_Finalize();
}
