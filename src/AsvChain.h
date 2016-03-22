#pragma once
#include <vector>
#include <memory>
#include "AsvState.h"
using namespace std;

class AsvChain
{
public:
	int Prev();
    int Next();
    AsvState* Current();
    void Add(AsvState* state);
private:
    size_t index {};
    vector<unique_ptr<AsvState>> list;
};
