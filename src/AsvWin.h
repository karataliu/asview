#include <menu.h>
#include <stdlib.h>
#include <string.h>
#include "AsvManager.h"

class AsvWin
{
    enum Layout{
        HEAD, BOTTOM1, BOTTOM2
    };

public:
    AsvWin(std::unique_ptr<AsvManager> manager);
    ~AsvWin();
    void Start(std::string uri);
    void drawWin();
private:
    static const size_t MessageBarWidth { 16 } ;

    std::unique_ptr<AsvManager> manager;
    std::shared_ptr<AsvState> currentState;

    int itemsCount;
    WINDOW *win;
    MENU *menu;
    ITEM **items;

    int scrWidth, scrHeight;
    void refreshWin();
    void update();
    void mainLoop();
    void freeMenu();
    void showText(std::string message, int y, int x, size_t maxWidth);
    void showText(std::string message, Layout layout);
};
