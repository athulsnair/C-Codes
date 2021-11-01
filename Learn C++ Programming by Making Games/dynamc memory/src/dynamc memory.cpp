//============================================================================
// Name        : dynamc.cpp
// Author      : Athul
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int main() {
	/*int * newIntPtr = new int;

	*newIntPtr = 8;

	cout << *newIntPtr << endl;

	delete newIntPtr;*/

	//char * newCharPtr = new char[5];

	char a[3];

	char *c = a;

	//char * next = newCharPtr;

	for(int i = 0; i < 3; i++)
	{
		cin >> *(a+i);
	}

	for(int i = 0; i < 3; i++)
	{
		//cout << newCharPtr[i] << endl;
		//cout << a[i] << endl;
		//cout << *(a+i) << endl;
		//cout << *(c+i) << endl;
		cout << c[i] << endl;
	}

	return 0;
}
