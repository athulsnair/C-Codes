//============================================================================
// Name        : Libraries_Vectors_Sorting.cpp
// Author      : Athul
// Version     :
// Copyright   : Your copyright notice
// Description : Libraries_Vectors_Sorting in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

bool DescentCompare(int x1, int x2);
bool AscentCompare(int x1, int x2);

int main() {

	srand(time(NULL));
	const int MAX = 20;
	const int RANDOM_MAX = 1000;

	vector<int> intVector;

	intVector.reserve(MAX);

	cout << "Random List: " << endl;

	for(int i = 0; i < MAX; i++)
	{
		int x = rand() % RANDOM_MAX;
		intVector.push_back(x);

		cout << x << endl;
	}

	//sort(intVector.begin(), intVector.end());
	//sort(intVector.begin(), intVector.end(), AscentCompare);
	sort(intVector.begin(), intVector.end(), DescentCompare);

	cout << "\nSorted List: " << endl;

	for(int i = 0; i < MAX; i++)
	{
		cout << intVector[i] << endl;
	}

	return 0;
}

bool AscentCompare(int x1, int x2)
{
	return x1 < x2;
}

bool DescentCompare(int x1, int x2)
{
	return x1 > x2;
}
