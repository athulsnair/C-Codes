//============================================================================
// Name        : HangMan.cpp
// Author      : Athul
// Version     :
// Copyright   : Your copyright notice
// Description : HangMan in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstring>
#include "utils.h"

using namespace std;

/*
 Create the program Hangman. Prompt the player to enter a phrase.
 That phrase will be hidden by a series of dashes (excluding spaces).
 The player can then guess letters. If they guess correctly all the letters that match will be revealed.
 If they guess incorrectly, then 1 more body part will be added to the gallows.
 If they lose the gallows should look like this:

 +---+
 |   |
 |   o
 |  /|\
 |  / \
-+-

If the player loses, the phrase should be revealed.
After the game is over the player should be prompted if they want to play again.
 */



/*
 We need a variable to store secret phrase
 we need a variable to store hidden phrase
 we need a variable to store number of guesses

 Step 1
 Main
 ------

 do
 {
 	 PlayGame();
 }while(WantToPlayAgain)


 Step 2

 PlayGame
 --------

 secretPhrase = GetSecretPhrase()
 hiddenPhrase = MakeHiddenPhrase(secretPhrase)
 numberOfGuessesLeft = 6

 DrawBoard(HiddenPhrase, numberOfGuessesLeft)

 do
 {
 	 guess = GetGuess()
 	 UpdateBoard(guess, secretPhrase, HiddenPhrase, numberOfGuessesLeft)
 	 DrawBoard(HiddenPhrase, numberOfGuessesLeft)

 }while(!IsGameOver(numberOfGuessesLeft, HiddenPhrase)

 DisplayResult(secretPhrase, numberOfGuessesLeft)

 Step3

 GetSecretPhrase()
 ------------------
 prompt user to type in a string
 get the secret phrase
 return the secret phrase


MakeHiddenPhrase(secretPhrase)
-----------------------------
hiddenPhrase = make new cstring given the length of the secret phrase

for(length of the secret phrase)
{
	hiddenPhrase[i] = '-'
}

 return hiddenPhrase

DrawBoard(HiddenPhrase, numberOfGuessesLeft)
---------------------------------------------
Draw hangman based in the number of guesses left
print out hidden phrase

GetGuess()
----------
prompt the user to type in character
get the character
return it

UpdateBoard(guess, secretPhrase, HiddenPhrase, numberOfGuessesLeft)
-------------------------------------------------------------------
bool found = false

for(length of the secret phrase)
{
	if(guess == secretPhrase[i]
	{
		HiddenPhrase[i[ = secretPhrase[i]
		found = true
	}
}

if(!isFound)
	numberOfGuessesLeft--

IsGameOver(numberOfGuessesLeft, HiddenPhrase)
---------------------------------------------
bool hasDash = false

for(length of the secret phrase && !hasDash)
{
	if(HiddenPhrase[i] == '-')
	{
		hasDash = true
	}
}

return numberOfGuessesLeft==0 || !hasDash

 */

const char *ERROR_MSG = "Input Error!!, Please try again";


void PlayGame();
bool WantToPlayAgain();
int GetSecretPhrase(char secretPhrase[], int maxLength);
char * MakeHiddenPhrase(char *secretPhrase, const int secretPhraseLength);
void DrawBoard(const int numberOfGuesses, const char *noptrhiddenPhrase);
bool IsGameOver(int numberOfGuesses, const char *noptrhiddenPhrase, int secretPhraseLength);
char GetGuess();
void UpdateBoard(char guess, const char secretPhrase[], char *noptrhiddenPhrase, int & numberOfGuesses, const int secretPhraseLength);
void DiplayResult(const char secretPhrase[], const int numberOfGuesses);

int main() {

	do
	{
		PlayGame();

	}while(WantToPlayAgain());

	return 0;
}

void PlayGame()
{
	const int MAX_NUMBER_OF_CHARACTERS = 256;
	const int MAX_NUMBER_OF_GUESSES = 6;
	int secretPhraseLength;
	char guess;

	char secretPhrase[MAX_NUMBER_OF_CHARACTERS];
	char *optrHiddenPhrase = nullptr;
	int numberOfGuesses = MAX_NUMBER_OF_GUESSES;

	secretPhraseLength = GetSecretPhrase(secretPhrase, MAX_NUMBER_OF_CHARACTERS);
	optrHiddenPhrase = MakeHiddenPhrase(secretPhrase, secretPhraseLength);

	DrawBoard(numberOfGuesses, optrHiddenPhrase);

	do
	{
		guess = GetGuess();

		UpdateBoard(guess, secretPhrase, optrHiddenPhrase, numberOfGuesses, secretPhraseLength);
		DrawBoard(numberOfGuesses, optrHiddenPhrase);

	}while(!IsGameOver(numberOfGuesses, optrHiddenPhrase, secretPhraseLength));

	DiplayResult(secretPhrase, numberOfGuesses);

	delete [] optrHiddenPhrase;

}

