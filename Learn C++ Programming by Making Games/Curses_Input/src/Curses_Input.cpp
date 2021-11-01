//============================================================================
// Name        : Curses_Input.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "curses.h"
using namespace std;

int main() {

	initscr();// initialise terminal in curses mode
	curs_set(false); // hide cursor
	noecho(); // avoid seeing other characters
	nodelay(stdscr, true); // true means no delay->  cause: "getch()" to not block anymore
	keypad(stdscr, true); // enable keypad arrow keys

	bool quit = false;
	int input;

	while(!quit)
	{
		input = getch(); // read one character from terminal

		/*if(input == 'q')
			quit = true;
		*/

		if(input == KEY_DOWN) // KEY_UP, KEY_RIGHT, KEY_LEFT
			quit = true;

		mvprintw(20, 20, "hello everyone!");

		refresh();
	}


	endwin();	// restore console to original state



	return 0;
}
