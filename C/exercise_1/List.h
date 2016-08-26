#ifndef LIST_H
#define LIST_H
 
 /******************************
 Interface for a List ADT

 Author: Vanessa White
 May, 2015

 This ADT provides basic operations for a list as the datatype.
 Throughout time, I may update it to include new operations, but for now
 it does the bare minimum

 The purpose of the ADT is to grant some flexibility when it comes to using a linked list and to be able to use it
 with any data type you like.

 This ADT does need to Boolean typedef enumeration to function 
 properly. If you do not want to include it you can simply declare
 in this file:

 typedef enum{false, true}Boolean;

 You must provide two function pointers inorder to use this library:

 1) Compare function pointer, it can be called whatever you please but the parameters
 must look something like this:

 int compare(void* data1, void* data2);

 return a positive number when data1 is larger than data2
 reutrn a negative number when data1 is less than data 2
 return zero when data1 equals data2

 The values of data1 and data2 do not have to be integers, they can be any data type you like

 2) Destory function pointer

 Essentially, it can have what you like in the function, but the signature must be as follows:

 void destroy(void * data)


The compare and destroy is used quite frequently throughout my code, you may not see it since they are helper functions.

Currently, the compare is not used as much in this ADT. It would be used for in-order insertion and deletion which may be added
at a later date.

There is one more feature that you may or may not use and that is the printing function. It is good to use for testing which is what I
used it for but you may find it useful. Create a function that is similar to this:

void printData(void* data);

As always, feel free to name the function whatever you like.

This code was tested with Valgrind on Ubuntu 12.04. If there are any issues feel free to contact me
***************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Boolean.h"


struct ListNode {

	void * data;
	int size;
	struct ListNode * next;
};

struct ListADT {
	struct ListNode * head;
	int (*compare)(void* data1, void* data2);
	void (*destroy)(void* data);
};

typedef struct ListADT List;
typedef struct ListNode Node;


/**
  createList:
    Creates a new List and initialized the destroy and compare function pointers
    Returns the new list if memory allocation is sucessful, if unsuccessful it will return NULL
**/
List * createList(int (*compare)(void* data1, void* data2), void (*destroy)(void*));

/**
  destroyList:
    Destroys the list that was created with the createList() function
    calls the delete() function to destroy Node * elements
**/
void destroyList(List * this);

/**
  addToList:
    Adds a node to the back of a list using the insert() function.
**/
void addToList(List * this, void *data);

/**
  isInList:
    Checks a list to see if a specific piece of data is in the list.
    Uses the search() function to iterate through the list.

    Returns true if it is in the list, if not returns false
**/
Boolean isInList(List * this, void * data);

/**
  removeFromList:
    Removes an element from the list: currently it will only remove the head of the list.
    In the future, it will be implemented so a specific piece of data can be removed from the list
    Uses the delete() function
**/
void removeFromList(List * this, void * data);

/**
  printList:
    recursively prints out the List
**/
void printList(Node * this, void (*printNode)(void * data));

/**
  initnode:
    Allocated memory for a node which is of void*
    This is a helper function that is used in insert()

    returns the new allocated node if allocation was successful, if not returns NULL
**/
Node * initnode(void* data);

/**
  insert:
    Inserts a node to the back of the Node structure. Currently, this is all it does, in the future
    an ordered insert may be implemented

    returns the new list with the inserted element if insertion was complete
    returns NULL if allocation is unsuccessful
**/
Node * insert(Node * this, void * data, int(*compare)(void* data1, void* data2));

/**
  search:
    Recursively searches for a specific node specified.
    Comparator is not used, used to do a binary search, not implemented as of now

	If found, it returns the node
	If not found, it recursively calls search() with the next node
	If it is not in the list at all, it returns NULL
**/
Node * search(Node * this, void * data, int (*compare)(void* data1, void* data2));

/**
  delete:
    Deletes a node from the head of the list. Comparator to do a search with search() to find the node easier(THIS IS NOT IMPLEMENTED)
    Returns the new head of the list
**/
Node * delete(Node * this, void * data, int (*compare)(void* data1, void* data2), void (*destroy)(void *));

#endif