#include "threads.h"
#include <stdlib.h>

typedef struct Semaphore
{
	int count;
	TCB_t* queue;
} Semaphore;

Semaphore* NewSemaphore()
{
	Semaphore* temp = (Semaphore*)malloc(sizeof(Semaphore));
	return temp;
}

void InitSem(Semaphore* sema, int startCount)
{
  sema->count = startCount;
  InitQueue(&sema->queue);
}

void P(Semaphore* sema)
{
	TCB_t* blocked;
	sema->count--;
	
	if (sema->count < 0)
	{
		blocked = RunQ;
		DelQueue(&RunQ);
		AddQueue(&sema->queue, blocked);
		swapcontext(&(blocked->context), &(RunQ->context));
	}
}

void V(Semaphore* sema)
{
	sema->count++;
	
	if (sema->count <= 0)
	{
		AddQueue(&RunQ, DelQueue(&sema->queue));
		yield();
	}
}