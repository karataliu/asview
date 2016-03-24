#include <menu.h>
#include <stdlib.h>
#include <string.h>
#include "AsvManager.h"

class AsvWin
{
public:
    AsvWin(std::unique_ptr<AsvManager> manager);
    ~AsvWin();
    void Start(std::string uri);
private:
    static const char* clean;
    std::unique_ptr<AsvManager> manager;
    std::shared_ptr<AsvState> currentState;

    int itemsCount;
    WINDOW *win;
    MENU *menu;
    ITEM **items;

    void drawWin();
    void refreshWin();
    void update();
    void mainLoop();
    void freeMenu();
    void hint(const char* message);
};
