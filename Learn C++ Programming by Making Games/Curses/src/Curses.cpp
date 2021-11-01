//============================================================================
// Name        : Curses.cpp
// Author      : Athul
// Version     :
// Copyright   : Your copyright notice
// Description : Curses Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>

#include "curses.h"
using namespace std;

int main() {

	initscr();// initialise terminal in curses mode
	curs_set(false); // hide cursor

	int windowmaxX = 0;
	int windowmaxY = 0;

	getmaxyx(stdscr, windowmaxY, windowmaxX);

	//move(15, 10);
	//printw("Hello World !!!");
	//mvprintw(20, 15, "Hello World!!!");

	string helloString = "Hello";
	//mvprintw(20, 10, helloString.c_str());

	// LINES is the number of rows of our window
	mvprintw(windowmaxY/2, windowmaxX/2 - helloString.length()/2, helloString.c_str());

	//addch('*');
	//mvaddch(4, 4, '*');

	//clear();

	refresh();

	getch(); // get one character from user. Here used as "pause"

	endwin();	// restore console to original state


	return 0;
}
