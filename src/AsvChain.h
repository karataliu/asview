#pragma once
#include "AsvState.h"
#include<list>
#include<memory>
using namespace std;

class AsvChain
{
public:
	int Prev();
	int Next();
	AsvState* GetCurrent();
	void Add(shared_ptr<AsvState> state); 
private:
};