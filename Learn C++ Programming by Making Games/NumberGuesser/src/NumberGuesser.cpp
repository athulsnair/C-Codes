//============================================================================
// Name        : NumberGuesser.cpp
// Author      : Athul
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cmath>
#include <cctype>
#include <stdlib.h>
#include <ctime>

using namespace std;

void PlayGame();
bool WantToPlayAgain();
bool IsGameOver(int numberOfTries, int guess, int secretNumber);
int GetGuess(int numberOfTries);
void displayResult(int numberOfTries, int secretNumber);

const int IGNORE_CHARS = 256;

int main() {

	srand((unsigned int)time(NULL));

	do
	{
		PlayGame();

	}while(WantToPlayAgain());

	return 0;
}

void PlayGame()
{
	const int UPPER_LIMIT = 100;
	int guess;
	int numberOfTries = ceil(log2(UPPER_LIMIT));
	int secretNumber = rand() % UPPER_LIMIT;

	do
	{

		guess = GetGuess(numberOfTries);

		if(guess != secretNumber)
		{
			numberOfTries--;
			if(guess > secretNumber)
			{
				cout << "Your guess is too high!" << endl;
			}
			else
			{
				cout << "Your guess is too low!" << endl;
			}
		}

	}while(!IsGameOver(numberOfTries, guess, secretNumber));

	displayResult(numberOfTries, secretNumber);
}

bool IsGameOver(int numberOfTries, int guess, int secretNumber)
{

	return numberOfTries == 0 || guess == secretNumber;
}

int GetGuess(int numberOfTries)
{
	int guess;
	bool failure;


	do
	{
		failure = false;

		cout << "Please enter your guess (Number of tries left: " << numberOfTries << "): ";
		cin >> guess;

		if(cin.fail())
		{
			cin.clear();
			cin.ignore(IGNORE_CHARS, '\n');

			cout << "Input Error!!!, Please try again" << endl;
			failure = true;
		}
	}while(failure);

	return guess;
}

void displayResult(int numberOfTries, int secretNumber)
{
	if(numberOfTries > 0)
	{
		cout << "Your guess is correct, the secret number is: " << secretNumber << endl;
	}
	else
	{
		cout << "Your guess is incorrect, the secret number is: " << secretNumber << endl;
	}
}

bool WantToPlayAgain()
{
	char playAgain;
	bool failure;

	do
	{
		cout << "Do you want to play again ? (y/n)" << endl;
		cin >> playAgain;

		if(cin.fail())
		{
			cin.clear();
			cin.ignore(IGNORE_CHARS, '\n');

			cout << "Input Error!!!, Please try again" << endl;
			failure = true;
		}
		else
		{
			cin.ignore(IGNORE_CHARS, '\n');
			playAgain = tolower(playAgain);
		}

	}while(failure);

	return playAgain == 'y';
}
