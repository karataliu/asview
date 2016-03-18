#pragma once

// Loader with protocol
#include <vector>
#include <memory>
#include <list>
#include "AsvState.h"
#include "AsvScheme.h"
using namespace std;

class AsvLoader
{
public:
    void Load(AsvState* state) const;
    AsvState* Load1(AsvState* state, size_t index) const;
    AsvScheme* GetProtocol(string name) const;
    void AddProtocol(AsvScheme* protocol);
private:
    list<AsvScheme*> protocolList;
};

