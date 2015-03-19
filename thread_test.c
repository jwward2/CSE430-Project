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
int x;
int y;

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

//This function displays the factorial of the current value of the two gloal variables x and y.
void function_3()
{
    while (1)
    {
		int x_current;
		int y_current;
		int z, fact = 1;
		
		for (z = 1; z <= x; z++)
		{
			fact = fact * z;
		}
		
		x_current = fact;
		
		fact = 1;
		
		for (z = 1; z <= y; z++)
		{
			fact = fact * z;
		}
		
		y_current = fact;
		
        printf("Current facotiral of x is %d\n", x_current);
        printf("Current factorial of y is %d\n", y_current);
        sleep(1);
        yield();
    }
}

//This function increments the two global variables x and y
void function_4()
{
    while(1)
    {
		x++;
		y++;
        printf("Global Variable x is %d\n", x);
        printf("Global Variable y is %d\n", y);
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
