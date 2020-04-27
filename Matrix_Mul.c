#include <omp.h> 
#include <stdio.h> 
#include <stdlib.h> 
#define mSize 512

int main(int argc, char* argv[]) 
{	
	double A[mSize][mSize], B[mSize][mSize], C[mSize][mSize];
	  
	int sum=0;
	for(int i=0;i<mSize;i++)
	{
		for(int j=0;j<mSize;j++)
		{
			A[i][j] = 1;
			B[i][j] = 1;
			C[i][j] = 0;
		}
	}
	double t1 = omp_get_wtime();
    	#pragma omp parallel for collapse(2)
		for(int i=0;i<mSize;i++)
			for(int j=0;j<mSize;j++)
				for(int k=0;k<mSize;k++)
					C[i][j] += (A[i][k] *B[k][j]);
	for(int i=0;i<mSize;i++)
	{
		for(int j=0;j<mSize;j++)
		{
			printf("%f ",C[i][j]);
		}
		printf("\n");
	}
		
	double t2 = omp_get_wtime();
	printf("\n TIME : %f",t2-t1);

} 


