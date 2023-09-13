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
gcc -c omp_parallel_for.c
gcc -c omp_parallel_for_schedule.c
gcc -o omp_parallel_for_schedule -fopenmp main.o fish.o sequential.o omp_parallel_for.o omp_parallel_for_schedule.o -lm 

export OMP_NUM_THREADS=16 

srun ./omp_parallel_for_schedule