//CSE430
//Project #2
//-----------------
// Jacob Ward
// Joshua Stark

#include "threads.h"
#include <unistd.h>
#include <stdio.h>
#include <time.h>

int fibonacciA;
int fibonacciB;

//This function shows the current time since the process began
void function_clock()
{
    while(1)
    {
	time_t t;
	time(&t);
        printf("The current time is %s", ctime(&t));
        sleep(1);
        yield();
    }
}

//Uses its own local variables and a global variable to generate the Fibonacci sequence over time
void function_fibonacci()
{
    while(1)
    {
        int localResult = fibonacciA + fibonacciB;
	fibonacciB = fibonacciA;
	fibonacciA = localResult;
        printf("Fibonacci mumbles aloud %d.\n", localResult);
        sleep(1);
        yield();
    }
}

void function_3()
{
    while (1)
    {
        printf("Hello I'm function 3!\n");
        sleep(1);
        yield();
    }
}

void function_4()
{
    while(1)
    {
        printf("Hello I'm function 4!\n");
        sleep(1);
        yield();
    }
}

int main()
{
    fibonacciA = 1;
    fibonacciB = 0;
  
    InitQueue(&RunQ);
    start_thread(function_clock);
    start_thread(function_fibonacci);
    start_thread(function_3);
    start_thread(function_4);
	
    run();
	
    return 0;
}
