#include <menu.h>
#include <stdlib.h>
#include <string.h>
#include "AsvState.h"
#include "AsvWin.h"
#include "signal.h"

static AsvWin* currentWin;

static void handle_winch(int sig){
    if(!currentWin) return;
    currentWin->drawWin();
}

const char* AsvWin::clean = "                                               ";
AsvWin::AsvWin(std::unique_ptr<AsvManager> manager) : manager(std::move(manager))
{
    // init screen
    initscr();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    raw();
    nonl();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    this->win   = NULL;
    this->menu  = NULL;
    this->drawWin();

    currentWin = this;
    struct sigaction sa;
    memset(&sa, 0, sizeof(struct sigaction));
    sa.sa_handler = handle_winch;
    sigaction(SIGWINCH, &sa, NULL);
}

void AsvWin::drawWin()
{
    if (win){
        delwin(win);
        endwin();
        refresh();
        clear();
        win = NULL;
    }

    getmaxyx(stdscr, maxY, maxX);
    win = newwin(maxY, maxX, 0, 0);
    box(win, 0, 0);
    keypad(win, TRUE);

    mvwprintw(win, 1, 1, "%s", "My menu1");
    mvwhline(win, 2, 1, ACS_HLINE, maxX-2);
    mvwhline(win, maxY - 3, 1, ACS_HLINE, maxX-2);
    this->hint("F11 to exit.");
    refresh();
    wrefresh(win);

    this->currentState = nullptr;
    this->refreshWin();
}

AsvWin::~AsvWin()
{
    freeMenu();
    if(win){
        delwin(win);
        endwin();
    }
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

void AsvWin::hint(const char* message)
{
    wattron(this->win, COLOR_PAIR(1));
    mvwprintw(this->win, LINES - 2, 1, message);
    wattroff(this->win, COLOR_PAIR(1));
}

void AsvWin::Start(std::string uri)
{
    this->manager->PushState(uri);
    this->mainLoop();
}

void AsvWin::refreshWin()
{
    this->hint(clean);
    this->hint(this->manager->Message().c_str());
    update();
    wrefresh(win);
}

void AsvWin::update()
{
    std::shared_ptr<AsvState> state = this->manager->Current();
    if(!state || state == currentState) return;

    wmove(win, 1, 1);
    mvwprintw(win, 1, 1, "%s", state->Uri.c_str());

    this->freeMenu();
    itemsCount = state->Data.size() + 1;
    items = (ITEM **)calloc(itemsCount, sizeof(ITEM *));
    for(int i = 0; i < itemsCount - 1; ++i)
        items[i] = new_item(state->Data[i]->id.c_str(), "    ");
    items[itemsCount - 1] = new_item(NULL, NULL);

    menu = new_menu(items);
    set_menu_win(menu, win);
    // need free this sub win?
    auto sw = derwin(win, maxY - 5, maxX-2, 3, 1);
    // box(sw, 0, 0);
    set_menu_sub(menu, sw);
    set_menu_format(menu, maxY - 6, 1);
    set_menu_mark(menu, " ");
    post_menu(menu);

    this->currentState = state;
}

void AsvWin::mainLoop()
{
    int c;

    this->refreshWin();
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
                this->manager->Prev();
                break;
            case KEY_RIGHT:
                this->manager->Next();
                break;
            case 13: // ENTER
                this->manager->Index = item_index(current_item(menu));
                this->manager->Enter();
                break;
            default:
                std::string a("unknown key" + std::to_string(c));
                this->hint(a.c_str());
                break;
        }

        this->refreshWin();
    }
}
