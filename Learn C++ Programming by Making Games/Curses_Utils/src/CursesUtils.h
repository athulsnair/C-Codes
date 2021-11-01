/*
 * CursesUtils.h
 *
 *  Created on: 7 Aug 2021
 *      Author: TESLA BLACK
 */

#ifndef CURSESUTILS_H_
#define CURSESUTILS_H_

#include "curses.h"


void InitializeCurses(bool nodelay);
void shutdownCurses();
void ClearScreen();
void RefreshScreen();
int ScreenWidth();
int ScreenHeight();
int GetChar();
void DrawCharacter(int xPos, int yPos, char aCHaracter);
void MoveCursor(int xPos, int yPos);

#endif /* CURSESUTILS_H_ */
