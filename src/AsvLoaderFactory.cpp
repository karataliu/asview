#include "AsvLoader.h"
#include "schemes/AsvCalc.h"
#include "schemes/AsvFile.h"

int init = 0;

AsvLoader* GetLoader()
{
    static std::unique_ptr<AsvLoader> loader(new AsvLoader());
    if(init==0){
        loader->AddScheme(new AsvCalc());
        loader->AddScheme(new AsvFile());
        init=1;
    }

    return loader.get();
}
