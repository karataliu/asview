#pragma once

#include <list>
#include "AsvScheme.h"

class AsvLoader
{
public:
    AsvScheme* GetProtocol(std::string name) const;
    void AddProtocol(AsvScheme* protocol);
private:
    std::list<AsvScheme*> protocolList;
};

