#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "fish.h"
#include "sequential.h"

int main(int argc, char *argv[]) {
    clock_t start, end;
    start = clock();

    srand(time(NULL));
    Fish* fishArray = initializeFish();
    // Remember to free
    free(fishArray);
    
    end = clock();
    double timeElapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Total time elapsed: %10.6f\n",timeElapsed );
}