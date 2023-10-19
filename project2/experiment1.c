#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <mpi.h>
#include "fish.h"

void writeFishToFile(const char *filename, Fish *fishArray, int numfish) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("Failed to open file");
        return;
    }

    for (int i = 0; i < numfish; i++) {
        fprintf(fp, "x_coord: %f\n", fishArray[i].x_c);
        fprintf(fp, "y_coord: %f\n", fishArray[i].y_c);
    }
    fclose(fp);
}

/**
 * This experiment performs file writing using point-to-point communication 
 * of MPI_Send and MPI_Receive
*/
int main(int argc, char* argv[]) {
    int numfish = 100000000;
    Fish *fishArray1;
    Fish *localFishArray;
    int size, rank;
    int localSize;

    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    // Create the MPI_FISH type for sending fish
    MPI_Datatype MPI_FISH = create_mpi_fish_datatype();

    // Start timer
    double start;
    if (rank == 0){
        start = omp_get_wtime();
    }

    if (size != 4) {
        printf("This program requires 4 MPI processes (1 master and 3 workers).\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    localSize = numfish / size; 

    if (rank == 0) {
        fishArray1 = initializeFish(numfish);
        writeFishToFile("initial_data.txt", fishArray1, numfish);
    }

    localFishArray = (Fish *)malloc(sizeof(Fish) * localSize);

    // Manual scatter using MPI_Send and MPI_Recv
    for(int i = 0; i < size; i++) {
        if(rank == 0) {
            MPI_Send(&fishArray1[i * localSize], localSize, MPI_FISH, i, 0, MPI_COMM_WORLD);
        }
        if(rank == i) {
            MPI_Recv(localFishArray, localSize, MPI_FISH, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    }

    // Manual gather using MPI_Send and MPI_Recv
    for(int i = 0; i < size; i++) {
        if(rank == i) {
            MPI_Send(localFishArray, localSize, MPI_FISH, 0, 1, MPI_COMM_WORLD);
        }
        if(rank == 0) {
            MPI_Recv(&fishArray1[i * localSize], localSize, MPI_FISH, i, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    }

    if (rank == 0) {
        writeFishToFile("final_data.txt", fishArray1, numfish);
        free(fishArray1);
        double end = omp_get_wtime();
        double timeElapsed = end - start;
        printf("Time for Send Receive for %d fish elapsed: %10.6f\n", numfish, timeElapsed );
    }

    free(localFishArray);
    
    MPI_Finalize();

    return 0;
}