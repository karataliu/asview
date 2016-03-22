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
}

AsvWin::~AsvWin()
{
    freeMenu();
    delwin(win);
    endwin();
}

void AsvWin::freeMenu()
{
    if(menu){
        unpost_menu(menu);
        free_menu(menu);
        menu = NULL;
        for(auto i = 0; i < itemsCount; ++i)free_item(items[i]);
        free(items);
    }
}

void AsvWin::Start(std::string uri)
{
    chain.Add(AsvState::Create(uri, this->loader).release());
    Refresh();
    this->MainLoop();
}

void AsvWin::Refresh()
{
    Update(chain.Current());
}

void AsvWin::Update(const AsvState *state)
{
    if(!state) return;

    wmove(win, 1, 1);
    wclrtoeol(win);
    mvwprintw(win, 1, 1, "%s", state->Uri.c_str());

    this->freeMenu();
    itemsCount = state->Data.size() + 1;
    items = (ITEM **)calloc(itemsCount, sizeof(ITEM *));
    for(int i = 0; i < itemsCount - 1; ++i)
        items[i] = new_item(state->Data[i]->id.c_str(), "     ");
    items[itemsCount - 1] = new_item(NULL, NULL);

    menu = new_menu(items);
    set_menu_win(menu, win);
    set_menu_sub(menu, derwin(win, 16, 32, 3, 1));
    set_menu_mark(menu, " ");
    post_menu(menu);
}

void AsvWin::MainLoop()
{
    int c;
    while((c = wgetch(win)) != KEY_F(11))
    {
        switch(c)
        {
            case KEY_DOWN:
                menu_driver(menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(menu, REQ_UP_ITEM);
                break;
            case KEY_NPAGE:
                menu_driver(menu, REQ_SCR_DPAGE);
                break;
            case KEY_PPAGE:
                menu_driver(menu, REQ_SCR_UPAGE);
                break;
            case KEY_LEFT:
                chain.Prev();
                Refresh();
                break;
            case KEY_RIGHT:
                chain.Next();
                Refresh();
                break;
            case 13: // ENTER
                chain.Add(chain.Current()->Load1(item_index(current_item(menu))).release());
                Refresh();
                break;
        }

        wrefresh(win);
    }
}

