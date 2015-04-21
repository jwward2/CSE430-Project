//CSE430
//Project #3
//-----------------
// Jacob Ward
// Joshua Stark

#include "sem.h"
#include <unistd.h>
#include <stdio.h>
#include <time.h>

#define DEBUG 0
#define DEBUG_COUNT 0
#define BUFFER_SIZE 9
//0 - Method 1, 1 - Method 2, 2 - Debug Method
#define IMPLEMENTATION 1

//Global var for Method 1
int global = 0;
//Global vars for Method 2
int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
//Global var for Debug Method
int r = 0;

//Semaphore for method 1
Semaphore* mutex;

//Semaphores for method 2
Semaphore* mutexProd;
Semaphore* mutexCons;
Semaphore* empty;
Semaphore* full;

//Semaphores for debug fuctions
Semaphore* d1;
Semaphore* d2;
Semaphore* d3;

//Debug function that displays information regarding all the queues
void QueueDebug(int num)
{
	if (DEBUG)
	{
		switch(IMPLEMENTATION)
		{
			case 0:
				if (DEBUG_COUNT)
				{
					printf("\nDebug %d------\n", num);
					printf("Mutex Count: %d.\n\n", mutex->count);					
				}
				else
				{
					printf("\nDebug %d------\n", num);
					printf("RunQ Size: %d.\n", QueueSize(RunQ));
					printf("MutexQ Size: %d.\n\n", QueueSize(mutex->queue));
				}
				break;
			case 1:
				if (DEBUG_COUNT)
				{
					printf("\nDebug %d------\n", num);
					printf("MutexProd Count: %d.\n", mutexProd->count);
					printf("MutexCons Count: %d.\n", mutexCons->count);		
					printf("Empty Count: %d.\n", empty->count);
					printf("Full Count: %d.\n\n", full->count);					  
				}
				else
				{
					printf("\nDebug %d------\n", num);
					printf("RunQ Size: %d.\n", QueueSize(RunQ));
					printf("MutexProdQ Size: %d.\n", QueueSize(mutexProd->queue));
					printf("MutexConsQ Size: %d.\n", QueueSize(mutexCons->queue));		
					printf("EmptyQ Size: %d.\n", QueueSize(empty->queue));
					printf("FullQ Size: %d.\n\n", QueueSize(full->queue));		
				}
				break;
			case 2:
				if (DEBUG_COUNT)
				{
					printf("\nDebug %d------\n", num);
					printf("D1Q Count: %d.\n", d1->count);
					printf("D2Q Count: %d.\n", d2->count);
					printf("D3Q Count: %d.\n\n", d3->count);				  
				}
				else
				{
					printf("\nDebug %d------\n", num);
					printf("RunQ Size: %d.\n", QueueSize(RunQ));
					printf("D1Q Size: %d.\n", QueueSize(d1->queue));
					printf("D2Q Size: %d.\n", QueueSize(d2->queue));
					printf("D3Q Size: %d.\n\n", QueueSize(d3->queue));
				}
				break;
		}
	}
}

//Function for first method of implementing semaphores
void method1Function()
{
	int local = 0;
  
	while(1)
	{
		QueueDebug(1);
		P(mutex);
			QueueDebug(2);
			local++;
			global++;
			printf("Local: %d\n", local);
			printf("Global: %d\n", global);
			sleep(1);
		V(mutex);
		printf("Exited critical section\n");
		sleep(1);
		yield();
	}
}

//Functions for second method of implementing semaphores
void produce()
{
	while (1)
	{
		QueueDebug(1);
		P(empty);
			QueueDebug(2);
			P(mutexProd);
				buffer[in] = 1;
				printf("Produced a 1\n");
				sleep(1);
				in = (in + 1) % BUFFER_SIZE;
			V(mutexProd);
		V(full);
		yield();
	}
}

void consume()
{
	while (1)
	{
		QueueDebug(3);
		P(full);
			QueueDebug(4);
			P(mutexCons);
				buffer[out] = 0;
				printf("Consumed a 1\n");
				sleep(1);
				out = (out + 1) % BUFFER_SIZE;
			V(mutexCons);	
		V(empty);
		yield();
	}
}

//Functions representing exam question; used for debugging.
void GetRandom()
{
	while(1)
	{
		QueueDebug(1);
		P(d1);
			QueueDebug(2);
			r = rand();
			printf("Got random %d.\n", r);
			sleep(1);
		V(d2);
	}
}

void IsEven()
{
	while(1)
	{
		QueueDebug(3);
		P(d2);
			QueueDebug(4);
			if (r % 2 == 0)
			{
				printf("Random is even.\n");
				sleep(1);
			}
		V(d3);
	}
}

void IsOdd()
{
	while(1)
	{
		QueueDebug(5);
		P(d3);
			QueueDebug(6);
			if (r % 2 != 0)
			{
				printf("Random is odd.\n");
				sleep(1);
			}
		V(d1);
	}
}

int main()
{
	switch(IMPLEMENTATION)
	{
		case 0:
		{
			mutex = NewSemaphore();
			InitSem(mutex, 1);
			
			InitQueue(&RunQ);
			start_thread(method1Function);
			start_thread(method1Function);
			start_thread(method1Function);
			
			run();
			break;
		}
		case 1:
		{
			int i;
			for (i = 0; i < BUFFER_SIZE; i++)
				buffer[i] = 0;
		  
			mutexProd = NewSemaphore();
			InitSem(mutexProd, 1);
			mutexCons = NewSemaphore();
			InitSem(mutexCons, 1);
			empty = NewSemaphore();
			InitSem(empty, 2);
			full = NewSemaphore();
			InitSem(full, 0);
			
			InitQueue(&RunQ);
			start_thread(produce);
			start_thread(consume);
			start_thread(consume);
			start_thread(produce);
			
			run();
			break;
		}
		case 2:
		{
			srand(time(NULL));
			
			d1 = NewSemaphore();
			InitSem(d1, 1);
			d2 = NewSemaphore();
			InitSem(d2, 0);
			d3 = NewSemaphore();
			InitSem(d3, 0);
			
			InitQueue(&RunQ);
			start_thread(IsOdd);
			start_thread(IsEven);
			start_thread(GetRandom);

			run();  
			break;
		}
	}
	
    return 0;
}
