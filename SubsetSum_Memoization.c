#include<stdio.h>
#include<omp.h>
#include<stdbool.h>
#include<stdlib.h>
// using namespace std;

int solve(int n , int sum , int arr[], int **memo)
{
	if(n==0 && sum>0) {
		// memo[n][sum] = 0;
		return 0;
	}
	if(sum==0) {
		// memo[n][sum]=1;
		return 1;
}

	int temp1 ;
	int temp2 ;

	if(memo[n][sum]!=-1)
	{
		return memo[n][sum];
	}

	#pragma omp task shared(temp1)
	temp1 = solve(n-1,sum,arr+1, memo);
	
	#pragma omp task shared(temp2)
	temp2 = solve(n-1, sum-arr[0], arr+1, memo);
	
	#pragma omp taskwait
	// #pragma omp taskwait

	if(arr[0] > sum){
		memo[n][sum] = temp1;
	 	return temp1;
	}

	// #pragma omp taskwait


	memo[n][sum] = temp1 || temp2;
	return  memo[n][sum];
}
int main(int argc, char const *argv[])
{
	int n ;
	int sum;
	printf("Enter n and sum : ");
	scanf("%d %d",&n,&sum);
	printf("Enter array elements :\n");
	int arr[n];
	int exists;
	for(int i=0;i<n;i++)
	{
		scanf("%d",&arr[i]);
	}


	int *memo[n+1];
	for(int i=0;i<=n;i++)
	{
		memo[i] = (int *)malloc((sum+1) * sizeof(int));
	} 
	for(int i=0;i<=n;i++)
	{
		for(int j=0;j<=sum;j++)
		{
			memo[i][j] = -1;
		}
	}
	for(int i=1;i<=sum;i++)
	{
		memo[0][i] = 0;
	}
	for(int i=0;i<=n;i++)
	{
		memo[i][0] = 1;
	}


//  3 34 4 12 5 2 
/*	for(int i=0;i<=n;i++)
	{
		for(int j=0;j<=sum;j++)
		{
			printf("%d ",memo[i][j]);
		}
		printf("\n");
	}
*/
	#pragma omp parallel
	#pragma omp single
	exists = solve(n,sum, arr, memo);
/*

	for(int i=0;i<=n;i++)
	{
		for(int j=0;j<=sum;j++)
		{
			printf("%d ",memo[i][j]);
		}
		printf("\n");
	}
*/
	if(exists) printf("Found a subset with given sum\n");
	else printf("No subset with given sum\n");
	return 0;
}