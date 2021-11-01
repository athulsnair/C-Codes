//============================================================================
// Name        : star2.cpp
// Author      : Athul
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int main() {
	int num;

	cout << "Enter a numbers :";
	cin >> num;

	for(int i = 0; i < num; i++)
	{
		for(int j = 0; j < (num -i-1); j++)
		{
			cout << " ";
		}

		for(int j = 0; j < (2*i+1) ; j++)
		{
			cout << "*";
		}


		cout << endl;
	}

	return 0;
}
