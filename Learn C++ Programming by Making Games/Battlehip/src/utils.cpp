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


char GetCharacter(const char *prompt, const char* error, const char validInput[], int validInputLength, CharacterCaseType charCase)
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

			if(isalpha(input))
			{

				if(charCase == CC_UPPER_CASE)
				{
					input = toupper(input);
				}
				else if(charCase == CC_LOWER_CASE)
				{
					input = tolower(input);
				}

				for(int i = 0; i < validInputLength; i++)
				{
					if(validInput[i] == input)
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

int GetInteger(const char* prompt, const char* error, const int validInput[], int validInputLength)
{
	int input;
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
			for(int i = 0; i <  validInputLength; i++)
			{
				if(input == validInput[i])
					return input;
			}
			cout <<  error << endl;
			failure = true;
		}

	}while(failure);
	return input;
}

void ClearScreen()
{
	system("cls");
}

void WaitForKeyPress()
{
	system("pause");
}
