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
void parallelReductionOld(Fish* fishArray, int numfish, int numsteps){
    for(int i = 0; i < numsteps; i++){
        double maxDiff = 0;
        double sumOfProduct = 0;
        double sumOfDistance = 0;

        #pragma omp parallel
        {
            // Loops through fish array and finds maxDiff in the current round
            #pragma omp for reduction(max:maxDiff)
            for(int j = 0; j < numfish; j++) {
                double dist = distance(fishArray[j].x_c, fishArray[j].y_c) - fishArray[j].euclDist;
                if(dist > maxDiff) {maxDiff = dist;}
            }

            // Loops through fish array and performs eat & swim operations
            #pragma omp for
            for(int j = 0; j < numfish; j++){
                eat(&fishArray[j], maxDiff, i);
                swim(&fishArray[j]);
            }
            // Loops through fish array and accumulates variables for barycentre
            #pragma omp for reduction(+:sumOfProduct,sumOfDistance)
            for(int j = 0; j < numfish; j++){
                sumOfProduct += fishArray[j].euclDist * fishArray[j].weight_p;
                sumOfDistance += fishArray[j].euclDist;
            }
        }

        double barycentre = sumOfProduct / sumOfDistance;
    }  
}

/**
 * Function to implement parallelisation using reduction
 * This is the base case
 * Input: Fish* fishArray
*/
void parallelReduction(Fish* fishArray, int numfish, int numsteps){
    for(int i = 0; i < numsteps; i++){
        double maxDiff = 0;
        double sumOfProduct = 0;
        double sumOfDistance = 0;

        #pragma omp parallel
        {
            // Loops through fish array and finds maxDiff in the current round
            #pragma omp for reduction(max:maxDiff)
            for(int j = 0; j < numfish; j++) {
                double dist = distance(fishArray[j].x_c, fishArray[j].y_c) - fishArray[j].euclDist;
                if(dist > maxDiff) {maxDiff = dist;}
            }

            // Loops through fish array and accumulates variables for barycentre
            #pragma omp for reduction(+:sumOfProduct,sumOfDistance)
            for(int j = 0; j < numfish; j++){
                eat(&fishArray[j], maxDiff, i);
                swim(&fishArray[j]);
                sumOfProduct += fishArray[j].euclDist * fishArray[j].weight_p;
                sumOfDistance += fishArray[j].euclDist;
            }
        }

        double barycentre = sumOfProduct / sumOfDistance;
    }  
}

/**
 * Function to experiment with different scheduling types
 * Input: Fish* fishArray
 * Input: char* scheduleType
*/
void parallelSchedule(Fish* fishArray, char* scheduleType, int numfish, int numsteps){
    for(int i = 0; i < numsteps; i++){
        double maxDiff = 0;
        double sumOfProduct = 0;
        double sumOfDistance = 0;
        
        if(strcmp(scheduleType, "STATIC") == 0){
            #pragma omp parallel
            {
                #pragma omp for reduction(max: maxDiff) schedule(static)
                for(int j = 0; j < numfish; j++) {
                    double dist = distance(fishArray[j].x_c, fishArray[j].y_c) - fishArray[j].euclDist;
                    if(dist > maxDiff) {maxDiff = dist;}
                }

                #pragma omp for reduction(+ : sumOfProduct, sumOfDistance) schedule(static)
                for(int j = 0; j < numfish; j++){
                    eat(&fishArray[j], maxDiff, i);
                    swim(&fishArray[j]);
                    sumOfProduct += fishArray[j].euclDist * fishArray[j].weight_p;
                    sumOfDistance += fishArray[j].euclDist;
                }
            }
        } else if(strcmp(scheduleType, "DYNAMIC") == 0) {
            #pragma omp parallel
            {
                #pragma omp for reduction(max: maxDiff) schedule(dynamic)
                for(int j = 0; j < numfish; j++) {
                    double dist = distance(fishArray[j].x_c, fishArray[j].y_c) - fishArray[j].euclDist;
                    if(dist > maxDiff) {maxDiff = dist;}
                }

                #pragma omp for reduction(+ : sumOfProduct, sumOfDistance) schedule(dynamic)
                for(int j = 0; j < numfish; j++){
                    eat(&fishArray[j], maxDiff, i);
                    swim(&fishArray[j]);
                    sumOfProduct += fishArray[j].euclDist * fishArray[j].weight_p;
                    sumOfDistance += fishArray[j].euclDist;
                }
            }
        } else if(strcmp(scheduleType, "GUIDED") == 0) {
            #pragma omp parallel
            {
                #pragma omp for reduction(max: maxDiff) schedule(guided)
                for(int j = 0; j < numfish; j++) {
                    double dist = distance(fishArray[j].x_c, fishArray[j].y_c) - fishArray[j].euclDist;
                    if(dist > maxDiff) {maxDiff = dist;}
                }

                #pragma omp for reduction(+ : sumOfProduct, sumOfDistance) schedule(guided)
                for(int j = 0; j < numfish; j++){
                    eat(&fishArray[j], maxDiff, i);
                    swim(&fishArray[j]);
                    sumOfProduct += fishArray[j].euclDist * fishArray[j].weight_p;
                    sumOfDistance += fishArray[j].euclDist;
                }
            }
        } else if(strcmp(scheduleType, "RUNTIME") == 0) {
            #pragma omp parallel
            {
                #pragma omp for reduction(max: maxDiff) schedule(runtime)
                for(int j = 0; j < numfish; j++) {
                    double dist = distance(fishArray[j].x_c, fishArray[j].y_c) - fishArray[j].euclDist;
                    if(dist > maxDiff) {maxDiff = dist;}
                }

                #pragma omp for reduction(+ : sumOfProduct, sumOfDistance) schedule(runtime)
                for(int j = 0; j < numfish; j++){
                    eat(&fishArray[j], maxDiff, i);
                    swim(&fishArray[j]);
                    sumOfProduct += fishArray[j].euclDist * fishArray[j].weight_p;
                    sumOfDistance += fishArray[j].euclDist;
                }
            }
        }
        double barycentre = sumOfProduct / sumOfDistance;
    }   
}

