//============================================================================
// Name        : Curses_stringdraw.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <ctime>
#include "curses.h"
using namespace std;

int main() {

	initscr();
	curs_set(false); // hide cursor
	noecho();

	string aString = "Hello";

	/*
	 * Available attributes
	 * A_NORMAL		Normal display (no highlight)
	 * A_STANDOUT	Best highlighting mode of terminal
	 * A_UNDERLINE	Underlining
	 * A_BLINK		Blinking
	 * A_DIM		Half Bright
	 * A_BOLD		Extra bright or bold
	 * A_PROJECT	Protected mode
	 * A_INVIS		Invisible or blank mode
	 * A_ALTCHARSET	Alternate character set
	 * A_CHARTEXT	Bit-mask to extract a character
	 */

	/*
	 * Available colours
	 * COLOUR_BLACK		0
	 * COLOUR_RED		1
	 * COLOUR_GREEN		2
	 * COLOUR_YELLOW	3
	 * COLOUR_BLUE		4
	 * COLOUR_MAGENTA	5
	 * COLOUR_CYAN		6
	 * COLOUR_WHITE		7
	 */

	//attroff(A_UNDERLINE);

	if(!has_colors())
	{
		endwin();
		cout << "Your console doesn't support colours! Too bad..." << endl;
		return 0;
	}

	start_color();

	init_pair(1, COLOR_RED, COLOR_BLACK); // colours are in pair, text colour and background color

	//attron(A_STANDOUT);
	//attron(A_BOLD);
	attron(COLOR_PAIR(1));

	mvprintw(LINES/2, COLS/2 - aString.length()/2, aString.c_str());

	/*
	attroff(A_STANDOUT);
	mvprintw(LINES/2+1, COLS/2 - aString.length()/2, aString.c_str());

	attroff(A_BOLD);
	mvprintw(LINES/2+2, COLS/2 - aString.length()/2, aString.c_str());
	*/

	getch();

	endwin();

	return 0;
}
