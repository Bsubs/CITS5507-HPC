#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#include "fish.h"
#include "omp_parallel_for_schedule.h"

void parallelForSchedule(Fish* fishArray, char* scheduleType){
    for(int i = 0; i < NUMSTEPS; i++){
        double maxDiff = 0;
        double sumOfProduct = 0;
        double sumOfDistance = 0;
        
        if(strcmp(scheduleType, "STATIC") == 0){
            #pragma omp parallel
            {
                #pragma omp for reduction(max: maxDiff) schedule(static)
                for(int j = 0; j < NUMFISH; j++) {
                    double dist = fishArray[j].euclDist;
                    if(dist > maxDiff) {maxDiff = dist;}
                }

                #pragma omp for schedule(static)
                for(int j = 0; j < NUMFISH; j++){
                    eat(&fishArray[j], maxDiff, i);
                    swim(&fishArray[j]);
                }

                #pragma omp for reduction(+ : sumOfProduct, sumOfDistance) schedule(static)
                for(int j = 0; j < NUMFISH; j++){
                    sumOfProduct += fishArray[j].euclDist * fishArray[j].weight_p;
                    sumOfDistance += fishArray[j].euclDist;
                }
            }
        } else if(strcmp(scheduleType, "DYNAMIC") == 0) {
            #pragma omp parallel
            {
                #pragma omp for reduction(max: maxDiff) schedule(dynamic)
                for(int j = 0; j < NUMFISH; j++) {
                    double dist = fishArray[j].euclDist;
                    if(dist > maxDiff) {maxDiff = dist;}
                }

                #pragma omp for schedule(dynamic)
                for(int j = 0; j < NUMFISH; j++){
                    eat(&fishArray[j], maxDiff, i);
                    swim(&fishArray[j]);
                }

                #pragma omp for reduction(+ : sumOfProduct, sumOfDistance) schedule(dynamic)
                for(int j = 0; j < NUMFISH; j++){
                    sumOfProduct += fishArray[j].euclDist * fishArray[j].weight_p;
                    sumOfDistance += fishArray[j].euclDist;
                }
            }
        } else if(strcmp(scheduleType, "GUIDED") == 0) {
            #pragma omp parallel
            {
                #pragma omp for reduction(max: maxDiff) schedule(guided)
                for(int j = 0; j < NUMFISH; j++) {
                    double dist = fishArray[j].euclDist;
                    if(dist > maxDiff) {maxDiff = dist;}
                }

                #pragma omp for schedule(guided)
                for(int j = 0; j < NUMFISH; j++){
                    eat(&fishArray[j], maxDiff, i);
                    swim(&fishArray[j]);
                }

                #pragma omp for reduction(+ : sumOfProduct, sumOfDistance) schedule(guided)
                for(int j = 0; j < NUMFISH; j++){
                    sumOfProduct += fishArray[j].euclDist * fishArray[j].weight_p;
                    sumOfDistance += fishArray[j].euclDist;
                }
            }
        }



        double barycentre = sumOfProduct / sumOfDistance;
    }   
}