#pragma once

#include <list>
#include "AsvScheme.h"
using namespace std;

class AsvLoader
{
public:
    AsvScheme* GetProtocol(string name) const;
    void AddProtocol(AsvScheme* protocol);
private:
    list<AsvScheme*> protocolList;
};

