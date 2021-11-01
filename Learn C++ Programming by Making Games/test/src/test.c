/*
 ============================================================================
 Name        : test.c
 Author      : Athul
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
//#include "header.h"


int main(void) {

	int a = 5;
	int *p1 = &a;
	int *p2 = &p1;
	int **ptr = &p1;
	int *p = *ptr;

	printf("a: %d &a: %d\n", a, &a);
	printf("p1: %d &p1: %d *p1: %d\n", p1, &p1, *p1);
	printf("p2: %d &p2: %d *p2: %d\n", p2, &p2, *p2);
	//printf("**p2: %d\n", **p2); //!!!ERROR
	printf("ptr: %d &ptr: %d *ptr: %d **ptr:%d\n", ptr, &ptr, *ptr, **ptr);
	printf("p:%d &p: %d *p: %d\n", p, &p, *p);



	return 0;
}
