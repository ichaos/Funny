//#include <curses.h>
 #include <ncurses.h>
 #include <stdlib.h> //replace with C++ random function?
 #include <iostream>

int main()
{
    initscr();
    refresh();
    start_color();
    init_pair(1,COLOR_YELLOW,COLOR_CYAN);
    WINDOW *win = newwin(10,10,1,1);
    wbkgd(win,COLOR_PAIR(1));
    wprintw(win,"Hello, World.");
    wrefresh(win);
    getch();

    delwin(win);
    endwin();
}