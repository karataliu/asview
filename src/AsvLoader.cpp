#include "AsvLoader.h"

void AsvLoader::AddProtocol(AsvScheme* protocol)
{
	protocolList.push_back(protocol);
}

AsvScheme* AsvLoader::GetProtocol(string name) const
{
    for(auto iter = protocolList.begin(); iter!=protocolList.end(); iter++){
		if((*iter)->CanHandle(name)) return *iter;
    }
	return NULL;
}

void AsvLoader::Load(AsvState* state) const
{
    try{
        const AsvUri* asvUri = state->BoundUri.get();
        // auto protocol = this->GetProtocol(asvUri->Scheme);
        auto protocol = state->Scheme;
        if(protocol == NULL)
            throw string("protocol null");

        state->Data = protocol->Load(asvUri->Path);
    } catch (const string& str){
        vector<shared_ptr<AsvEntry>> d1;
        d1.push_back(make_shared<AsvEntry>(str));
        state->Data = d1;
    }
}
