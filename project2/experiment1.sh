#!/bin/sh 
#SBATCH --account=courses0101
#SBATCH --partition=debug
#SBATCH --ntasks=4
#SBATCH --ntasks-per-node=1
#SBATCH --time=00:01:00
#SBATCH --exclusive
#SBATCH --mem-per-cpu=32G
#module load  openmpi/4.0.5

export OMP_NUM_THREADS=2
mpicc -fopenmp -o experiment1 experiment1.c fish.c -lm
srun ./experiment1