//============================================================================
// Name        : Curses_Utils.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "curses.h"
#include "CursesUtils.h"

using namespace std;

int main() {

	InitializeCurses(false);

	string aString = "Hello Everyone!!!";

	mvprintw(10, 10, aString.c_str());

	GetChar();

	shutdownCurses();

	return 0;
}
