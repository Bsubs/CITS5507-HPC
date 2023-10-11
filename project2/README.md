# CITS5507 Project 1 

Author: Joo Kai TAY (22489437)


ssh -Y jookaitay@setonix.pawsey.org.au

scp * jookaitay@setonix.pawsey.org.au:./project2


Things to do:
1. Sequential with millions of fish
2. Parallel with millions of fish
3. MPI - Use global reduction operators
4. MPI - Use normal reduction operators (manually send stuff)

Part 1:
1. Scatter & Gather (done)
2. Send & Receive
3. Broadcast (if I have time)

Part 2:

- Run with 10,000,000 fish and 1,000 steps
- Run with 1,2,3,4 processes 
- Run with 2, 4, 6, 8, 16 threads

1. Base Sequential case (project1)
2. Base Parallel case (project1)
3. Base sequential MPI case (experiment1)
4. Base parallel MPI case (experiment2)
5. look into scheduling, etc 