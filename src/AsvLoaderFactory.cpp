#include "AsvLoader.h"
#include "schemes/AsvCalc.h"
#include "schemes/AsvFile.h"

int init = 0;

AsvLoader* GetLoader()
{
    static unique_ptr<AsvLoader> loader(new AsvLoader());
    if(init==0){
        loader->AddProtocol(new AsvCalc());
        loader->AddProtocol(new AsvFile());
        init=1;
    }

    return loader.get();
}
