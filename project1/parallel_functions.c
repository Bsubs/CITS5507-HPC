#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#include "fish.h"
#include "parallel_functions.h"

/**
 * Function to implement parallelisation using reduction
 * This is the base case
 * Input: Fish* fishArray
*/
void parallelForReduction(Fish* fishArray, int numfish, int numsteps){
    for(int i = 0; i < numsteps; i++){
        double maxDiff = 0;
        double sumOfProduct = 0;
        double sumOfDistance = 0;

        // Loops through fish array and finds maxDiff in the current round
        #pragma omp parallel for reduction(max:maxDiff)
        for(int j = 0; j < numfish; j++) {
            double dist = fishArray[j].euclDist;
            if(dist > maxDiff) {maxDiff = dist;}
        }

        // Loops through fish array and performs eat & swim operations
        #pragma omp parallel for
        for(int j = 0; j < numfish; j++){
            eat(&fishArray[j], maxDiff, i);
            swim(&fishArray[j]);
        }

        // Loops through fish array and accumulates variables for barycentre
        #pragma omp parallel for reduction(+:sumOfProduct,sumOfDistance)
        for(int j = 0; j < numfish; j++){
            sumOfProduct += fishArray[j].euclDist * fishArray[j].weight_p;
            sumOfDistance += fishArray[j].euclDist;
        }
        double barycentre = sumOfProduct / sumOfDistance;
    }  
}

/**
 * Function to experiment with different scheduling types
 * Input: Fish* fishArray
 * Input: char* scheduleType
*/
void parallelForSchedule(Fish* fishArray, char* scheduleType, int numfish, int numsteps){
    for(int i = 0; i < numsteps; i++){
        double maxDiff = 0;
        double sumOfProduct = 0;
        double sumOfDistance = 0;
        
        if(strcmp(scheduleType, "STATIC") == 0){
            #pragma omp parallel
            {
                #pragma omp for reduction(max: maxDiff) schedule(static)
                for(int j = 0; j < numfish; j++) {
                    double dist = fishArray[j].euclDist;
                    if(dist > maxDiff) {maxDiff = dist;}
                }

                #pragma omp for schedule(static)
                for(int j = 0; j < numfish; j++){
                    eat(&fishArray[j], maxDiff, i);
                    swim(&fishArray[j]);
                }

                #pragma omp for reduction(+ : sumOfProduct, sumOfDistance) schedule(static)
                for(int j = 0; j < numfish; j++){
                    sumOfProduct += fishArray[j].euclDist * fishArray[j].weight_p;
                    sumOfDistance += fishArray[j].euclDist;
                }
            }
        } else if(strcmp(scheduleType, "DYNAMIC") == 0) {
            #pragma omp parallel
            {
                #pragma omp for reduction(max: maxDiff) schedule(dynamic)
                for(int j = 0; j < numfish; j++) {
                    double dist = fishArray[j].euclDist;
                    if(dist > maxDiff) {maxDiff = dist;}
                }

                #pragma omp for schedule(dynamic)
                for(int j = 0; j < numfish; j++){
                    eat(&fishArray[j], maxDiff, i);
                    swim(&fishArray[j]);
                }

                #pragma omp for reduction(+ : sumOfProduct, sumOfDistance) schedule(dynamic)
                for(int j = 0; j < numfish; j++){
                    sumOfProduct += fishArray[j].euclDist * fishArray[j].weight_p;
                    sumOfDistance += fishArray[j].euclDist;
                }
            }
        } else if(strcmp(scheduleType, "GUIDED") == 0) {
            #pragma omp parallel
            {
                #pragma omp for reduction(max: maxDiff) schedule(guided)
                for(int j = 0; j < numfish; j++) {
                    double dist = fishArray[j].euclDist;
                    if(dist > maxDiff) {maxDiff = dist;}
                }

                #pragma omp for schedule(guided)
                for(int j = 0; j < numfish; j++){
                    eat(&fishArray[j], maxDiff, i);
                    swim(&fishArray[j]);
                }

                #pragma omp for reduction(+ : sumOfProduct, sumOfDistance) schedule(guided)
                for(int j = 0; j < numfish; j++){
                    sumOfProduct += fishArray[j].euclDist * fishArray[j].weight_p;
                    sumOfDistance += fishArray[j].euclDist;
                }
            }
        }



        double barycentre = sumOfProduct / sumOfDistance;
    }   
}