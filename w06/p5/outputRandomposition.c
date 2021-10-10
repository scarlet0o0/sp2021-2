#include <ncurses.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int main(void){
	char mesg[] = "Just a string";
	int row,col;
	int rand_row,rand_col;

	srand(time(NULL));

	initscr();
	getmaxyx(stdscr,row,col);
	rand_row = rand()%row;
	rand_col = rand()%((col-strlen(mesg))+1-strlen(mesg))+strlen(mesg);
	mvprintw(rand_row,rand_col,"%s",mesg);

	mvprintw(row-2,0,"This screen has %d rows and %d columns\n",row,col);
	printw("Try resizing your window(if possible) and then run this program again");
	refresh();
	getch();
	endwin();

	return 0;
}
