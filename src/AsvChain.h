#pragma once

#include <vector>
#include <memory>
#include "AsvState.h"

class AsvChain
{
public:
    void Prev();
    void Next();
    AsvState* Current();
    void Add(AsvState* state);
private:
    std::size_t index {};
    std::vector<std::unique_ptr<AsvState>> list;
};
