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
- Change number of fish /steps
    - 10,000 / 10,000
        - Sequential: 12.838577s
        - Parallel: 12.823821s
    - 100,000 / 10,000
        - Sequential: 128.361821
        - Parallel: 128.003554s
    - 200,000 / 10,000
        - Sequential: 257.536186s
        - Parallel: 255.538548s
    - 10,000 / 100,000
        - Sequential: 127.602913s
        - Parallel: 127.259265s
    - 10,000 / 200,000 
        - Sequential: 260.593139s
        - Parallel: 261.114517s
- Tasks? 
- change number of threads
    - 16 threads:
        - Sequential: 12.838577s
        - Parallel: 12.823821s
    - 8 threads:
        - Sequential: 12.809720s
        - Parallel: 12.818975s
    - 4 threads:
        - Sequential: 12.899041s
        - Parallel: 12.788475s 
- schedule clause: static, dynamic, guided
Total time for sequential elapsed:  12.895183
Total time for parallel_for elapsed:  12.896078
Total time for static_parallel_for elapsed:  12.861514
Total time for dynamic_parallel_for elapsed:  12.886132
Total time for guided_parallel_for elapsed:  12.904375

Total time for sequential elapsed:  12.899295
Total time for parallel_for elapsed:  12.898575
Total time for static_parallel_for elapsed:  12.859763
Total time for dynamic_parallel_for elapsed:  12.878765
Total time for guided_parallel_for elapsed:  12.897214

