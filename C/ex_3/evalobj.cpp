#include <string>
#include <iostream>
using namespace std;
#include "evalobj.h"

struct env * init(string var, int value);
struct env * append(struct env * root, string var, int value);

int Constant::eval(env * e) {
	
	return n;
}

int Var::eval(env *e) {

	struct env * conductor = e;

	while(conductor)
	{
		
		if(conductor->var == name)
		{
			return conductor->value;
		}

		conductor = conductor->next;
	}

	return conductor->value;
}

int Let::eval(env * e) {

	struct env * conductor = e;

	int result = 0;

	result = bexp->eval(e);

	e = append(e, bvar, result);

	result = body->eval(e);

	return result;
}

int OpApp::eval(env * e) {

	int result;
	bool isAdd = false;
	ExpList * temp;


	if(op == 0)
	{
		isAdd = true;
		result = 0;
	}
	else
	{
		result = 1;
	}

	temp = args;
	
	while(temp)
	{
		if(isAdd)
		{
			result += temp->head->eval(e);
		}
		else
		{
			result *= temp->head->eval(e);
		}
		temp = temp->tail;
	}


	return result;
}

/*Initializes an object*/
struct env * init(string var, int value) {

	struct env *e = new struct env;

	if(!e)
	{
		exit(0);
	}

	e->var = var;
	e->value = value;
	e->next = nullptr;

	return e;
}

/*Adds to the front of a list, behaves like a queue*/
struct env * append(struct env * e, string var, int value) {

	struct env * data;

	data = init(var, value);

	if(!e)
	{	
		e = data;
	}
	else
	{
		data->next = e;
		return data;
	}

	return e;
}



