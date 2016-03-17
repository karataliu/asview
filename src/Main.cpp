#include "AsvConfig.h"
#include "AsvLoaderFactory.h"
#include "AsvWin.h"

int main()
{
    auto loader = GetLoader();  
    AsvWin win(loader.get());
    win.Start("calc://0");

    return 0;
}
