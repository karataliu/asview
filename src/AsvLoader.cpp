#include "AsvLoader.h"
#include "AsvUri.h"

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

shared_ptr<AsvState> AsvLoader::Load(string uri, string append) const
{
    auto state = make_shared<AsvState>(uri);

    try{
        auto asvUri = AsvUri::Create(uri);
        if(asvUri == NULL)
            throw string("uri null");

        auto protocol = this->GetProtocol(asvUri->Scheme);
        if(protocol == NULL)
            throw string("protocol null");

        auto path =asvUri->Path;
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

	return state; 
}

shared_ptr<AsvState> AsvLoader::Load(const AsvState* state, int index) const
{
    return this->Load(state->Uri, state->Data[index]->id);
}
