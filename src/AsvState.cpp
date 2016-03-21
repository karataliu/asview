#include "AsvState.h"
#include "AsvUri.h"
#include "AsvLoaderFactory.h"

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

AsvState* AsvState::Load1(size_t index) const
{
    if (index >= this->Data.size()){
        throw "invalid index";
    }

    const AsvUri* asvUri = this->BoundUri.get();
    auto protocol = this->Scheme;;
    if(protocol == NULL)
        throw string("protocol null");

    auto path = asvUri->Path;
    path = protocol->Jump(path, this->Data[index]->id);
    auto newuri = asvUri->Scheme + "://" + path;

    auto s2 = new AsvState(newuri);
    s2->Scheme = this->Scheme;
    return s2;
}
