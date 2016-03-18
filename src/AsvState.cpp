#include "AsvState.h"
#include "AsvUri.h"

AsvEntry::AsvEntry(string id) : id(id) {}

AsvState::AsvState(string uri) : Uri(uri)
{
    auto asvUri = AsvUri::Create(uri);
    if(!asvUri) return;
    this->BoundUri = std::move(asvUri);
}
