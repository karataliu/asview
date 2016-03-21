#include <menu.h>
#include <stdlib.h>
#include <string.h>
#include "AsvState.h"
#include "AsvChain.h"
#include "AsvWin.h"
#include "AsvLoaderFactory.h"

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
    s1 = make_shared<AsvState>("s1");
    s1->Data.push_back(make_shared<AsvEntry>("1a"));
    s1->Data.push_back(make_shared<AsvEntry>("1b"));

    s2 = make_shared<AsvState>("s2");
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
    // auto state = std::make_shared<AsvState>(uri);
    // this->loader->Load(state.get());
    //auto state = this->loader->CreateState(uri);
    auto state = CreateState(uri, this->loader);
    this->loader->Load(state);
    chain.Add(shared_ptr<AsvState>(state));
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
    AsvState* sn;
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
                sn = loader->Load1(chain.Current(), item_index(current_item(menu)));
                loader->Load(sn);
                chain.Add(shared_ptr<AsvState>(sn));
                Refresh();
                break;
            case '1':
                chain.Add(s1);
                Refresh();
                break;
            case '2':
                chain.Add(s2);
                Refresh();
                break;
        }
        wrefresh(win);
    }
}

