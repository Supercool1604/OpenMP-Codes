# OpenMP-Codes  
OpenMP codes I wrote during my course on Parallel and Distributed Programming:  
sum.c - Basic Array sum computation  
Matrix_mul.c - Multiplication of 2 matrices of size 512 * 512 each   
SubsetSum_Memoization - https://www.geeksforgeeks.org/subset-sum-problem-dp-25/ Implementation of this program in Top-Down Approach (memoization) using OpenMP tasks   
pdp_2.c - Implementing locks structure using OpenMP atomic instruction.  

Compilation :   
Go to directory where the code is,   
gcc -o temp -fopenmp SubsetSum_Memoization.c   

Run:   
./temp   
