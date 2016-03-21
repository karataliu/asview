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



AsvState* CreateState(const string& uri, const AsvLoader* loader)
{
    auto state = new AsvState(uri);
    auto scheme = loader->GetProtocol(state->BoundUri->Scheme);
    if (scheme == NULL)
        throw string("scheme null");
    state->Scheme = scheme;

    return state;
}
