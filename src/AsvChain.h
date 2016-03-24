#pragma once

#include <vector>
#include <memory>
#include "AsvState.h"

class AsvChain
{
public:
    void Prev();
    void Next();
    std::shared_ptr<AsvState> Current();
    void Add(std::shared_ptr<AsvState> state);
private:
    std::size_t index {};
    std::vector<std::shared_ptr<AsvState>> list;
};
