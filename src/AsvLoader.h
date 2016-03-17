#pragma once

// Loader with protocol
#include <vector>
#include <memory>
#include <list>
#include "AsvState.h"
using namespace std;

class AsvProtocol
{
public:
	AsvProtocol(string scheme);
	bool CanHandle(string name);
	virtual vector<shared_ptr<AsvEntry>> Load(string path) = 0;
    virtual string Jump(string path, string id);
private:
	string scheme;
};

class AsvLoader
{
public:
    shared_ptr<AsvState> Load(string uri, string append = "") const;
    shared_ptr<AsvState> Load(shared_ptr<AsvState> state, int index) const;
    AsvProtocol* GetProtocol(string name) const;
	void AddProtocol(AsvProtocol* protocol);
private:
	list<AsvProtocol*> protocolList;
};

