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

int main(int argc, char* argv[]) {
    int numfish = 10000;
    Fish *fishArray1;
    Fish *localFishArray;
    int size, rank;
    int localSize;

    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

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
            MPI_Send(&fishArray[i * fish_per_process], fish_per_process, MPI_FISH, i, 0, MPI_COMM_WORLD);
        }
        if(rank == i) {
            MPI_Recv(localFishArray, fish_per_process, MPI_FISH, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    }
    
    MPI_Gather(localFishArray, localSize*sizeof(Fish), MPI_BYTE, fishArray1, localSize*sizeof(Fish), MPI_BYTE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        writeFishToFile("final_data.txt", fishArray1, numfish);
        free(fishArray1);
    }

    free(localFishArray);
    
    MPI_Finalize();

    printf("test: %d\n", size);
    return 0;
}