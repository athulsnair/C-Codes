//============================================================================
// Name        : pointer.cpp
// Author      : Athul
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int main() {
	/*
	 * int a = 5;

	int *p1 = &a;
	int *p2 = p1;

	cout << "&a:" << &a << endl;
	cout << "p1: " << p1 << endl;
	cout << "*p1: " << *p1 << endl;
	cout << "&p1: " << &p1 << endl;
	cout << "p2: " << p2 << endl;
	cout << "*p2: " << *p2 << endl;
	//cout << "**p2: " << **p2 << endl;
	cout << "&p2: " << &p2 << endl;
	*/

	/*
	int *newIntPtr = new int;

	*newIntPtr = 6;

	cout << *newIntPtr << endl;

	delete newIntPtr;
	*/

	/*
	int length;

	cout << "Enter length : ";
	cin >> length;

	int *newIntPtr = new int[length];

	for(int i= 0; i < length; i++)
	{
		newIntPtr[i] = i+1;

	}

	for(int i= 0; i < length; i++)
	{
		cout << "newIntPtr[" << i << "]:" << newIntPtr[i] << endl;

	}

	delete [] newIntPtr;
	*/

	int array[] = {1,2,3,4,5};

	array[1] = 5;

	cout << array << " "<< &array << " " << &array[0]<< endl;

	for(int i = 0; i < 5; i++)
	{
		cout << array[i] << endl;
	}

	return 0;
}
