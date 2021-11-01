//============================================================================
// Name        : functionPointer2.cpp
// Author      : Athul
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

typedef int(*Arithmetic)(int, int);

int addition(int a, int b);
int substration(int a, int b);
int multiplication(int a, int b);
int division(int a, int b);

Arithmetic GetArithmeticType(char op);

int main() {

	int a, b;
	char op;

	cout <<  "Enter two number : ";
	cin >> a >> b;

	cout << "Enter operation : ";
	cin >> op;

	Arithmetic oPtr = GetArithmeticType(op);

	cout << a << " " << op << " " << b << " = " << oPtr(a, b) << endl;

	return 0;
}

Arithmetic GetArithmeticType(char op)
{
	switch(op)
	{
	case '+' : return addition;
	case '-' : return substration;
	case '*' : return multiplication;
	case '/' : return division;
	}

	return addition;
}

int addition(int a, int b)
{
	return a + b;
}

int substration(int a, int b)
{
	return a - b;
}

int multiplication(int a, int b)
{
	return a * b;
}

int division(int a, int b)
{
	return a / b;
}
