#include "AsvLoader.h"
#include "schemes/AsvCalc.h"
#include "schemes/AsvFile.h"

unique_ptr<AsvLoader> GetLoader()
{
    unique_ptr<AsvLoader> loader(new AsvLoader());
    loader->AddProtocol(new AsvCalc());
    loader->AddProtocol(new AsvFile());
    return loader;
}
