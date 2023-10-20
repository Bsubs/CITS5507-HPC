#ifndef FISH_H
#define FISH_H
#define STARTWEIGHT 10000
#define NUMFIELDS 5

/**
 * Author: Joo Kai TAY (22489437)
*/

// Fish struct
typedef struct fish {
    double euclDist;
    // Current
    double x_c;
    double y_c;
    double weight_c;
    // Previous
    double weight_p;
} Fish;

// MPI_FISH
extern MPI_Datatype MPI_FISH;

// Fish Functions implemented
Fish* initializeFish(int numfish);
double distance(double x, double y);
void swim(Fish* fish1);
void eat(Fish* fish1, double maxObj, int step);
MPI_Datatype create_mpi_fish_datatype();

#endif