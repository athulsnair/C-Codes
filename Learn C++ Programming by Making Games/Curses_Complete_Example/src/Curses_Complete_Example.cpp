//============================================================================
// Name        : Curses_Complete_Example.cpp
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
	int currentXpos = 0;
	int currentYpos = 0;

	initscr();
	curs_set(false); // hide cursor
	noecho();
	nodelay(stdscr, true);
	keypad(stdscr, true);

	bool quit = false;
	int input; // int for arrow keys

	mvprintw(10,10, "fFFF");

	clock_t currentTime = clock(); // current time in clock ticks
	const int FPS = 60;

	while(!quit)
	{
		clock_t newTime = clock();
		clock_t dt = newTime - currentTime;

		if(dt > CLOCKS_PER_SEC/FPS)	// CLOCKS_PER_SEC/FPS (t/s/f/s = t/f)
		{
			currentTime = newTime;

			input = getch();

			if(input !='q')
			{
				clear();
				if(input == KEY_UP)
				{
					currentYpos--;
				}
				else if(input == KEY_DOWN)
				{
					currentYpos++;
				}
				else if(input == KEY_RIGHT)
				{
					currentXpos++;
				}
				else if(input == KEY_LEFT)
				{
					currentXpos--;
				}

				mvprintw(currentYpos, currentXpos, "o");
				refresh();
			}
			else
			{
				quit = true;
			}
		}
	}

	endwin();

	return 0;
}
