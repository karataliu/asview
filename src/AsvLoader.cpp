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
        auto protocol = this->GetProtocol(asvUri->Scheme);
        // auto protocol = state->Scheme;
        if(protocol == NULL)
            throw string("protocol null");

        state->Data = protocol->Load(asvUri->Path);
    } catch (const string& str){
        vector<shared_ptr<AsvEntry>> d1;
        d1.push_back(make_shared<AsvEntry>(str));
        state->Data = d1;
    }
}

AsvState* AsvLoader::Load1(AsvState* state, size_t index) const
{
    if (index >= state->Data.size()){
        throw "invalid index";
    }

    const AsvUri* asvUri = state->BoundUri.get();
    auto protocol = this->GetProtocol(asvUri->Scheme);
    if(protocol == NULL)
        throw string("protocol null");

    auto path = asvUri->Path;
    path = protocol->Jump(path, state->Data[index]->id);
    auto newuri = asvUri->Scheme + "://" + path;

    auto s2 = new AsvState(newuri);
    return s2;
}
