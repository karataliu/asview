#include <menu.h>
#include <stdlib.h>
#include <string.h>
#include "AsvState.h"
#include "AsvManager.h"
#include "AsvLoader.h"

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
    void Update(const AsvState* state);
    void MainLoop();
    void freeMenu();
    void Hint(const char* message);
};
