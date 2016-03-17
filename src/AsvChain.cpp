#include "AsvChain.h"

AsvChain::AsvChain() : index(0) {}

int AsvChain::Prev()
{
    if (index > 1) return --index;
	return -1;		
}

int AsvChain::Next()
{
    if (index < list.size()) return ++index;
    return -1;
}

void AsvChain::Add(shared_ptr<AsvState> state)
{
    if (index < list.size()){
        auto itr = list.begin();
        int idx = index;
        while(--idx >= 0) ++itr;
        while(itr!=list.end()) itr = list.erase(itr);
    }

	list.push_back(state);
	++index;
}

shared_ptr<AsvState> AsvChain::Current()
{
    return list[index-1];
}
