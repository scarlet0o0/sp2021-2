#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ncurses.h>

#define twTRUE 1
#define twFALSE 0

#define TKIM_COLOR 1

WINDOW *createWindow(int height, int width, int startY, int startX);
void destroyWindow(WINDOW *win);

int main(){
	int x = 0, y = 0, i = 0;
	int max_x = 0, max_y = 0;
	int next_x = 0;
	int direction = 1;
	int ch = 0; // init
	int msg = 0; // init
	char buffer[8]={0,};
	WINDOW *mywin = NULL;

	initscr(); // start curses mode
	cbreak(); // line buffering disabled; pass on everything to me

	if( has_colors() == FALSE ) { // color is not supported
		endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	start_color(); // start the color mode
	/*
	 * define a new color-pair to use it later
	 * : init_pair(index, foreground, background)
	 */
	init_pair(TKIM_COLOR, COLOR_GREEN, COLOR_BLACK);
	noecho();
	keypad(stdscr, TRUE); // call after initscr, to understand KEY strokes
	curs_set(FALSE);

	getmaxyx(stdscr, max_y, max_x);
	x = max_x / 2;
	y = max_y / 2;
	
	int nItem = 3;
	char menus[3][16]={{"  pizza"}, {"  oil"}, {"  apple"}};
	char selMenus[3][8]={{"> pizza"}, {"> oil"}, {"> apple"}};
	char description[3][64]={{"Info: Italian pizza from Pusan"},{"Info: Best rotten oil"},{"Info: Red, poisoned apple"}};
	int currItem = 0;
	int cont = twTRUE;
	int nRemainingItems = nItem;
	int deleted[3]={0,0,0};
	char *deletedMenu="  (deleted)";
	char *deletedMenuSel="> (deleted)";
	
	int boxWidth = 10;
	int boxHeight = 10;
	int boxY = 10;
	int boxX = 0;
	while( cont ) { 
		clear(); // clearn the screen, and place the cursor in upper-left corner
		// write characters on the buffer, and print out when refresh is called
		for( i = 0 ; i < nItem ; i++ ) {
			if( ! deleted[i] ) {
				if( currItem == i ) {
					attron(COLOR_PAIR(TKIM_COLOR));
					mvprintw(i,0,selMenus[i]);
					attroff(COLOR_PAIR(TKIM_COLOR));
				} else mvprintw(i,0,menus[i]);
			} else {
				if( currItem == i ) {
					attron(COLOR_PAIR(TKIM_COLOR));
					mvprintw(i,0,deletedMenuSel);
					attroff(COLOR_PAIR(TKIM_COLOR));
				}
				else mvprintw(i,0,deletedMenu);
			}
		}
		mvhline(i, 0, '_', max_x/2); // draw a horizontal line
		mvprintw(++i,0,description[currItem]); // prints out a message
		if( mywin != NULL )
			mvprintw(++i,0,"Box is not null"); // prints out a message
		else
			mvprintw(++i,0,"Box is null"); // prints out a message

		
		refresh();
		if( mywin != NULL ) {
			destroyWindow(mywin);
			mywin = createWindow(boxWidth,boxHeight,boxY,boxX);
			wrefresh(mywin);
		} 

		ch = (int) getch();	

		switch( ch ) {
			case KEY_UP:
				if( currItem > 0 ) currItem -= 1;
				if( mywin != NULL ) {destroyWindow(mywin); mywin = NULL;}
				break;
			case KEY_DOWN:
				if( currItem + 1 < nItem ) currItem += 1;
				if( mywin != NULL ) {destroyWindow(mywin); mywin = NULL;}
				break;
			case 'd':
				if( ! deleted[currItem] ) {
					deleted[currItem] = 1;
					nRemainingItems -= 1;
				}
				if( mywin != NULL ) {destroyWindow(mywin); mywin = NULL;}
				break;
			case 'q':
				cont = twFALSE;
				if( mywin != NULL ) {destroyWindow(mywin); mywin = NULL;}
				break;
			case 'r':
				if( deleted[currItem] ) {
					deleted[currItem] = 0;
					nRemainingItems += 1;
				}
				if( mywin != NULL ) {destroyWindow(mywin); mywin = NULL;}
				break;				
			case 'w':
				if( mywin == NULL ) {
					mywin = createWindow(boxWidth,boxHeight,boxY,boxX);
				} 
				break;
			case 'x':
				if( mywin != NULL ) {
					destroyWindow(mywin);
					mywin = NULL;
				}
				break;
			default:
				break;
		}
	}
	endwin();

	return 0;
}
WINDOW *createWindow(int height, int width, int startY, int startX){
	WINDOW *localWin =  newwin(height, width, startY, startX);
	box(localWin, 0, 0); // 0,0 for the default char for the vertical and horizontal lines
	wrefresh(localWin); // show the box!
	return localWin;	
} 
void destroyWindow(WINDOW *win){
	wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(win);
	delwin(win);
} 
