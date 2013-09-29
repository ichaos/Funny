/**
 * Learn how to use ncurses library in C++
 */

 //#include <curses.h>
 #include <ncurses.h>
 #include <stdlib.h> //replace with C++ random function?
 #include <iostream>
 

 using namespace std;

 int main() {
 	//set characters set: default ISO-8859-1
 	setlocale(LC_ALL, "");

 	initscr();
 	cbreak();
 	noecho();

 	int nrows = 30;
 	int ncolumns = 40;
 	int x0 = 0;
 	int y0 = 0;
 	int c;
 	chtype ch;

 	//arguments order, row first, column second, same as reading
 	WINDOW *farm = newwin(nrows, ncolumns, y0, x0);
	nodelay(farm, TRUE);
 	
 	for (int i = 0; i < nrows; i++) {
 		mvwaddch(farm, i, 0, '#' | A_NORMAL);
 		mvwaddch(farm, i, ncolumns - 1, '#' | A_NORMAL);
 	}
 	for (int i = 0; i < ncolumns; i++) {
 		mvwaddch(farm, 0, i, '#' | A_NORMAL);
 		mvwaddch(farm, nrows - 1, i, '#' | A_NORMAL);
 	}
 	//wrefresh(farm);

 	int x, y;
 	//0.5s sleep time
 	int sleep = 500 * 1000;
 	int x = x0 / 2;
 	int y = y0 / 2;
 	while (1) {
 		//get random position for new character each time
 		//x = random() % ncolumns;
 		//y = random() % nrows;
 		//cout << "x: " << x << ", y: " << y << endl;
 		///*
 		if ((c = wgetch(farm)) == ERR) {
 			//mvwaddch(farm, y, x, '#');
 		} else if (c == 'q') {
 			endwin();
 			return 0;
 		} else {
 			ch = c | A_UNDERLINE | COLOR_PAIR(3);
 			mvwaddch(farm, y, x, ch);
 		}
 		//*/
 		//move to random position 
 		//wmove(farm, y, x);
 		//refresh my test fram window
 		//question? if it will clean the characters of previous window?
	 	wrefresh(farm);
	 	usleep(sleep);
 	}

 	return 0;
 }