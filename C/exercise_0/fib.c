#include <stdio.h>

long fib(long m) {

	if(m == 0)
	{
		return 0;
	}
	else if(m == 1)
	{
		return 1;
	}
	return (fib(m-1) + fib(m-2));
}