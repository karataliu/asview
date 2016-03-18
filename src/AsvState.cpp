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
