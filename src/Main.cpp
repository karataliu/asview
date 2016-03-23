#include "AsvConfig.h"
#include "AsvLoaderFactory.h"
#include "AsvWin.h"
#include <memory>

int main()
{
    AsvWin win(std::unique_ptr<AsvManager>(new AsvManager(GetLoader())));
    // win.Start("calc://0");
    win.Start("file:///home/karata");

    return 0;
}
