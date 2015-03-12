#include "threads.h"

void function_1()
{
	while(1)
	{
		
	}
}

void function_1()
{
	while(1)
	{
		
	}
}

void function_3()
{
	while (1)
	{
		
	}
}

void function_4()
{
	while(1)
	{
		
	}
	
}

int main()
{
	start_thread(function_1);
	start_thread(function_2);
	start_thread(function_3);
	start_thread(function_4);
	
	run();
	
	return 0;
}
