#include <menu.h>
#include <stdlib.h>
#include <string.h>
#include "AsvState.h"
#include "AsvChain.h"
#include "AsvWin.h"

AsvWin::AsvWin(const AsvLoader* loader) : loader(loader)
{
    initscr();
    //start_color();
    raw();
    //cbreak();
    nonl();
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
    menu = NULL;

    // For testing:
    s1 = make_shared<AsvState>();
    s1->Uri="s1";
    s1->Data.push_back(make_shared<AsvEntry>("1a"));
    s1->Data.push_back(make_shared<AsvEntry>("1b"));

    s2 = make_shared<AsvState>();
    s2->Uri="s2";
    s2->Data.push_back(make_shared<AsvEntry>("2a"));
    s2->Data.push_back(make_shared<AsvEntry>("2b"));
}

AsvWin::~AsvWin()
{
    freeMenu();
    endwin();
}

void AsvWin::freeMenu()
{
    if(menu){
        unpost_menu(menu);
        free_menu(menu);
        for(auto i = 0; i < itemsCount; ++i)free_item(items[i]);
    }
}

void AsvWin::Start(string uri)
{
    auto state = this->loader->Load(uri);
    chain.Add(state);
    Refresh();
    this->MainLoop();
}

void AsvWin::Refresh()
{
    Update(chain.Current().get());
}

void AsvWin::Update(const AsvState *state)
{
    if(!state) return;

    wmove(win, 1, 1);
    wclrtoeol(win);
    mvwprintw(win, 1, 1, "%s", state->Uri.c_str());

    this->freeMenu();
    itemsCount = state->Data.size();
    items = (ITEM **)calloc(itemsCount, sizeof(ITEM *));
    for(int i = 0; i < itemsCount; ++i)
        items[i] = new_item(state->Data[i]->id.c_str(), "     ");

    menu = new_menu(items);
    set_menu_win(menu, win);
    set_menu_sub(menu, derwin(win, itemsCount, 8, 3, 1));
    set_menu_mark(menu, " ");
    post_menu(menu);
}

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
            case KEY_ENTER:
                chain.Add(s1);
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
