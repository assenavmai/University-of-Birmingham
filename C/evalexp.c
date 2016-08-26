/***Vanessa White, C/C++****/
#include "evalexp.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct env {

	char varname[8];
	int val;
	int pos;
	struct env *next;
};

struct env *head;
struct env *tail;
int len;

struct env * init(char * varname, int val, int pos);
void destroy();
void enqueue(char * varname, int val, int pos);
void dequeue();
int isEmpty();
void print();


int evalexpenv(struct exp *e, struct env *env);
int listEval(int oper, struct exp * e, struct env *env);
int getVarVal(struct exp *e, struct env *env);

int evalexp(struct exp *e) {

	int result = 0;
	struct env *q = malloc(sizeof(struct env *) * 100);


	if(e)
	{
		switch(e->tag)
		{
			case 0:
				printf("evalexp.c: Let Tag\n");
				result = evalexpenv(e, q);
				break;
			case 1:
				printf("evalexp.c: Constant Tag\n");
				break;
			case 2:
				printf("evalexp.c: Var Tag\n");
				break;
			case 3:
				printf("evalexp.c: OppApp Tag\n");
				result = listEval(e->op, e, q);
				evalexp(e->body);
				break;
		}
	}

	return tail->val;
}

int listEval(int oper, struct exp * e, struct env *env) {

	int result = 0;
	int varval = 0;
	struct explist *curr;


	//If it is multiplication, make result = 1 so we actually get an answer
	if(oper == 1)
	{
		result = 1;
	}

	curr = e->exps;

	while(curr)
	{
		printf("Node %d %d\n", curr->head->constant, curr->head->tag);

		if(curr->head->tag == 0)
		{
			printf("listeval() tag islet\n");
			evalexpenv(curr->head, env);
			
		}
		//If the element in the list is a constant
		if(curr->head->tag == 1)
		{
			printf("listeval() tag isconstant\n");
			if(oper == 0)
			{
				result += curr->head->constant;
			}
			else if(oper == 1)
			{
				result *= curr->head->constant;
			}
			else
			{
				printf("listeval(): improper operation\n");
				exit(1);
			}
		}
		//If the element is a var
		if(curr->head->tag == 2)
		{
			printf("listeval() tag isvar\n");
			varval = getVarVal(curr->head, env);
			printf("len of Queue %d\n", len);

			if(oper == 0)
			{
				result += varval;
			}
			else if(oper == 1)
			{
				result *= varval;
			}
			else
			{
				printf("listeval(): improper operation\n");
				exit(1);
			}
		}
		curr = curr->tail;

		
	}

	return result;

}

int getVarVal(struct exp *e, struct env *env) {

	int i = 0;

	/*for(i = 0; i < 100; i++)
	{
		if(strcmp(env[i].varname, e->var) == 0)
		{
			printf("getvarval() found: %s %d\n", env[i].varname, env[i].val);
			return env[i].val;
		}
	}*/

	struct env *temp = head;
	while(temp)
	{
		if(strcmp(temp->varname, e->var) == 0)
		{
			printf("getvarval() found while : %s %d\n", temp->varname, temp->val);
			return temp->val;
		}
		temp = temp->next;
	}

	return -1;
}

int evalexpenv(struct exp *e, struct env *env) {

	int result = 0;
	char tempvar[8];
	int i = 0;

	//store the variable for the let tag
	strcpy(tempvar, e->bvar);
	printf("Variable found: %s\n", tempvar);
	//strcpy(env[0].varname, e->bvar);
	//printf("Var found: %s\n", env[0].varname);


	//get the tag for the bexp part of the tree
	switch(e->bexp->tag)
	{
		case 0:
			printf("evalexpen(): tag bexp islet\n");//recursive call
			evalexpenv(e->bexp, env);
			break;
		case 1:
			printf("evalexpen(): tag bexp isconstant\n");
			enqueue(e->bvar, e->bexp->constant, i);//just equating
			strcpy(env[i].varname, e->bvar);
			env[i].val = e->bexp->constant;
			i++;
			print();
			break;
		case 2:
			printf("evalexpen(): tag bexp isvar\n");
			int varval = getVarVal(e->bexp, env);
			enqueue(e->bexp->var, varval, i);
			break;
		case 3:
			printf("evalexpen(): tag bexp isopapp\n");
			result = listEval(e->bexp->op, e->bexp, env);
			printf("evalexpenv(): bexp result found %d\n", result);
			enqueue(tempvar, result, i); //add vars and corresponding vals to queue
			strcpy(env[i].varname, e->bvar); //testing queue
			env[i].val = result;
			i++;
			print();
			break;
	}

	switch(e->body->tag)
	{
		case 0:
			printf("evalexpen(): tag body islet\n");
			evalexpenv(e->body, env);
			break;
		case 1:
			printf("evalexpen(): tag body isconstant\n");
			enqueue(e->bvar, e->bexp->constant, i);
			strcpy(env[i].varname, e->bvar);
			env[i].val = e->bexp->constant;
			i++;
			print();
			break;
		case 2:
			printf("evalexpen(): tag body isvar\n");
			break;
		case 3:
			printf("evalexpen(): tag body isopapp\n");
			result = listEval(e->body->op, e->body, env);
			printf("evalexpenv(): body result found %d\n", result);
			dequeue(); //remove used vars
			enqueue(tempvar, result, i);
			strcpy(env[i].varname, e->bvar);
			env[i].val = result;
			i++;
			print();
			break;
	}

	return result;
}



/*******Data structure**********/

struct env * init(char * varname, int val, int pos) {

	struct env *newEnv = malloc(sizeof(struct env) * 1);

	if(!newEnv)
	{
		fprintf(stderr, "%s\n", "error: malloc() in function init()");
		exit(0);
	}

	strcpy(newEnv->varname, varname);
	newEnv->val = val;
	newEnv->pos = pos;
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

void enqueue(char * varname, int val, int pos) {

	struct env *data;

	data = init(varname, val, pos);

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
        printf("%s %d %d\n", temp->varname, temp->val, temp->pos);
        temp = temp->next;
    }
    printf("\nQueue end printing....\n");

}

