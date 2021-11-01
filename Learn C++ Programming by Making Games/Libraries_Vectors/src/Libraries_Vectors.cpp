//============================================================================
// Name        : Libraries_Vectors.cpp
// Author      : Athul
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>

using namespace std;

int main() {

	vector<int> intVec;

	intVec.reserve(10);
	intVec.push_back(6);

	for(int i = 0; i < 20; i++)
	{
		intVec.push_back(7);
		cout << "The size of the Vector: " << intVec.size() <<  endl;
		cout << "The capcity of the Vector: " << intVec.capacity() << endl;
	}

	intVec.pop_back(); // remove the last element in the vector

	cout << "The size of the Vector: " << intVec.size() <<  endl;
	cout << "The capcity of the Vector: " << intVec.capacity() << endl;

	intVec.clear(); // remove all elements from the vector

	if(intVec.empty())
	{
		cout << "Vector is empty" << endl;
	}
	else
	{
		cout << "Vector is not empty" << endl;
	}

	intVec[0] = 20;


	cout << "intVec[0]: " << intVec[0] << endl;

	cout << "The size of the Vector: " << intVec.size() <<  endl;
	cout << "The capcity of the Vector: " << intVec.capacity() << endl;

	if(intVec.empty())
		{
			cout << "Vector is empty" << endl;
		}
		else
		{
			cout << "Vector is not empty" << endl;
		}

	return 0;
}
