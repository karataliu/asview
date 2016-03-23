#include "AsvChain.h"
#include "AsvException.h"

void AsvChain::Prev()
{
    if (index <= 1) throw AsvException("First state reached.");
    --index;
}

void AsvChain::Next()
{
    if (index >= list.size()) throw AsvException("Last state reached.");
    ++index;
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
    if(index - 1 >= list.size()) return NULL;
    return list[index-1].get();
}
