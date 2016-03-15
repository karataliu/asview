#include "AsvChain.h"

int AsvChain::Prev()
{
	if (index > 0) return --index;
	return -1;		
}

void AsvChain::Add(shared_ptr<AsvState> state)
{
	list.push_back(state);
	++index;
}

shared_ptr<AsvState> AsvChain::Current()
{
	return list[index];
}