#include <ncurses.h>

int main(int argc, char *argv[])
{
	initscr();
	start_color();

	init_pair(1,COLOR_RED, COLOR_BLUE);
	printw("A Big strimg which i didn't catr to type fully ");
	mvchgat(0,0,-1,A_BLINK,1,NULL);

	refresh();
	getch();
	endwin();
	return 0;
}
