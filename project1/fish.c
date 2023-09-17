#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fish.h"

/**
 * Initializes the fish array
 * Creates an array equal to the size of NUMFISH defined in fish.h
*/
Fish* initializeFish(int numfish){
    // Dynamically allocate memory according to NUMFISH
    Fish* fishArray = (Fish*)malloc(numfish * sizeof(Fish));
    if (fishArray == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1); 
    }

    // Allocate the initial positions between -100 and 100
    // Allocate initial weight 1
    // We can probably parallelize this or not probably not required
    for(int i = 0; i < numfish; i++){
        fishArray[i].x_c = ((double)rand() / RAND_MAX) * 200.0 - 100.0;
        fishArray[i].y_c = ((double)rand() / RAND_MAX) * 200.0 - 100.0;
    }

    return fishArray;
}

/**
 * Distance function
 * input: A Fish object
 * output: Euclidean distance from origin
*/
double distance(double x, double y) {
    return sqrt(pow(x, 2) + pow(y, 2));
}

/**
 * Helper function to ensure that values do not stray outside of
 * predefined boundaries
*/
double clamp(double value, double min, double max) {
    if (value < min) {
        value = min;
    }
    else if (value > max) {
        value = max;
    }
    return value;
}

/**
 * A fish eats in every step
*/
void eat(Fish* fish1, double maxWeight, int step){
    if (step == 0) {
        fish1->weight_c = STARTWEIGHT;
    }
    else {
        double weight = fish1->weight_c;
        double deltaI = distance(fish1->x_c, fish1->y_c) - fish1->euclDist;

        // Calculate new weight and clamp it between boundary
        if(maxWeight == 0) {
            weight = 0;
        }
        else {
            weight += deltaI / maxWeight;
            weight = clamp(weight, 0, 2*STARTWEIGHT);
        }
        fish1->weight_p = fish1->weight_c;
        fish1->weight_c = weight;
    }
}

/**
 * A fish swims in a random direction if it can eat in the current round
*/
void swim(Fish* fish1){
    if(fish1->weight_c < (2 * STARTWEIGHT)) {
        // Add a random number between -0.1 and 0.1
        double x_dist = ((double)rand() / RAND_MAX) * (0.1 + 0.1) + fish1->x_c;
        double y_dist = ((double)rand() / RAND_MAX) * (0.1 + 0.1) + fish1->y_c;

        // Limit the distance to the boundary
        x_dist = clamp(x_dist, -100, 100);
        y_dist = clamp(x_dist, -100, 100);

        // Previous euclidean distance for caluclation of weight in next step
        fish1->euclDist = distance(fish1->x_c, fish1->y_c);

        // Update position of fish
        fish1->x_c = x_dist;
        fish1->y_c = y_dist;
    }
}

