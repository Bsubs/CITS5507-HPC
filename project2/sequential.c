/**
 * Author: Joo Kai TAY (22489437)
*/

#include <stdio.h>
#include <stdlib.h>
#include "fish.h"
#include "sequential.h"

/**
 * @brief Simulates the movement and actions of an array of Fish structures over a specified number of steps.
 * 
 * The function sequentialOld makes use of three inner loops in the calculation and has the best performance.
 * 
 * This function serves as the base case for Sequential functions.
 *
 * @param fishArray A pointer to an array of Fish structures representing the fishes to be processed.
 * @param numfish An integer representing the number of fishes in fishArray.
 * @param numsteps An integer representing the number of simulation steps to be performed.
 */
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

