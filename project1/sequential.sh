#!/bin/sh
#SBATCH --account=courses0101
#SBATCH --partition=debug
#SBATCH --ntasks=1
#SBATCH --ntasks-per-node=4
#SBATCH --cpus-per-task=4
#SBATCH --time=00:05:00

module load gcc

gcc -c main.c
gcc -c fish.c
gcc -c sequential.c
gcc -o sequential main.o fish.o sequential.o -lm

export OMP_NUM_THREADS=16 

srun ./sequential