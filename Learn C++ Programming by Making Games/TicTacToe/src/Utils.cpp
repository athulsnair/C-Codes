/*
 * Utils.cpp
 *
 *  Created on: 10 Oct 2021
 *      Author: TESLA BLACK
 */
#include "Utils.h"
#include <iostream>

using namespace std;


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
			cout << error << endl; // input reading error
			failure = true;
		}
		else	// input read
		{
			cin.ignore(IGNORE_CHARS, '\n');
			if(isalpha(input))	// is input an Alphabet???
			{
				input = tolower(input); // to lower case
			}
			else
			{
				cout << error << endl; // not an Alphabet
				failure = true;
			}
		}

	}while(failure);

	return input;
}

char GetCharacter(const char* prompt, const char* error, const char validIputs[], int validInputLength, CharacterCaseType charCase)
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
			cout << error << endl; // input reading error
			failure = true;
		}
		else	// input read
		{
			cin.ignore(IGNORE_CHARS, '\n');

			if(isalpha(input))	// is input an Alphabet???
			{
				if(charCase == CC_LOWER_CASE)
				{
					input = tolower(input); // to lower case
				}
				else if(charCase == CC_UPPER_CASE)
				{
					input = toupper(input); // to upper case
				}

				for(int i = 0; i < validInputLength; i++)
				{
					if(input == validIputs[i])
					{
						return input;
					}
				}
			}

			cout << error << endl; // not an Alphabet or not found in validInput table
			failure = true;

		}

	}while(failure);

	return input;
}

int GetInteger(const char* prompt, const char* error, const int validIputs[], int validInputLength)
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
			cout << error << endl; // input reading error
			failure = true;
		}
		else	// input read
		{
			for(int i = 0; i < validInputLength; i++)
			{
				if(input == validIputs[i])
					return input;
			}

			cout << error << endl;
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