int GetSecretPhrase(char secretPhrase[], int maxLength)
{
	bool failure = false;
	int length;

	do
	{
		cout << "Please Enter your Secret Phrase: ";
		cin.get(secretPhrase, maxLength);

		if(cin.fail())
		{
			cin.clear();
			cin.ignore(IGNORE_CHARS, '\n');
			failure = true;
			cout << ERROR_MSG << endl;
		}
		else
		{
			length = strlen(secretPhrase);
			if(length == 0)
			{
				cout << "You must enter a word that is longer than 0 characters, Please try again" << endl;
				failure = true;
			}
		}
	}while(failure);

	return length;

}

char * MakeHiddenPhrase(char *secretPhrase, const int secretPhraseLength)
{
	char *hiddentPhrase = new char[secretPhraseLength + 1];

	for(int i = 0; i < secretPhraseLength; i++)
	{
		if(secretPhrase[i] != ' ')
		{
			hiddentPhrase[i] = '-';
		}
		else
		{
			hiddentPhrase[i] = ' ';
		}
	}

	hiddentPhrase[secretPhraseLength] = '\0';

	return hiddentPhrase;

}


void DrawBoard(const int numberOfGuesses, const char *noptrhiddenPhrase)
{
	switch(numberOfGuesses)
	{
	case 6:
	{
		cout << " +---+" << endl;
		cout << " |   |" << endl;
		cout << " |"     << endl;
		cout << " |"     << endl;
		cout << " |"     << endl;
		cout << " |"     << endl;
		cout << "-+-"    << endl << endl;
	}
	break;
	case 5:
	{
		cout << " +---+" << endl;
		cout << " |   |" << endl;
		cout << " |   O" << endl;
		cout << " |"     << endl;
		cout << " |"     << endl;
		cout << " |"     << endl;
		cout << "-+-"    << endl << endl;
	}
	break;
	case 4:
	{
		cout << " +---+" << endl;
		cout << " |   |" << endl;
		cout << " |   O" << endl;
		cout << " |   |" << endl;
		cout << " |"     << endl;
		cout << " |"     << endl;
		cout << "-+-"    << endl << endl;
	}
	break;
	case 3:
	{
		cout << " +---+" << endl;
		cout << " |   |" << endl;
		cout << " |   O" << endl;
		cout << " |   |\\"<< endl;
		cout << " |"     << endl;
		cout << " |"     << endl;
		cout << "-+-"    << endl << endl;
	}
	break;
	case 2:
	{
		cout << " +---+" << endl;
		cout << " |   |" << endl;
		cout << " |   O" << endl;
		cout << " |  /|\\"<< endl;
		cout << " |"     << endl;
		cout << " |"     << endl;
		cout << "-+-"    << endl << endl;
	}
	break;
	case 1:
	{
		cout << " +---+" << endl;
		cout << " |   |" << endl;
		cout << " |   O" << endl;
		cout << " |  /|\\"<< endl;
		cout << " |    \\"<< endl;
		cout << " |"     << endl;
		cout << "-+-"    << endl << endl;
	}
	break;
	case 0:
	{
		cout << " +---+" << endl;
		cout << " |   |" << endl;
		cout << " |   O" << endl;
		cout << " |  /|\\"<< endl;
		cout << " |  / \\"<< endl;
		cout << " |"     << endl;
		cout << "-+-"    << endl << endl;
	}
	break;
	default:
		break;
	}

	cout << "Secret phrase: " << noptrhiddenPhrase << endl;
	cout << "Number of guesses left: " << numberOfGuesses << endl << endl;
}

bool WantToPlayAgain()
{
	const char validInputs[] = {'y', 'n'};

	char response = GetCharacter("Do you Want to Play Again (y/n): ", ERROR_MSG, validInputs, 2);
	return response == 'y';
}

bool IsGameOver(int numberOfGuesses, const char *noptrhiddenPhrase, int secretPhraseLength)
{
	bool foundDash = false;

	for(int i = 0; i < secretPhraseLength; i++)
	{
		if(noptrhiddenPhrase[i] == '-')
		{
			foundDash = true;
			break;
		}
	}

	return numberOfGuesses == 0 || !foundDash;
}

char GetGuess()
{
	return GetCharacter("Please enter your guess: ", ERROR_MSG);
}

void UpdateBoard(char guess, const char secretPhrase[], char *noptrhiddenPhrase, int & numberOfGuesses, const int secretPhraseLength)
{
	bool found = false;

	for(int i = 0; i < secretPhraseLength; i++)
	{
		if(tolower(secretPhrase[i]) == guess)
		{
			noptrhiddenPhrase[i] = secretPhrase[i];
			found = true;
		}
	}

	if(!found)
		numberOfGuesses--;
}

void DiplayResult(const char secretPhrase[], const int numberOfGuesses)
{
	if(numberOfGuesses > 0)
		cout << "You got it, Secret phrase is: " << secretPhrase << endl;
	else
		cout << "You didn't get it, the phrase was: " << secretPhrase << endl;
}

