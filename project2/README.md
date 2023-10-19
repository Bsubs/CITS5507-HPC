# CITS5507 Project 1 

Author: Joo Kai TAY (22489437)


ssh -Y jookaitay@setonix.pawsey.org.au

scp * jookaitay@setonix.pawsey.org.au:./project2


Things to do:

Part 1
1. Implement Scatter and gather
2. Implement send and receive
3. Implement broadcast? Maybe

For part 1: time the different implementations. Try massive ass arrays if timing is not good 

Part 2 (up to 10million fish)
1. Best case sequential
2. Best case parallel
3. MPI - Use global reduction operators
4. MPI - Use normal reduction operators (manually send stuff)

- experiment 0: File writing (scatter gather)
- experiment 1: File writing (send and receive)
- experiment 2: File writing (broadcast)
- experiment 3: Sequential
- experiment 4: OMP Parallel
- experiment 5: MPI Sequential
- experiment 6: MPI Parallel Base
- experiment 7: MPI Parallel Threadsafe
- experiment 8: MPI Sequential (Scatter and Gather)