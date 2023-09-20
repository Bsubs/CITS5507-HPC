#!/bin/sh
#SBATCH --account=courses0101
#SBATCH --partition=debug
#SBATCH --ntasks=1
#SBATCH --ntasks-per-node=4
#SBATCH --cpus-per-task=4
#SBATCH --time=00:60:00

module load gcc

gcc -o experiment4 experiment4.c fish.c sequential.c parallel_functions.c -fopenmp -lm

export OMP_NUM_THREADS=32

srun ./experiment4