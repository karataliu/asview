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
	shared_ptr<AsvState> Current();
	void Add(shared_ptr<AsvState> state); 
private:
    size_t index = 0 ;
	vector<shared_ptr<AsvState>> list;
};
