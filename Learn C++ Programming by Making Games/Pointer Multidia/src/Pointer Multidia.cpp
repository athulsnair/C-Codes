//============================================================================
// Name        : Pointer.cpp
// Author      : Athul
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;


int main() {


	const int MAX = 10;

	/*int array2D[MAX][MAX];

	int (*pointer)[MAX] = array2D;

	for(int r = 0; r < MAX; r++)
	{
		for(int c = 0; c < MAX; c++)
		{
			pointer[r][c] = r * c;
			cout << "Row: " << r << " Column: " << c << " Value: " << pointer[r][c] << endl;
		}
	}*/

	/*
	int (*pointer)[MAX] = new int[MAX][MAX];

	for(int r = 0; r < MAX; r++)
	{
		for(int c = 0; c < MAX; c++)
		{
			pointer[r][c] = r * c;
			cout << "Row: " << r << " Column: " << c << " Value: " << pointer[r][c] << endl;
		}
	}

	delete [] pointer;*/

	int **pointer = new int *[MAX];

	for(int r = 0; r < MAX; r++)
	{
		pointer[r] = new int[MAX];
	}

	for(int r = 0; r < MAX; r++)
	{
		for(int c = 0; c < MAX; c++)
		{
			pointer[r][c] = r * c;
			cout << "Row: " << r << " Column: " << c << " Value: " << pointer[r][c] << endl;
		}
	}

	for(int r = 0; r < MAX; r++)
	{
		delete [] pointer[r];
	}

	delete [] pointer;

}