/**
 * Function to implement parallelisation using taskloop
*/
void parallelTaskloop(Fish* fishArray, int numfish, int numsteps){
    for(int i = 0; i < numsteps; i++){
        double maxDiff = 0;
        double sumOfProduct = 0;
        double sumOfDistance = 0;

        #pragma omp parallel
        {
            #pragma omp single
            {
                // Loops through fish array and finds maxDiff in the current round
                #pragma omp taskloop reduction(max:maxDiff)
                for(int j = 0; j < numfish; j++) {
                    double dist = distance(fishArray[j].x_c, fishArray[j].y_c) - fishArray[j].euclDist;
                    if(dist > maxDiff) {maxDiff = dist;}
                }
            }

            #pragma omp single
            {
                // Loops through fish array and accumulates variables for barycentre
                #pragma omp taskloop reduction(+:sumOfProduct,sumOfDistance)
                for(int j = 0; j < numfish; j++){
                    eat(&fishArray[j], maxDiff, i);
                    swim(&fishArray[j]);
                    sumOfProduct += fishArray[j].euclDist * fishArray[j].weight_p;
                    sumOfDistance += fishArray[j].euclDist;
                }
            }
        }

        double barycentre = sumOfProduct / sumOfDistance;
    }  
}

/**
 * Function to implement parallelisation using tasks for all loops
*/
void parallelTasks(Fish* fishArray, int numfish, int numsteps){
    for(int i = 0; i < numsteps; i++){
        double maxDiff = 0;
        double sumOfProduct = 0;
        double sumOfDistance = 0;
        int block_size = 100; 

        // Loops through fish array and finds maxDiff in the current round
        #pragma omp parallel
        {
            #pragma omp single
            {
                for(int j = 0; j < numfish; j += block_size) {
                    #pragma omp task
                    {
                        double localMaxDiff = 0;
                        for(int k = 0; k < block_size && j+k < numfish; ++k) {
                            double dist = fishArray[j+k].euclDist;
                            if(dist > localMaxDiff) {localMaxDiff = dist;}
                        }
                        #pragma omp critical
                        {
                            if(localMaxDiff > maxDiff) {maxDiff = localMaxDiff;}
                        }
                    }
                }
            }
        

            // Loops through fish array and performs eat & swim operations
            #pragma omp single
            {
                for(int j = 0; j < numfish; j++){
                    #pragma omp task
                    {
                        eat(&fishArray[j], maxDiff, i);

                    }
                    #pragma omp task
                    {
                        swim(&fishArray[j]);
                    }
                }
            }

            // Loops through fish array and accumulates variables for barycentre
            #pragma omp single
            {
                for(int j = 0; j < numfish; j += block_size) {
                    #pragma omp task
                    {
                        double localSumOfProduct = 0.0;
                        double localSumOfDistance = 0.0;
                        for(int k = 0; k < block_size && j+k < numfish; ++k) {
                            localSumOfProduct += fishArray[j+k].euclDist * fishArray[j+k].weight_p;
                            localSumOfDistance += fishArray[j+k].euclDist;
                        }
                        #pragma omp critical
                        {
                            sumOfProduct += localSumOfProduct;
                            sumOfDistance += localSumOfDistance;
                        }
                    }
                }
            }
        }
        double barycentre = sumOfProduct / sumOfDistance;
    }  
}

/**
 * Implemented using sections
*/
void parallelSections(Fish* fishArray, int numfish, int numsteps){
    for(int i = 0; i < numsteps; i++){
        double maxDiff = 0;
        double sumOfProduct = 0;
        double sumOfDistance = 0;

        #pragma omp parallel
        {

            #pragma omp sections
            {
                #pragma omp section
                {
                    #pragma omp parallel for reduction(max:maxDiff) 
                    for(int j = 0; j < numfish; j++) {
                        double dist = distance(fishArray[j].x_c, fishArray[j].y_c) - fishArray[j].euclDist;
                        if(dist > maxDiff) { maxDiff = dist; }
                    }
                }

                #pragma omp section
                {
                    #pragma omp parallel for reduction(+:sumOfProduct,sumOfDistance) 
                    for(int j = 0; j < numfish; j++){
                        eat(&fishArray[j], maxDiff, i);
                        swim(&fishArray[j]);
                        sumOfProduct += fishArray[j].euclDist * fishArray[j].weight_p;
                        sumOfDistance += fishArray[j].euclDist;
                    }
                }
            }
        }

        double barycentre = sumOfProduct / sumOfDistance;
        // Use or remove barycentre variable as necessary
    }  
}