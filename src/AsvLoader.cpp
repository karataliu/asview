#include "AsvLoader.h"

void AsvLoader::AddScheme(AsvScheme* protocol)
{
	protocolList.push_back(protocol);
}

AsvScheme* AsvLoader::GetScheme(std::string schemeName) const
{
    for(auto iter = protocolList.begin(); iter!=protocolList.end(); iter++){
        if((*iter)->CanHandle(schemeName)) return *iter;
    }
	return NULL;
}
