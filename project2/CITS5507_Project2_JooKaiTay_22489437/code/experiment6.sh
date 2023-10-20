#!/bin/sh 
#SBATCH --account=courses0101
#SBATCH --partition=debug
#SBATCH --ntasks=4
#SBATCH --ntasks-per-node=1
#SBATCH --time=00:60:00
#SBATCH --exclusive
#SBATCH --mem-per-cpu=32G
#module load  openmpi/4.0.5

export OMP_NUM_THREADS=4
mpicc -fopenmp -o experiment6 experiment6.c fish.c -lm
srun ./experiment6