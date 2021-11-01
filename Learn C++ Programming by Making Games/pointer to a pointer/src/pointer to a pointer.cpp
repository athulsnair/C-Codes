//============================================================================
// Name        : pointer.cpp
// Author      : Athul
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

void Resize(int **nptrArray, int newSize);

int main() {

	const int MAX = 10;

	int *optrArray = nullptr;
	optrArray = new int[MAX];

	int length = MAX;

	do
	{
		cout << "Length is now: " << length << endl;

		for(int i = 0; i < length; i++)
		{
			optrArray[i] = i+1;
			cout << "optrArra[" << i << "]: " << optrArray[i] << endl;

		}

		cout << "Please input the new length of the array (0 will quit): ";
		cin >> length;

		if(length > 0)
		{
			Resize(&optrArray, length);
		}

	}while(length > 0);

	delete [] optrArray;

	return 0;
}

void Resize(int **optrArray, int newSize)
{

	if(optrArray != nullptr)
		delete [] *optrArray;

	*optrArray = new int[newSize];
}
