//============================================================================
// Name        : Reference.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstring>
#include <string>
using namespace std;

void func(int a[])
{
	a[0] = 44;
}

int main() {

	/* Problem 1*/

	/*
	int a = 5;
	int & ref = a;

	int b = 10;

	ref = b;

	ref = 44;

	cout << "ref: " << ref << " a: " <<  a << " b: " << b << " " <<   endl;
	*/

	/*Passing pointer to a function*/

	/*int a[] = {1,2,3};

	for(int i = 0; i <  3; i++)
	{
		cout << a[i] << " ";
	}

	cout << endl;

	func(a);

	for(int i = 0; i <  3; i++)
	{
		cout << a[i] << " ";
	}

	cout << endl;*/

	const char *message[3] = {"AAA", "BBB", "CCC"};

	char *str[4];

	str[0] = new char[4];

	strcpy(str[0], message[0]);

	cout << str[0] << endl;

	str[0][1] = 'd';
	cout << str[0] << endl;




	return 0;
}
