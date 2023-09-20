#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fish.h"

/**
 * @brief Initialize an array of Fish structures.
 *
 * This function dynamically allocates memory for an array of Fish structures 
 * and initializes each fish with random coordinates within a bounded range.
 *
 * @param numfish The number of fish to initialize.
 * @return A pointer to the dynamically allocated array of Fish structures.
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
 * @brief Returns the euclidean distance given two points.

 * @param x The x coordinate.
 * @param y The y coordinate
 * @return The calculated distance.
 */
double distance(double x, double y) {
    return sqrt(pow(x, 2) + pow(y, 2));
}

/**
 * @brief Clamps a value between two other values.
 *
 * This function ensures that a value does not stray beyond a min and max value 
 *
 * @param value The value to clamp
 * @param min The minimum allowed 
 * @param max The maximum allowed 
 */
void clamp(double* value, double min, double max) {
    if (value == NULL) {
        return;
    }
    
    if (*value < min) {
        *value = min;
    } else if (*value > max) {
        *value = max;
    }
}

/**
 * @brief Updates the weight of a fish during a simulation step.
 *
 * This function updates the weight of a fish instance. The weight is bounded within 0 and 2w.
 *
 * @param fish1 Pointer to the Fish instance whose weight is to be updated.
 * @param maxObj The objective function in the current step.
 * @param step The current simulation step. If step is 0, the weight is reset to STARTWEIGHT.
 */
void eat(Fish* fish1, double maxObj, int step){
    if (step == 0) {
        double random_weight = ((double)rand() / (double)(RAND_MAX)) * 2.0 - 1.0;
        fish1->weight_c = STARTWEIGHT + random_weight;
    }
    else {
        double weight = fish1->weight_c;
        double deltaI = distance(fish1->x_c, fish1->y_c) - fish1->euclDist;

        // Calculate new weight and clamp it between boundary
        if(maxObj == 0) {
            weight = 0;
        }
        else {
            weight += deltaI / maxObj;
            clamp(&weight, 0, 2*STARTWEIGHT);
        }
        fish1->weight_p = fish1->weight_c;
        fish1->weight_c = weight;
    }
}

/**
 * @brief Updates the position of a fish in the current step.
 *
 * This function updates the position of a fish instance if its current weight is 
 * less than two times the STARTWEIGHT. The new position is calculated randomly 
 * within certain bounds and is then clamped to ensure it remains within a 
 * 200 x 200 square.
 *
 * @param fish1 Pointer to the Fish instance whose position is to be updated.
 */
void swim(Fish* fish1){
    if(fish1->weight_c < (2 * STARTWEIGHT)) {
        // Add a random number between -0.1 and 0.1
        double x_dist = ((double)rand() / RAND_MAX) * (0.1 + 0.1) + fish1->x_c;
        double y_dist = ((double)rand() / RAND_MAX) * (0.1 + 0.1) + fish1->y_c;

        // Limit the distance to the boundary
        clamp(&x_dist, -100, 100);
        clamp(&x_dist, -100, 100);

        // Previous euclidean distance for caluclation of weight in next step
        fish1->euclDist = distance(fish1->x_c, fish1->y_c);

        // Update position of fish
        fish1->x_c = x_dist;
        fish1->y_c = y_dist;
    }
}

