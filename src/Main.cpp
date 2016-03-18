#include "AsvConfig.h"
#include "AsvLoaderFactory.h"
#include "AsvWin.h"

int main()
{
    AsvWin win(GetLoader());
    // win.Start("calc://0");
    win.Start("file:///home/karata");

    return 0;
}
