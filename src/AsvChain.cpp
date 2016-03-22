#include "AsvChain.h"

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

void AsvChain::Add(AsvState* state)
{
    if (index < list.size()){
        auto itr = list.begin();
        int idx = index;
        while(--idx >= 0) ++itr;
        while(itr!=list.end()) itr = list.erase(itr);
    }

    list.push_back(std::unique_ptr<AsvState>(state));
	++index;
}

AsvState* AsvChain::Current()
{
    return list[index-1].get();
}
