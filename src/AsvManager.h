#include "AsvChain.h"
#include <vector>

class AsvManager
{
public:
    AsvManager(std::unique_ptr<AsvLoader> loader);
    const AsvState* Current();
    void PushState(std::string uri);
    void Enter();
    void Prev();
    void Next();

    const std::string& Message() const;

    std::unique_ptr<AsvLoader> loader;

    int Index;

private:
    std::string message {};
    AsvChain chain;
};
