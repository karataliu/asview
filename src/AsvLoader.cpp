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

void AsvLoader::Load(AsvState* state, string append) const
{
    try{
        const AsvUri* asvUri = state->BoundUri.get();
        auto protocol = this->GetProtocol(asvUri->Scheme);
        if(protocol == NULL)
            throw string("protocol null");

        auto path = asvUri->Path;
        if(append != ""){
            path = protocol->Jump(path, append);
            state->Uri = asvUri->Scheme + "://" + path;
        }

        state->Data = protocol->Load(path);
    } catch (const string& str){
        vector<shared_ptr<AsvEntry>> d1;
        d1.push_back(make_shared<AsvEntry>(str));
        state->Data = d1;
    }
}

shared_ptr<AsvState> AsvLoader::Load(AsvState* state, int index) const
{
    auto s1 = std::make_shared<AsvState>(state->Uri);
    this->Load(s1.get(), state->Data[index]->id);
    return s1;
}
