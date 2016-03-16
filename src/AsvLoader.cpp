#include "AsvLoader.h"


AsvProtocol::AsvProtocol(string scheme) : scheme(scheme) {}

bool AsvProtocol::CanHandle(string name)
{
	return name == scheme;
}


AsvLoader* AsvLoader::Instance = new AsvLoader();

void AsvLoader::AddProtocol(AsvProtocol* protocol)
{
	protocolList.push_back(protocol);
}

AsvProtocol* AsvLoader::GetProtocol(string name)
{
	for(auto iter = protocolList.begin(); iter!=protocolList.end(); iter++)
		if((*iter)->CanHandle(name)) return *iter;
	return NULL;
}