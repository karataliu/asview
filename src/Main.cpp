#include "AsvConfig.h"
#include "AsvLoader.h"
#include "AsvWin.h"

unique_ptr<AsvLoader> GetLoader()
{
    unique_ptr<AsvLoader> loader;
    return loader;
}


int main()
{
    auto loader = GetLoader();

    AsvChain chain;
    auto s1 = make_shared<AsvState>();
    s1->Data.push_back(make_shared<AsvEntry>("1a"));
    s1->Data.push_back(make_shared<AsvEntry>("1b"));

    auto s2 = make_shared<AsvState>();
    s2->Data.push_back(make_shared<AsvEntry>("2a"));
    s2->Data.push_back(make_shared<AsvEntry>("2b"));

    chain.Add(s1);

    AsvWin win;
    win.Update(s1.get());
    win.MainLoop();

    return 0;
}
