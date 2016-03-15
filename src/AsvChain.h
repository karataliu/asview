#pragma once
#include <vector>
#include <memory>
#include "AsvState.h"
using namespace std;

class AsvChain
{
public:
	int Prev();
	shared_ptr<AsvState> Current();
	void Add(shared_ptr<AsvState> state); 
private:
	int index = -1;
	vector<shared_ptr<AsvState>> list;
};