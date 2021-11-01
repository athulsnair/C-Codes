/*
 * CursesUtils.cpp
 *
 *  Created on: 7 Aug 2021
 *      Author: TESLA BLACK
 */

#include "CursesUtils.h"

void InitializeCurses(bool noDelay)
{
	initscr();
	noecho();
	curs_set(false);
	nodelay(stdscr, noDelay);
	keypad(stdscr, true);
}


void shutdownCurses()
{
	endwin();
}

void ClearScreen()
{
	clear();
}

void RefreshScreen()
{
	refresh();
}

int ScreenWidth()
{
	return COLS;
}

int ScreenHeight()
{
	return LINES;
}

int GetChar()
{
	return getch();
}

void DrawCharacter(int xPos, int yPos, char aCharacter)
{
	mvaddch(yPos, xPos, aCharacter);
}

void MoveCursor(int xPos, int yPos)
{
	move(yPos, xPos);
}

void DrawSprite(int xPos, int yPos, const char * sprite[], int spriteHeight, int offset)
{
	for(int h = 0; h < spriteHeight; h++)
	{
		mvprintw(yPos + h, xPos, "%s", sprite[h+offset]);
	}
}

void DrawString(int xPos, int yPos, const std::string& string)
{
	mvprintw(yPos, xPos, string.c_str());
}
