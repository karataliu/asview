#pragma once
#include <vector>
#include <memory>
#include "AsvState.h"
using namespace std;

class AsvChain
{
public:
    AsvChain();
	int Prev();
    int Next();
	shared_ptr<AsvState> Current();
	void Add(shared_ptr<AsvState> state); 
private:
    size_t index;
	vector<shared_ptr<AsvState>> list;
};
