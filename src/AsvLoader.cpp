#include "AsvLoader.h"

void AsvLoader::AddProtocol(AsvScheme* protocol)
{
	protocolList.push_back(protocol);
}

AsvScheme* AsvLoader::GetProtocol(std::string name) const
{
    for(auto iter = protocolList.begin(); iter!=protocolList.end(); iter++){
		if((*iter)->CanHandle(name)) return *iter;
    }
	return NULL;
}
