#include <menu.h>
#include <stdlib.h>
#include <string.h>
#include "AsvState.h"

int n_choices;
WINDOW *my_menu_win;
MENU *my_menu;
ITEM **my_items;

void init_win()
{
	initscr();
	start_color();
	raw();
    noecho();
	keypad(stdscr, TRUE);
	
	my_menu_win = newwin(20, 80, 0, 0);
    keypad(my_menu_win, TRUE);
	box(my_menu_win, 0, 0);
	mvwprintw(my_menu_win, 1, 1, "%s", "My menu1");
	
	mvwhline(my_menu_win, 2, 1, ACS_HLINE, 38);
	mvprintw(LINES - 1, 0, "F11 to exit");
	refresh();
	wrefresh(my_menu_win);
}

void set_menu(const AsvState* state)
{
	int n_choices, i;
	
	n_choices = state->Data.size();
	
	my_items = (ITEM **)calloc(n_choices, sizeof(ITEM *));
	for(i = 0; i < n_choices; ++i)
		my_items[i] = new_item(state->Data[i]->id.c_str(), "");
			
	my_menu = new_menu(my_items);
	set_menu_win(my_menu, my_menu_win);
	set_menu_sub(my_menu, derwin(my_menu_win, 2, 38, 3, 1));
	set_menu_mark(my_menu, " ");
	post_menu(my_menu);
}

void main_loop()
{
	int c;
	while((c = wgetch(my_menu_win)) != KEY_F(11))
	{       
		switch(c)
		{	case KEY_DOWN:
			menu_driver(my_menu, REQ_DOWN_ITEM);
			break;
		case KEY_UP:
			menu_driver(my_menu, REQ_UP_ITEM);
			break;
		}
		wrefresh(my_menu_win);
	}	
}

int main1()
{
	init_win();
    int i;
	auto state = make_shared<AsvState>();
	state->Data.push_back(make_shared<AsvEntry>("m1"));
	state->Data.push_back(make_shared<AsvEntry>("m1中+9rr"));
	set_menu(state.get());
	main_loop();
	
	unpost_menu(my_menu);
	free_menu(my_menu);
	for(i = 0; i < n_choices; ++i)
			free_item(my_items[i]);
	endwin();
	
	return 0;
}