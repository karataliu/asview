#include "AsvLoader.h"
#include "schemes/AsvCalc.h"

unique_ptr<AsvLoader> GetLoader()
{
    unique_ptr<AsvLoader> loader(new AsvLoader());
    auto calc = new AsvCalc();
    loader->AddProtocol(calc);
    return loader;
}
