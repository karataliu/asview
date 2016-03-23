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

    int itemsCount;
    WINDOW *win;
    MENU *menu;
    ITEM **items;

    void Refresh();
    void Update();
    void MainLoop();
    void freeMenu();
    void Hint(const char* message);
};
