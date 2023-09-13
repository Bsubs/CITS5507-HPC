# CITS5507 Project 1 

## File structure
- main.c
- fish.h
    - header file containing the Fish struct 
    - contains the functions to interact with Fish
- fish.c
    - implementation of functions declared in fish.h

- sequential.c
    - sequential version of the loops

- omp_parallel_for.c
    - Parallel version of the loops implemented using reduction

## Login to setonix
ssh -Y jookaitay@setonix.pawsey.org.au

## Transferring files to setonix
scp * jookaitay@setonix.pawsey.org.au:
rm -f .*

## Running the program
sbatch sequential.sh

## Project ideas
- Use parallel for reduction
- Tasks? 
- change number of fish /steps 
- change number of threads 
- schedule clause: static, dynamic, guided