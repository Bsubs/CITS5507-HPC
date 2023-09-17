#!/bin/sh
#SBATCH --account=courses0101
#SBATCH --partition=debug
#SBATCH --ntasks=1
#SBATCH --ntasks-per-node=4
#SBATCH --cpus-per-task=4
#SBATCH --time=00:30:00

module load gcc

gcc -c experiment3.c
gcc -c fish.c
gcc -c sequential.c
gcc -c parallel_functions.c
gcc -o experiment3 -fopenmp experiment3.o fish.o sequential.o parallel_functions.o -lm 

export OMP_NUM_THREADS=16 

srun ./experiment3