#include<stdio.h>
#include<omp.h>
#include<stdbool.h>
#include<stdlib.h>
#define n 1000000



/************ CODE BY : KABIR JUNEJA , 2017UCS0043  ************/



typedef struct mutex{
 int val;
 } my_struct;


/*********  LOCK USING FETCH AND ADD METHOD  ******


typedef struct lock_t {
int ticket;
int turn;
} my_struct;


int FetchAndAdd(int *ptr) {
int old ;
#pragma omp atomic capture
{
old = *ptr;
*ptr = old + 1;

}
return old;
}

void mylock_init(my_struct *lock) {
lock->ticket = 0;
lock->turn= 0;
}


void mylock_lock(my_struct *lock) {
int myturn = FetchAndAdd(&lock->ticket);
while (lock->turn != myturn)
; // spin
}



void mylock_unlock(my_struct *lock) {
#pragma omp atomic 
lock->turn = lock->turn + 1;
}


void mylock_destroy(my_struct *lock) {
free(lock);
}



*********************/






/************* TEST AND SET METHOD TO IMPLEMENT A LOCK ************/

int T_S(my_struct *ptr) {
int temp ;
#pragma omp atomic capture
{

temp =  ptr->val; // fetch old value at ptr
// store ’new’ into ptr
ptr->val = 1;
}
return temp;
// return the old value
}




/****************   LOCK USING COMPARE AND SWAP



int CompareAndSwap(my_struct *ptr, int expected, int new) 
{
// (actual == expected) ? ptr->flag = new : ;
int actual;
#pragma omp atomic capture
{

actual	=  ptr->flag;
// if(expected == actual)
ptr->flag = new;

// if(actual == expected) ptr->flag = actual;
}

return actual;
}


***************/

 void mylock_init(my_struct *mutex) {
 mutex->val = 0;
 }

 void mylock_lock(my_struct *mutex) {
 while(T_S(mutex) == 1)
 ;
  // spin
 }

 void mylock_unlock(my_struct *mutex) {
 mutex->val = 0;
 }	

void mylock_destroy(my_struct *mutex) {
 mutex->val = -1;
 // free(lock);
 }





 


int main(int argc, char const *argv[])
{
	my_struct mutex;
	mylock_init(&mutex);

	int a[1000000];
	for(int i=0;i<n;i++)
		a[i]=1;
	int i,tid,numt,sum=0;
	double t1,t2;
	t1 = omp_get_wtime();
	#pragma omp parallel default(shared)private(i,tid)
	{

		int from,to;
		tid = omp_get_thread_num();
		numt = omp_get_num_threads();
		
		from = (n/numt)*tid;
		to = (n/numt) * (tid+1) -1;
		if(tid==numt-1)
			to = n-1;
		// printf( "Hello from %d of %d, my range is from=%d to=%d\n",tid, numt, from, to ) ;
		
		int psum=0;
		

		for(i=from;i<=to;i++)
		{
		
			psum+=a[i];
		}
		mylock_lock(&mutex);
		sum += psum;	
		mylock_unlock(&mutex);
		
	}
	mylock_destroy(&mutex);
	t2 = omp_get_wtime();

	printf("%d\n",sum );
	printf("%f\n", t2-t1);
	return 0;
}