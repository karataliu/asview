#include <menu.h>
#include <stdlib.h>
#include <string.h>
#include "AsvState.h"
#include "AsvChain.h"

class AsvWin
{
public:
    AsvWin();
    ~AsvWin();
    void Update(const AsvState* state);
    void MainLoop();
private:
    int itemsCount;
    WINDOW *win;
    MENU *menu;
    ITEM **items;
};

AsvWin::AsvWin()
{
    initscr();
    //start_color();
    //raw();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    win = newwin(20, 80, 0, 0);
    keypad(win, TRUE);
    box(win, 0, 0);
    mvwprintw(win, 1, 1, "%s", "My menu1");

    mvwhline(win, 2, 1, ACS_HLINE, 38);
    mvprintw(LINES - 1, 0, "F11 to exit");
    refresh();
    wrefresh(win);
}

AsvWin::~AsvWin()
{
    unpost_menu(menu);
    free_menu(menu);
    for(auto i = 0; i < itemsCount; ++i)free_item(items[i]);
    endwin();
}

void AsvWin::Update(const AsvState *state)
{
    int i;

    itemsCount = state->Data.size();

    items = (ITEM **)calloc(itemsCount, sizeof(ITEM *));
    for(i = 0; i < itemsCount; ++i)
        items[i] = new_item(state->Data[i]->id.c_str(), "");

    menu = new_menu(items);
    set_menu_win(menu, win);
    set_menu_sub(menu, derwin(win, 2, 38, 3, 1));
    set_menu_mark(menu, " ");
    post_menu(menu);
}

AsvChain chain;
shared_ptr<AsvState> s1;
shared_ptr<AsvState> s2;

void AsvWin::MainLoop()
{
	int c;
    while((c = wgetch(win)) != KEY_F(11))
	{       
		switch(c)
		{	case KEY_DOWN:
                menu_driver(menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(menu, REQ_UP_ITEM);
                break;
            case KEY_LEFT:
                chain.Prev();
                Update(chain.Current().get());
                break;
            case '1':
                chain.Add(s1);
                Update(chain.Current().get());
                break;
            case '2':
                chain.Add(s2);
                Update(chain.Current().get());
                break;
		}

        wrefresh(win);
	}	
}

int main1()
{
    s1 = make_shared<AsvState>();
    s1->Data.push_back(make_shared<AsvEntry>("1a"));
    s1->Data.push_back(make_shared<AsvEntry>("1b"));

    s2 = make_shared<AsvState>();
    s2->Data.push_back(make_shared<AsvEntry>("2a"));
    s2->Data.push_back(make_shared<AsvEntry>("2b"));

    chain.Add(s1);

    AsvWin win;
    win.Update(s1.get());
    win.MainLoop();
	
	return 0;
}


