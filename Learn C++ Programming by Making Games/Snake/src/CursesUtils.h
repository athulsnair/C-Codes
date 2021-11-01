/*
 * CursesUtils.h
 *
 *  Created on: 7 Aug 2021
 *      Author: TESLA BLACK
 */

#ifndef CURSESUTILS_H_
#define CURSESUTILS_H_

#include "curses.h"
#include <string>

enum ArrowKeys{
	AK_UP = KEY_UP,
	AK_DOWN = KEY_DOWN,
	AK_LEFT = KEY_LEFT,
	AK_RIGHT = KEY_RIGHT
};

void InitializeCurses(bool nodelay);
void shutdownCurses();
void ClearScreen();
void RefreshScreen();
int ScreenWidth();
int ScreenHeight();
int GetChar();
void DrawCharacter(int xPos, int yPos, char aCHaracter);
void MoveCursor(int xPos, int yPos);
void DrawSprite(int xPos, int yPos, const char * sprite[], int spriteHeight, int offset = 0);
void DrawString(int xPos, int yPos, const std::string& string);

#endif /* CURSESUTILS_H_ */
