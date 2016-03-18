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
    shared_ptr<AsvState> Load(string uri, string append = "") const;
    shared_ptr<AsvState> Load(const AsvState* state, int index) const;
    AsvScheme* GetProtocol(string name) const;
    void AddProtocol(AsvScheme* protocol);
private:
    list<AsvScheme*> protocolList;
};

