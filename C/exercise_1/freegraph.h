#ifndef FGRPH_H
#define FGRPH_H

#include <stdio.h>
#include "List.h"

struct A {
    struct A *a, *b, *c;
    long n;
};

struct A stack[100];


long sumA(struct A *ap);

void deallocateA(struct A *ap);
int compare(void* data1, void* data2);
void printData(void* data);
void destroy(void * data);

#endif