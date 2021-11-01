/*
 * CursesUtils.cpp
 *
 *  Created on: 7 Aug 2021
 *      Author: TESLA BLACK
 */

#include "CursesUtils.h"

enum ArrowKeys{
	UP = KEY_UP,
	DOWN = KEY_DOWN,
	LEFT = KEY_LEFT,
	RIGHT = KEY_RIGHT
};

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

void clearScreen()
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
