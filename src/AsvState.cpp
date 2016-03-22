#include "AsvState.h"
#include "AsvUri.h"
#include "AsvLoaderFactory.h"
using namespace std;

AsvState::AsvState(string uri) : Uri(uri)
{
    auto asvUri = AsvUri::Create(uri);
    if(!asvUri) return;
    this->BoundUri = std::move(asvUri);
    this->Scheme = NULL;
}

void AsvState::Load()
{
    try{
        const AsvUri* asvUri = this->BoundUri.get();
        auto protocol = this->Scheme;
        if(protocol == NULL)
            throw string("protocol null");

        this->Data = protocol->Load(asvUri->Path);
    } catch (const string& str){
        vector<shared_ptr<AsvEntry>> d1;
        d1.push_back(make_shared<AsvEntry>(str));
        this->Data = d1;
    }
}

unique_ptr<AsvState> AsvState::Load1(std::size_t index) const
{
    if (index >= this->Data.size()){
        throw "invalid index";
    }

    const AsvUri* asvUri = this->BoundUri.get();
    auto protocol = this->Scheme;
    if(protocol == NULL)
        throw string("protocol null");

    auto path = asvUri->Path;
    path = protocol->Jump(path, this->Data[index]->id);
    auto newuri = asvUri->Scheme + "://" + path;

    unique_ptr<AsvState> s2 = unique_ptr<AsvState>(new AsvState(newuri));
    s2->Scheme = this->Scheme;

    s2->Load();
    return s2;
}

unique_ptr<AsvState> AsvState::Create(const string& uri, const AsvLoader* loader)
{
    auto state = unique_ptr<AsvState>(new AsvState(uri));
    auto scheme = loader->GetScheme(state->BoundUri->Scheme);
    if (scheme == NULL)
        throw string("scheme null");
    state->Scheme = scheme;

    state->Load();
    return state;
}
