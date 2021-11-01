//============================================================================
// Name        : functionPointer.cpp
// Author      : Athul
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int addition(int a, int b);
int substration(int a, int b);
int multiplication(int a, int b);
int division(int a, int b);
void calculator();
void output(char c, int a, int b, int (*function)(int a, int b));

int main() {

	calculator();

	return 0;
}

void calculator()
{
	int a, b;
	char c;
	cout << "Please enter operation (+, -, *, /) and two integers: ";
	cin >> c >> a >> b;

	switch(c)
	{
	case '+':
	{
		output(c, a, b, addition);
	}
	break;

	case '-':
	{
		output(c, a, b, substration);
	}
	break;

	case '*':
	{
		output(c, a, b, multiplication);
	}
	break;

	case '/':
	{
		output(c, a, b, division);
	}
	break;

	default:
		cout << "Invalid entry!!" << endl;
	}
}

void output(char c, int a, int b, int (*function)(int a, int b))
{
	cout << a << " " << c  << " " <<  b << " = " << function(a, b) << endl;
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
