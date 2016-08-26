#include "List.h"

/*Author: Vanessa White
  May, 2015
*/
List * createList(int (*compare)(void* data1, void* data2), void (*destroy)(void*)) {

	List * this;

	this = malloc(sizeof(List));

	if(this)
	{
		this->head = NULL;
		this->compare = compare;
		this->destroy = destroy;
		return this;
	}

	return NULL;
}

void destroyList(List * this) {
	
	Node * rm;

	while(this->head)
	{
		rm = this->head;
		this->head = delete(this->head, rm->data, this->compare, this->destroy);
	}

	free(this);
}

void addToList(List * this, void *data) {

	this->head = insert(this->head, data, this->compare);	
}

Boolean isInList(List * this, void * data) {

	Node * toFind;

	toFind = search(this->head, data, this->compare);

	if(toFind)
	{
		return true;
	}

	return false;
}

void removeFromList(List * this, void * data) {

	this->head = delete(this->head, data, this->compare, this->destroy);
}

void printList(Node * this, void (*printNode)(void * data)) {

	if(!this)
	{
		return;
	}

	printNode(this->data);
	printList(this->next, printNode);
}


Node * initnode(void* data) {

	Node * this;

	this = malloc(sizeof(Node));

	if(this)
	{
		this->data = data;
		this->size = 0;
		this->next = NULL;

		return this;
	}

	return NULL;
}

Node * insert(Node * this, void * data, int(*compare)(void* data1, void* data2)) {

	Node * newNode, *temp;

	newNode = initnode(data);

	if(!newNode)
	{
		return NULL;
	}

	if(!this)
	{
		return newNode;
	}
	else
	{
		temp = this;

		while(temp->next)
		{
			temp = temp->next;
		}

		temp->next = newNode;
		newNode->next = NULL;

		return this;
	}


	return NULL;
}

Node * search(Node * this, void * data, int (*compare)(void* data1, void* data2)) {

	if(!this)
	{
		return NULL;
	}

	if(compare(data, this->data) == 0)
	{
		return this->data;
	}
	else
	{
		return search(this->next, data, compare);
	}

	return NULL;
}

Node * delete(Node * this, void * data, int (*compare)(void* data1, void* data2), void (*destroy)(void *)) {

	Node * temp;

	if(!this)
	{
		return NULL;
	}
	else
	{
		temp = this->next;
		destroy(this->data);
		free(this);

		return temp;
	}

	return NULL;	
}
