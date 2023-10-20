# CITS5507 Project 2 

Author: Joo Kai TAY (22489437)

## Functions

- Fish Simulation
    - fish.h: Header file containing definiton of Fish structure and fish functions 
    - fish.c: Implementation of functions to manipulate the Fish structure

## Experiments

The results and analysis of each of the following experiments can be found in the report. To run any of the following experiments, SSH into Setonix and follow the commands listed below:

- Experiment 0 
    - This experiment tests file writing using collective communication `MPI_Scatter` and `MPI_Gather`
    - experiment0.c: The main function for Experiment 0.
    - experiment0.sh: `sbatch experiment0.sh` to run this experiment

- Experiment 1 
    - This experiment tests file writing using point-to-point communication `MPI_Send` and `MPI_Receive`
    - experiment1.c: The main function for Experiment 1.
    - experiment1.sh: `sbatch experiment1.sh` to run this experiment

- Experiment 3 
    - Experiment 3 runs the best sequential code from project 1
    - experiment3.c: The main function for Experiment 3.
    - experiment3.sh: `sbatch experiment3.sh` to run this experiment

- Experiment 4 
    - Experiment 4 runs the best sequential code from experiment 2
    - experiment4.c: The main function for Experiment 4.
    - experiment4.sh: `sbatch experiment4.sh` to run this experiment

- Experiment 5 
    - Experiment 5 runs sequential code with MPI
    - experiment5.c: The main function for Experiment 5.
    - experiment5.sh: `sbatch experiment5.sh` to run this experiment

- Experiment 6 
    - Experiment 6 runs parallel code with MPI
    - experiment6.c: The main function for Experiment 6.
    - experiment6.sh: `sbatch experiment6.sh` to run this experiment

- Experiment 7 
    - Experiment 7 runs parallel code with MPI with MPI_init_thread
    - experiment7.c: The main function for Experiment 7.
    - experiment7.sh: `sbatch experiment7.sh` to run this experiment

- Experiment 8
    - Experiment 8 runs sequential code with `MPI_Send` and `MPI_Receive`
    - experiment8.c: The main function for Experiment 8.
    - experiment8.sh: `sbatch experiment8.sh` to run this experiment    

