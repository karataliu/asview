#include "AsvLoader.h"
#include "schemes/AsvCalc.h"
#include "schemes/AsvFile.h"

std::unique_ptr<AsvLoader> GetLoader()
{
    std::unique_ptr<AsvLoader> loader(new AsvLoader());
    loader->AddScheme(std::unique_ptr<AsvCalc>(new AsvCalc()));
    loader->AddScheme(std::unique_ptr<AsvFile>(new AsvFile()));

    return loader;
}
