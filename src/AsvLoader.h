#pragma once

#include <list>
#include "AsvScheme.h"

class AsvLoader
{
public:
    AsvScheme* GetScheme(std::string schemeName) const;
    void AddScheme(AsvScheme* scheme);
private:
    std::list<AsvScheme*> protocolList;
};

