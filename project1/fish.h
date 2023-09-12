#ifndef FISH_H
#define FISH_H

#define NUMFISH 10000
#define STARTWEIGHT 1000
#define NUMSTEPS 10000

typedef struct fish {
    double euclDist;
    // Current
    double x_c;
    double y_c;
    double weight_c;
    // Previous
    double weight_p;
} Fish;

// Functions implemented
Fish* initializeFish();
double distance(double x, double y);
void swim(Fish* fish1);
void eat(Fish* fish1, double maxWeight, int step);

#endif