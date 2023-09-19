#include <stdio.h>
#include <stdlib.h>
#include "fish.h"
#include "sequential.h"

void sequential(Fish* fishArray, int numfish, int numsteps){
    for(int i = 0; i < numsteps; i++){
        double maxDiff = 0;
        double sumOfProduct = 0;
        double sumOfDistance = 0;

        // Loops through fish array and finds maxDiff in the current round
        for(int j = 0; j < numfish; j++) {
            double dist = distance(fishArray[j].x_c, fishArray[j].y_c) - fishArray[j].euclDist;
            if(dist > maxDiff) {maxDiff = dist;}
        }

        // Loops through fish array and performs eat & swim operations
        for(int j = 0; j < numfish; j++){
            eat(&fishArray[j], maxDiff, i);
            swim(&fishArray[j]);
        }

        // Loops through fish array and accumulates variables for barycentre
        for(int j = 0; j < numfish; j++){
            sumOfProduct += fishArray[j].euclDist * fishArray[j].weight_p;
            sumOfDistance += fishArray[j].euclDist;
        }
        double barycentre = sumOfProduct / sumOfDistance;
    }
}