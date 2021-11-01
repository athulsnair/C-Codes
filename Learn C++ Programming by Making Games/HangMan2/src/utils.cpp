/*
 * utils.cpp
 *
 *  Created on: 22 May 2021
 *      Author: TESLA BLACK
 */
#include "utils.h"
#include <iostream>
#include <cstring>
using namespace std;


char GetCharacter(const char* prompt, const char* error, const char ValidInput[], int ValidInputLength)
{
	char input;
	bool failure;

	do
	{
		failure = false;
		cout << prompt;
		cin >> input;

		if(cin.fail())
		{
			cin.clear();
			cin.ignore(IGNORE_CHARS, '\n');
			cout <<  error << endl;
			failure = true;
		}
		else
		{
			cin.ignore(IGNORE_CHARS, '\n');

			if(isalpha(input)){
				input = tolower(input);

				for(int i = 0; i < ValidInputLength; i++)
				{
					if(ValidInput[i] == input)
						return input;
				}
			}

			failure = true;
			cout <<  error << endl;
		}

	}while(failure);

	return input;
}

char GetCharacter(const char* prompt, const char* error)
{
	char input;
	bool failure;

	do
	{
		failure = false;
		cout << prompt;
		cin >> input;

		if(cin.fail())
		{
			cin.clear();
			cin.ignore(IGNORE_CHARS, '\n');
			cout <<  error << endl;
			failure = true;
		}
		else
		{
			cin.ignore(IGNORE_CHARS, '\n');

			if(isalpha(input)){
				input = tolower(input);
			}
			else
			{
				failure = true;
				cout <<  error << endl;
			}
		}

	}while(failure);
	return input;
}
