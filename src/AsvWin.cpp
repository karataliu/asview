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

    getmaxyx(stdscr, scrHeight, scrWidth);
    win = newwin(scrHeight, scrWidth, 0, 0);
    box(win, 0, 0);
    keypad(win, TRUE);

    mvwhline(win, 2, 1, ACS_HLINE, scrWidth - 2);
    mvwaddch(win, 2, 0, ACS_LTEE	);
    mvwaddch(win, 2, scrWidth-1, ACS_RTEE);
    mvwhline(win, scrHeight - 3, 1, ACS_HLINE, scrWidth-2);
    mvwaddch(win, scrHeight - 3, 0, ACS_LTEE	);
    mvwaddch(win, scrHeight - 3, scrWidth-1, ACS_RTEE);
    mvwhline(win, scrHeight - 2, scrWidth - 2 - MessageBarWidth, ACS_VLINE, 1);
    mvwaddch(win, scrHeight - 3, scrWidth - 2 - MessageBarWidth, ACS_TTEE);
    mvwaddch(win, scrHeight - 1, scrWidth - 2 - MessageBarWidth, ACS_BTEE);

    this->showText("F11 to exit.", BOTTOM2);

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

void AsvWin::Start(std::string uri)
{
    this->manager->PushState(uri);
    this->mainLoop();
}

void AsvWin::refreshWin()
{
    this->showText(this->manager->Message(), BOTTOM1);
    update();
    wrefresh(win);
}

void AsvWin::update()
{
    std::shared_ptr<AsvState> state = this->manager->Current();
    if(!state || state == currentState) return;

    this->showText(state->Uri, HEAD);

    this->freeMenu();
    itemsCount = state->Data.size() + 1;
    items = (ITEM **)calloc(itemsCount, sizeof(ITEM *));
    for(int i = 0; i < itemsCount - 1; ++i)
        items[i] = new_item(state->Data[i]->id.c_str(), "    ");
    items[itemsCount - 1] = new_item(NULL, NULL);

    menu = new_menu(items);
    set_menu_win(menu, win);
    // need free this sub win?
    auto sw = derwin(win, scrHeight - 5, scrWidth-2, 3, 1);
    // box(sw, 0, 0);
    set_menu_sub(menu, sw);
    set_menu_format(menu, scrHeight - 6, 1);
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
                this->showText(a, BOTTOM1);
                break;
        }

        this->refreshWin();
    }
}

void AsvWin::showText(std::string message, int y, int x, size_t maxWidth)
{
    size_t len = message.length();
    if(len > maxWidth){
        message = message.substr(0, maxWidth);
    }else if(len < maxWidth){
        message.insert(len, maxWidth - len, ' ');
    }

    mvwprintw(this->win, y, x, message.c_str());
}


void AsvWin::showText(std::string message, Layout layout)
{
    switch(layout){
        case HEAD:
            this->showText(message, 1, 1, this->scrWidth - 2);
            break;
        case BOTTOM1:
            wattron(this->win, COLOR_PAIR(1));
            this->showText(message, scrHeight - 2, 1, scrWidth - 3 - MessageBarWidth);
            wattroff(this->win, COLOR_PAIR(1));
            break;
        case BOTTOM2:
            this->showText(message, scrHeight - 2, scrWidth - 1 - MessageBarWidth, MessageBarWidth);
            break;
    }
}
