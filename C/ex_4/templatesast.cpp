#include <iostream>
#include <functional>
#include <string>
using namespace std;


template<typename V>
V Constant<V>::eval(env<V> * p) {
	
	cout << "constant" << c << "\n";
	return c;
}

template<typename V>
V Var<V>::eval(env<V> *p) {

	//cout << "VAR\n";
	env<V> * conductor = p;

	while(conductor)
	{
		//cout << "current " << conductor->var << "\n";
		if(conductor->var == name)
		{
			//cout << "VAR MATCH BOY" << conductor->value << "\n";	
			return conductor->value;
		}

		conductor = conductor->next;
	}

	//cout << "Var" << p->value << "\n";

	return conductor->value;
}

template<typename V>
V Let<V>::eval(env<V> *p) {

	//cout << "Let\n";
	V result = 0;

	result = bexp->eval(p);

	//cout << "bvar " << bvar << " res " << result << "\n";

	p = append(p, bvar, result);

	//cout << "call body \n"; 
	result = body->eval(p);

	cout << "FLLSLSS " << result << "\n"; 


	return result;
}

template<typename V>
V OpApp<V>::eval(env<V> *p) {

	//cout << "OP\n";
	V result = ops.unit;
	ExpList<V> *temp;

	temp = args;
	cout << "Res initial " << result << "\n";

	while(temp)
	{
		cout << "Res " << result << "\n";
		//cout << "\nPls " << ops.binop(temp->head->eval(p), result);
		result = ops.binop(temp->head->eval(p), result);
		temp = temp->tail;
	}

	cout << "\ntotal op " << result << "\n";
	return result;
}

template<typename V>
env<V> * init(string var, V value) {

	struct env<V> *e = new struct env<V>;

	if(!e)
	{
		exit(0);
	}

	e->var = var;
	e->value = value;
	e->next = nullptr;

	return e;
}

template<typename V>
env<V> * append(struct env<V> *e, string var, V value) {

	struct env<V> *data;

	data = init<V>(var, value);

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





