//============================================================================
// Name        : star1.cpp
// Author      : Athul
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int main() {
	int num1, num2;

	cout << "Enter two numbers :";
	cin >> num1 >> num2;

	for(int i = 0; i < num1; i++)
	{
		for(int j = 0; j < num2; j++)
		{
			cout << "*";
		}
		cout << endl;
	}

	return 0;
}
