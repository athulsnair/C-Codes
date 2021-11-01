//============================================================================
// Name        : TicTacToe.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstring>
#include <cstdlib>
#include "Utils.h"

using namespace std;

const char *INPUT_ERROR_STRING = "Input Error!!!, Please try again";

enum {

	NUM_ROWS = 3,
	NUM_COLUMNS = 3,
	BOARD_SIZE = 3,
	PLAYER1 = 1,
	PLAYER2 = 2
};

void PlayGame();
int GetPositionFromPlayer(int currentPlayer);
bool CheckForValidPlacement(int position, char* board);
void DrawBoard(char *board);
void UpdateBoard(char *board, int position, int currentPlayer);
void DrawSeperatorLine();
void DrawBoardRow(char *board, int r);
int CheckRows(char *board);
int CheckColumns(char *board);
int CheckDiagonal(char *board);
bool AllPositionsFilled(char *board);
bool WantToPlayAgain();
bool IsGameOver(char *board);

int main() {

	cout << " **** Welcome to TicTacToe ****" << endl;
	WaitForKeyPress();

	do
	{
		PlayGame();

	}while(WantToPlayAgain());

	return 0;
}

void PlayGame()
{
	char board[9] = {'0', '1', '2', '3', '4', '5', '6', '7', '8'};
	ClearScreen();
	cout << endl;
	DrawBoard(board);

	int currentPlayer = PLAYER1;

	do{
		int position;
		bool isValidPosition = false;
		do
		{
			position = GetPositionFromPlayer(currentPlayer);
			//cout << position << endl; // debug
			isValidPosition = CheckForValidPlacement(position, board);
			if(!isValidPosition)
			{
				cout << "That is not a Valid Position, Please Try Again: " << endl;
				WaitForKeyPress();
			}
		}while(!isValidPosition);

		UpdateBoard(board, position, currentPlayer);
		DrawBoard(board);

		if(currentPlayer == PLAYER1)
			currentPlayer = PLAYER2;
		else
			currentPlayer = PLAYER1;

	}while(!IsGameOver(board));
	//DrawBoard(board);
}

int GetPositionFromPlayer(int currentPlayer)
{
	int validInputs[] = {0,1,2,3,4,5,6,7,8};
	if(currentPlayer == PLAYER1)
		cout << "PLAYER1 ";
	else
		cout << "PLAYER2 ";
	return GetInteger("Please enter an input(0-8): ", INPUT_ERROR_STRING, validInputs, 9);
}

bool CheckForValidPlacement(int position, char* board)
{
	if(board[position] != 'X' && board[position] != 'O')
	{
		return true;
	}
	else
		return false;
}

void UpdateBoard(char *board, int position, int currentPlayer)
{
	if(currentPlayer == PLAYER1)
	{
		board[position] = 'X';
	}
	else
	{
		board[position] = 'O';
	}
}

void DrawSeperatorLine()
{
	for(int i = 0; i < BOARD_SIZE; i++)
	{
		cout << "+---";
	}
	cout << "+" << endl;
}

void DrawBoardRow(char *board, int r)
{
	cout << "|";
	for(int c = 0; c < BOARD_SIZE; c++)
	{
		cout << " " << board[BOARD_SIZE*r+c] << " |";
	}
	cout << endl;
}

void DrawBoard(char *board)
{
	ClearScreen();
	for(int r = 0; r < BOARD_SIZE; r++)
	{
		DrawSeperatorLine();
		DrawBoardRow(board, r);
	}
	DrawSeperatorLine();
}

bool WantToPlayAgain()
{
	char validInputs[] = {'y', 'n'};

	char input = GetCharacter("Do you want to play again(y/n)?", INPUT_ERROR_STRING, validInputs, 2, CC_LOWER_CASE);

	return input == 'y';
}

bool IsGameOver(char *board)
{
	int rowCheck = CheckRows(board);

	if(rowCheck != 0)
	{
		if(rowCheck == PLAYER1)
		{
			cout << "Player1 Won!!!" << endl;
			return true;
		}
		else if(rowCheck == PLAYER2)
		{
			cout << "Player2 Won!!!" << endl;
			return true;
		}
	}

	int colCheck = CheckColumns(board);
	if(colCheck != 0)
	{
		if(colCheck == PLAYER1)
		{
			cout << "Player1 Won!!!" << endl;
			return true;
		}
		else if(colCheck == PLAYER2)
		{
			cout << "Player2 Won!!!" << endl;
			return true;
		}
	}
	int diaCheck = CheckDiagonal(board);

	if(diaCheck != 0)
	{
		if(diaCheck == PLAYER1)
		{
			cout << "Player1 Won!!!" << endl;
			return true;
		}
		else if(diaCheck == PLAYER2)
		{
			cout << "Player2 Won!!!" << endl;
			return true;
		}
	}

	if(AllPositionsFilled(board))
	{
		cout << "Cat game!!!" << endl;
		return true;
	}

	return false;
}

int CheckRows(char *board)
{
	for(int r = 0; r <  NUM_ROWS; r++)
	{
		if(board[r*NUM_ROWS+0] == 'X' && board[r*NUM_ROWS+1] == 'X' && board[r*NUM_ROWS+2] == 'X')
		{
			return PLAYER1;
		}
		else if(board[r*NUM_ROWS+0] == 'O' && board[r*NUM_ROWS+1] == 'O' && board[r*NUM_ROWS+2] == 'O')
		{
			return PLAYER2;
		}
	}
	return 0;
}

int CheckColumns(char *board)
{
	for(int c = 0; c <  NUM_COLUMNS; c++)
	{
		if(board[c+0] == 'X' && board[c+3] == 'X' && board[c+6] == 'X')
		{
			return PLAYER1;
		}
		else if(board[c+0] == 'O' && board[c+3] == 'O' && board[c+6] == 'O')
		{
			return PLAYER2;
		}
	}
	return 0;
}

int CheckDiagonal(char *board)
{
	if(board[0] == 'X' && board[4] == 'X' && board[8] == 'X')
	{
		return PLAYER1;
	}
	else if(board[0] == 'O' && board[4] == 'O' && board[8] == 'O')
	{
		return PLAYER2;
	}

	if(board[2] == 'X' && board[4] == 'X' && board[6] == 'X')
	{
		return PLAYER1;
	}
	else if(board[2] == 'O' && board[4] == 'O' && board[6] == 'O')
	{
		return PLAYER2;
	}

	return 0;
}

bool AllPositionsFilled(char *board)
{
	for(int i = 0; i < NUM_ROWS * NUM_COLUMNS; i++)
	{
		if(board[i] != 'X' && board[i] != 'O')
			return false;
	}
	return true;
}
