#include <omp.h> 
#include <stdio.h> 
#include <stdlib.h> 
int arr[1000000];
int main(int argc, char* argv[]) 
{  
	int sum=0;
	for(int i=0;i<1000000;i++)
	{
		arr[i] = 1;
	}
	double t1 = omp_get_wtime();
    	#pragma omp parallel for reduction(+:sum)
		for(int j=0;j<1000000;j++)
                	sum+=arr[j]; 
	 
	printf("%d",sum);
	double t2 = omp_get_wtime();
	printf("\n%f",t2-t1);

} 


