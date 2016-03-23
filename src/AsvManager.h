#include "AsvChain.h"

class AsvManager
{
public:
    AsvManager(std::unique_ptr<AsvLoader> loader);
    AsvChain chain;
    std::unique_ptr<AsvLoader> loader;
};
