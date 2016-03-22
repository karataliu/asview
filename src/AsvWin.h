#include <menu.h>
#include <stdlib.h>
#include <string.h>
#include "AsvState.h"
#include "AsvChain.h"
#include "AsvLoader.h"

class AsvWin
{
public:
    AsvWin(const AsvLoader *);
    ~AsvWin();
    void Start(std::string uri);
private:
    void Refresh();
    void Update(const AsvState* state);
    void MainLoop();
    void freeMenu();
    AsvChain chain;
    const AsvLoader* loader;
    int itemsCount;
    WINDOW *win;
    MENU *menu;
    ITEM **items;
};
