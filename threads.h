#include "q.h"
#include <stdlib.h>

TCB_t* RunQ;

void start_thread(void (*function)())
{
    stack_t* stack = (stack_t*)malloc(8192);
    TCB_t* thread = NewItem();
    init_TCB(thread, function, stack, 8192);
    AddQueue(&RunQ, thread);
}

void run()
{
    ucontext_t parent;
    getcontext(&parent);
    swapcontext(&parent, &(RunQ->context));
}

void yield()
{
    TCB_t* previousThread = RunQ;
    RotateQ(&RunQ);
    swapcontext(&(previousThread->context), &(RunQ->context)); 
}
