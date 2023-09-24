# CITS5507 Project 1 

Author: Joo Kai TAY (22489437)

## Functions

- Fish Simulation
    - fish.h: Header file containing definiton of Fish structure and fish functions 
    - fish.c: Implementation of functions to manipulate the Fish structure

- Sequential Functions
    - sequential.h: Declaration of the two sequential functions tested
    - sequential.c: Implementation of the two sequential functions tested

- Parallel Functions
    - parallel_functions.h: Declaration of the six parallel functions tested
    - parallel_functions.c: Implementation of the six parallel functions tested

## Experiments

The results and analysis of each of the following experiments can be found in the report. To run any of the following experiments, SSH into Setonix and follow the commands listed below:

- Experiment 0 
    - This experiment tests the time savings by removing implicit barriers and parallel regions
    - experiment0.c: The main function for Experiment 0.
    - experiment0.sh: `sbatch experiment0.sh` to run this experiment

- Experiment 1 
    - Experiment 1 investigates the effect of changing the number of threads on the time take for computation.
    - experiment1.c: The main function for Experiment 1.
    - experiment1.sh: `sbatch experiment1.sh` to run this experiment

- Experiment 2 
    - Experiment 2 investigates the increase in time taken as the number of fish increases.
    - experiment2.c: The main function for Experiment 2.
    - experiment2.sh: `sbatch experiment2.sh` to run this experiment

- Experiment 3 
    - Experiment 3 investigates the increase in time taken as the number of steps increases.
    - experiment3.c: The main function for Experiment 3.
    - experiment3.sh: `sbatch experiment3.sh` to run this experiment

- Experiment 4 
    - Experiment 4 investigates the difference in time taken for different scheduling methods and compares them to the base cases for both sequential and parallel.
    - experiment4.c: The main function for Experiment 4.
    - experiment4.sh: `sbatch experiment4.sh` to run this experiment

- Experiment 5 
    - Experiment 5 investigates the time savings that can be garnered from using different worksharing constructs such as sections and tasks.
    - experiment5.c: The main function for Experiment 5.
    - experiment5.sh: `sbatch experiment5.sh` to run this experiment



