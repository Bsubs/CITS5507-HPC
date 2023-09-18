#!/bin/sh
#SBATCH --account=courses0101
#SBATCH --partition=debug
#SBATCH --ntasks=1
#SBATCH --ntasks-per-node=4
#SBATCH --cpus-per-task=4
#SBATCH --time=00:15:00

module load gcc

gcc -o experiment1 experiment1.c fish.c sequential.c parallel_functions.c -fopenmp -lm

export OMP_NUM_THREADS=2 
echo "Average time for 2 threads:"
srun ./experiment1

export OMP_NUM_THREADS=4 
echo "Average time for 4 threads:"
srun ./experiment1

export OMP_NUM_THREADS=8 
echo "Average time for 8 threads:"
srun ./experiment1

export OMP_NUM_THREADS=16 
echo "Average time for 16 threads:"
srun ./experiment1

export OMP_NUM_THREADS=32 
echo "Average time for 32 threads:"
srun ./experiment1