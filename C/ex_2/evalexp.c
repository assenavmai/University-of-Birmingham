#include "evalexp.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct env {

	char varname[8];
	int val;
	struct env *next;
};

struct env *head;
struct env *tail;
int len;

int evalexpenv(struct exp *e, struct env *env);
int getOp(struct exp *e);
int evalQueue(int oper);
int evaluateList(struct exp *e, int oper);
struct env * init(char * varname, int val);
void destroy();
void enqueue(char * varname, int val);
void dequeue();
int isEmpty();
void print();


int evalexp(struct exp *e) {

	int result = 0;

	switch(e->tag)
	{
		case 0:
			printf("let tag\n");
			result = evalexpenv(e, head);
			break;
		case 3:
			printf("operation tag\n");
			break;
		default:
			printf("other tag\n");
			break;
	}
	/*int oper = 0;

	oper = getOp(e);void print()
	printf("op %d\n", oper);

	result = evaluateList(e, oper);*/

	
	return result;
}

int evalexpenv(struct exp *e, struct env *env) {

	int oper = 0;
	int result = 0;
	struct explist *curr;

	oper = getOp(e);
	printf("op %d\n", oper);

	result = evaluateList(e, oper);

  	curr = e->body->exps;

  	while(curr)
  	{
  		enqueue(curr->head->var, result);
  		curr = curr->tail;
  	}

  	print();

  	oper = e->body->op;
  	printf("oooo %d\n", oper);

  	result = evalQueue(oper);

  	destroy();

	return result;
}

int evaluateList(struct exp *e, int oper) {

	struct explist *curr;
	int result = 1;
	int isAdd = 0;

	if(oper == 0)
	{
		isAdd = 1;
		result = 0;
	}

	curr = e->bexp->exps;

	while(curr)
	{
		printf("Node %d %d\n", curr->head->constant, curr->head->tag);

		if(curr->head->tag == 1)
		{
			if(isAdd)
			{
				result += curr->head->constant;
			}
			else
			{
				result *= curr->head->constant;
			}
		}
		curr = curr->tail;
	}

	return result;
}

int evalQueue(int oper) {

    struct env *temp;
    int result = 1;
    int isAdd = 0;

    if(oper == 0)
    {
    	result = 0;
    	isAdd = 1;
    }
   
    temp = head;
    //printf("\nQueue begin printing....\n");
    while(temp != NULL)
    {

    	if(isAdd)
    	{
    		result += temp->val;
    	}
    	else
    	{
    		result *= temp->val;
    	}
       // printf("%s %d\n", temp->varname, temp->val);

        temp = temp->next;
    }
   // printf("\nQueue end printing....\n");
    return result;
}


int getOp(struct exp *e) {

	if(e->bexp->tag == 3)
	{
		switch(e->bexp->op)
		{
			case 0:
				printf("addition\n");
				return 0;
			case 1:
				printf("mult\n");
				return 1;
			default:
				printf("invalid\n");
				break;
		}
	}

	return -1;
}


/*******Data structure**********/

struct env * init(char * varname, int val) {

	struct env *newEnv = malloc(sizeof(struct env) * 1);

	if(!newEnv)
	{
		fprintf(stderr, "%s\n", "error: malloc() in function init()");
		exit(0);
	}

	strcpy(newEnv->varname, varname);
	newEnv->val = val;
	newEnv->next = NULL;

	return newEnv;
}

void destroy() {

    if(!head)
    {
        return;
    }
    
    while(head != NULL)
    {
        dequeue();
    }
    
    tail = NULL;
}

void enqueue(char * varname, int val) {

	struct env *data;

	data = init(varname, val);

	if(!head)
	{
		head = tail = data;
	}
	else
	{
		tail->next = data;
		tail = data;
	}

	len++;
}

void dequeue() {

	struct env *temp;

	if(isEmpty())
	{
		fprintf(stderr, "%s\n", "error: dequeue()");
		exit(0);
	}

	temp = head;
	head = temp->next;
	free(temp);
	len--;
}

int isEmpty() {

	if(len == 0 || head == NULL)
	{
		return 1;
	}

	return 0;
}

void print() {

    struct env *temp;
   
    temp = head;
    printf("\nQueue begin printing....\n");
    while(temp != NULL)
    {
        printf("%s %d\n", temp->varname, temp->val);
        temp = temp->next;
    }
    printf("\nQueue end printing....\n");

}

