#include "threads.h"
#include <unistd.h>
#include <stdio.h>

void function_1()
{
    while(1)
    {
        printf("Hello I'm function 1!\n");
        sleep(1);
        yield();
    }
}

void function_2()
{
    while(1)
    {
        printf("Hello I'm function 2!\n");
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
    InitQueue(&RunQ);
    start_thread(function_1);
    start_thread(function_2);
    start_thread(function_3);
    start_thread(function_4);
	
    run();
	
    return 0;
}
