#include "freegraph.h"

int i = 0;
struct A stack[100];

long sumA(struct A *p){

	long result = 0;
	struct A *curr;


	/*if(p != NULL)
	{
		addToList(list, p);
		result += p->n;
		result += sumA(p->a);
	}*/

	if(p != NULL)
	{
		result += p->n;

		if(p->a != p)
		{
			printf("Parent != A\n");
			arr[i++] = p;
			result += sumA(p->a);
		}
		/*if(p->b != p)
		{
			printf("Parent != B\n");
			result += sumA(p->b);
		}*/
	}


	return result;
}

int compare(void* data1, void* data2) {

	if(data1 == data2)
	{
		return 0;
	}
	else if(data1 < data2)
	{
		return -1;
	}

	return 1;

}

void destroy(void * data) {

	free(data);
}

void printData(void* data) {

	printf("%p\n", data);
}

void deallocateA(struct A *ap) {

}