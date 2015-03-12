#include "threads.h"

void function_1()
{
	while(1)
	{
		yield();
	}
}

void function_1()
{
	while(1)
	{
		yield();
	}
}

void function_3()
{
	while (1)
	{
		yield();
	}
}

void function_4()
{
	while(1)
	{
		yield();
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
