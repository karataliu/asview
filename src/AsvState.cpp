#include "AsvState.h"
#include "AsvUri.h"
#include "AsvLoaderFactory.h"

AsvState::AsvState(string uri) : Uri(uri)
{
    auto asvUri = AsvUri::Create(uri);
    if(!asvUri) return;
    // this->Scheme = GetLoader()->GetProtocol(asvUri->Scheme);
    this->BoundUri = std::move(asvUri);
    this->Scheme = NULL;
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
