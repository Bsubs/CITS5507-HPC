#include <stdio.h>
#include <stdlib.h>
#include "fish.h"
#include "sequential.h"

void sequential(Fish* fishArray){
    for(int i = 0; i < NUMSTEPS; i++){
        double maxDiff = 0;
        double sumOfProduct = 0;
        double sumOfDistance = 0;

        // Loops through fish array and finds maxDiff in the current round
        for(int j = 0; j < NUMFISH; j++) {
            double dist = fishArray[j].euclDist;
            if(dist > maxDiff) {maxDiff = dist;}
        }

        // Loops through fish array and performs eat & swim operations
        for(int j = 0; j < NUMFISH; j++){
            eat(&fishArray[j], maxDiff, i);
            swim(&fishArray[j]);
        }

        // Loops through fish array and accumulates variables for barycentre
        for(int j = 0; j < NUMFISH; j++){
            sumOfProduct += fishArray[j].euclDist * fishArray[j].weight_p;
            sumOfDistance += fishArray[j].euclDist;
        }
        double barycentre = sumOfProduct / sumOfDistance;
    }
}