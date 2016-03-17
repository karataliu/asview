#include "AsvChain.h"

int AsvChain::Prev()
{
	if (index > 0) return --index;
	return -1;		
}

void AsvChain::Add(shared_ptr<AsvState> state)
{
    if (index + 1 < list.size()){
        auto itr = list.begin();
        int idx = index + 1;
        while(--idx >= 0) ++itr;
        while(itr!=list.end()) itr = list.erase(itr);
    }

	list.push_back(state);
	++index;
}

shared_ptr<AsvState> AsvChain::Current()
{
	return list[index];
}
