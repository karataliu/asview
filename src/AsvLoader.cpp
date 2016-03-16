#include "AsvLoader.h"
#include "AsvUri.h"

AsvProtocol::AsvProtocol(string scheme) : scheme(scheme) {}

bool AsvProtocol::CanHandle(string name)
{
	return name == scheme;
}

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

shared_ptr<AsvState> AsvLoader::Load(string uri)
{
	auto asvUri = AsvUri::Create(uri);
	if(asvUri == NULL)
		throw "uri null";
	
	auto protocol = this->GetProtocol(asvUri->Scheme);
	if(protocol == NULL)
		throw "protocol null";
	
	auto state = make_shared<AsvState>();
	state->Uri = uri;
	state->Data = protocol->Load(asvUri->Path);
	return state; 
}