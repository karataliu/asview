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

AsvProtocol* AsvLoader::GetProtocol(string name) const
{
    for(auto iter = protocolList.begin(); iter!=protocolList.end(); iter++){
		if((*iter)->CanHandle(name)) return *iter;
    }
	return NULL;
}

shared_ptr<AsvState> AsvLoader::Load(string uri) const
{
    auto state = make_shared<AsvState>();
    state->Uri = uri;

    try{
        auto asvUri = AsvUri::Create(uri);
        if(asvUri == NULL)
            throw string("uri null");

        auto protocol = this->GetProtocol(asvUri->Scheme);
        if(protocol == NULL)
            throw string("protocol null");

        state->Data = protocol->Load(asvUri->Path);
    } catch (const string& str){
        vector<shared_ptr<AsvEntry>> d1;
        d1.push_back(make_shared<AsvEntry>(str));
        state->Data = d1;
    }

	return state; 
}
