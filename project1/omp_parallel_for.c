#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "fish.h"
#include "omp_parallel_for.h"

void parallelFor(Fish* fishArray){
    for(int i = 0; i < NUMSTEPS; i++){
        double maxDiff = 0;
        double sumOfProduct = 0;
        double sumOfDistance = 0;

        #pragma omp parallel
        {
            #pragma omp for reduction(max: maxDiff)
            // Loops through fish array and finds maxDiff in the current round
            for(int j = 0; j < NUMFISH; j++) {
                double dist = fishArray[j].euclDist;
                if(dist > maxDiff) {maxDiff = dist;}
            }

            #pragma omp for
            // Loops through fish array and performs eat & swim operations
            for(int j = 0; j < NUMFISH; j++){
                eat(&fishArray[j], maxDiff, i);
                swim(&fishArray[j]);
            }

            #pragma omp for reduction(+ : sumOfProduct, sumOfDistance)
            // Loops through fish array and accumulates variables for barycentre
            for(int j = 0; j < NUMFISH; j++){
                sumOfProduct += fishArray[j].euclDist * fishArray[j].weight_p;
                sumOfDistance += fishArray[j].euclDist;
            }
        }
        double barycentre = sumOfProduct / sumOfDistance;
    }   
}

