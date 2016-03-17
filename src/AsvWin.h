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
