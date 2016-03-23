#include "AsvLoader.h"

void AsvLoader::AddScheme(std::unique_ptr<AsvScheme> protocol)
{
    protocolList.push_back(std::shared_ptr<AsvScheme>{std::move(protocol)});
}

std::shared_ptr<AsvScheme> AsvLoader::GetScheme(std::string schemeName) const
{
    for(auto iter = protocolList.begin(); iter!=protocolList.end(); iter++){
        if((*iter)->CanHandle(schemeName)) return *iter;
    }

    return nullptr;
}
